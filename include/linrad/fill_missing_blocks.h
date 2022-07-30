/* -*- c++ -*- */
/*
 * Copyright 2022 Daniel Estevez <daniel@destevez.net>.
 *
 * This file is part of gr-linrad
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_LINRAD_FILL_MISSING_BLOCKS_H
#define INCLUDED_LINRAD_FILL_MISSING_BLOCKS_H

#include <gnuradio/block.h>
#include <linrad/api.h>

namespace gr {
namespace linrad {

/*!
 * \brief Fill missing Linrad network protocol blocks
 * \ingroup linrad
 *
 */
class LINRAD_API fill_missing_blocks : virtual public gr::block
{
public:
    typedef std::shared_ptr<fill_missing_blocks> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of linrad::fill_missing_blocks.
     *
     * To avoid accidental use of raw pointers, linrad::fill_missing_blocks's
     * constructor is in a private implementation
     * class. linrad::fill_missing_blocks::make is the public interface for
     * creating new instances.
     */
    static sptr make();
};

} // namespace linrad
} // namespace gr

#endif /* INCLUDED_LINRAD_FILL_MISSING_BLOCKS_H */
