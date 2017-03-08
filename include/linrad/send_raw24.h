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


#ifndef INCLUDED_LINRAD_SEND_RAW24_H
#define INCLUDED_LINRAD_SEND_RAW24_H

#include <linrad/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace linrad {

    /*!
     * \brief <+description of block+>
     * \ingroup linrad
     *
     */
    class LINRAD_API send_raw24 : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<send_raw24> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of linrad::send_raw24.
       *
       * To avoid accidental use of raw pointers, linrad::send_raw24's
       * constructor is in a private implementation
       * class. linrad::send_raw24::make is the public interface for
       * creating new instances.
       */
      static sptr make(char *ip, int base_port, float passband_center, int bufsize);
    };

  } // namespace linrad
} // namespace gr

#endif /* INCLUDED_LINRAD_SEND_RAW24_H */

