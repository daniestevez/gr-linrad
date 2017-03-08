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

#ifndef INCLUDED_LINRAD_SEND_RAW24_IMPL_H
#define INCLUDED_LINRAD_SEND_RAW24_IMPL_H

#include <linrad/send_raw24.h>


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define NET_MULTICAST_PAYLOAD 1392
#define BYTES_PER_SAMPLE 3
#define SAMPLES_PER_PACKET (NET_MULTICAST_PAYLOAD/(BYTES_PER_SAMPLE*2))

namespace gr {
  namespace linrad {

    class send_raw24_impl : public send_raw24
    {
     private:
      float d_passband_center;
      uint32_t d_bufsize;
      uint32_t d_ptr;
      uint16_t d_block_no;
      int d_socket;
      struct sockaddr_in d_sockaddr;
      

     public:
      send_raw24_impl(char *ip, int base_port, float passband_center, int bufsize);
      ~send_raw24_impl();

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
    };

  } // namespace linrad
} // namespace gr

#endif /* INCLUDED_LINRAD_SEND_RAW24_IMPL_H */

