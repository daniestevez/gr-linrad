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

#ifndef _HEADER_H
#define _HEADER_H

#define HEADER_LEN 24

struct header {
  double passband_center;
  int32_t time;
  float userx_freq;
  uint32_t ptr;
  uint16_t block_no;
  int8_t userx_no;
  int8_t passband_direction;
};

#define NET_MULTICAST_PAYLOAD 1392

#endif
