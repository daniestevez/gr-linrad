/* -*- c++ -*- */
/* 
 * Copyright 2017 Daniel Estevez <daniel@destevez.net>
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "send_raw16_impl.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/time.h>

#include "header.h"

namespace gr {
  namespace linrad {

    send_raw16::sptr
    send_raw16::make(char *ip, int base_port, float passband_center, int bufsize)
    {
      return gnuradio::get_initial_sptr
        (new send_raw16_impl(ip, base_port, passband_center, bufsize));
    }

    /*
     * The private constructor
     */
    send_raw16_impl::send_raw16_impl(char *ip, int base_port, float passband_center, int bufsize)
      : gr::sync_block("send_raw16",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(0, 0, 0))
    {
      d_passband_center = passband_center;
      d_bufsize = bufsize;
      d_ptr = 0;
      d_block_no = 0;
      
      set_output_multiple(SAMPLES_PER_PACKET);

      /* TODO check errors */
      d_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

      memset(&d_sockaddr, 0, sizeof(struct sockaddr_in));
      d_sockaddr.sin_family = AF_INET;
      d_sockaddr.sin_port = htons(base_port);
      d_sockaddr.sin_addr.s_addr = inet_addr(ip);
    }

    /*
     * Our virtual destructor.
     */
    send_raw16_impl::~send_raw16_impl()
    {
    }

    int
    send_raw16_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      char packet[HEADER_LEN + NET_MULTICAST_PAYLOAD];
      struct header *header = (struct header *) &packet;
      int32_t sample;
      char *sample_ptr = (char *) &sample;
      struct timeval tv;
      
      const gr_complex *in = (const gr_complex *) input_items[0];

      for (int i = 0; i < noutput_items; i += SAMPLES_PER_PACKET) {
	for (int j = 0; j < SAMPLES_PER_PACKET; j++) {
	  sample = (int32_t) (in[i+j].real() * INT32_MAX);
	  /* 2 is for 2 ad channels */
	  packet[HEADER_LEN + j*2*BYTES_PER_SAMPLE] = sample_ptr[2];
	  packet[HEADER_LEN + j*2*BYTES_PER_SAMPLE + 1] = sample_ptr[3];

	  sample = (int32_t) (in[i+j].imag() * INT32_MAX);
	  /* 2 is for 2 ad channels */
	  packet[HEADER_LEN + j*2*BYTES_PER_SAMPLE + 2] = sample_ptr[2];
	  packet[HEADER_LEN + j*2*BYTES_PER_SAMPLE + 3] = sample_ptr[3];
	}
	
	d_ptr = (d_ptr + NET_MULTICAST_PAYLOAD) % d_bufsize;

	gettimeofday(&tv, NULL);
	header->passband_center = d_passband_center;
	header->time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	header->userx_freq = 0.0;
	header->ptr = d_ptr;
	header->block_no = d_block_no++;
	header->userx_no = -1;
	header->passband_direction = 1;

	sendto(d_socket, packet, sizeof(packet), 0, (struct sockaddr *) &d_sockaddr, sizeof(d_sockaddr));
      }
      
      return noutput_items;
    }

  } /* namespace linrad */
} /* namespace gr */

