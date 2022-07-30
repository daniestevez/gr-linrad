/* -*- c++ -*- */
/*
 * Copyright 2022 Daniel Estevez <daniel@destevez.net>.
 *
 * This file is part of gr-linrad
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_LINRAD_FILL_MISSING_BLOCKS_IMPL_H
#define INCLUDED_LINRAD_FILL_MISSING_BLOCKS_IMPL_H

#include <linrad/fill_missing_blocks.h>
#include <cstdint>

namespace gr {
namespace linrad {

class fill_missing_blocks_impl : public fill_missing_blocks
{
private:
    std::uint16_t d_block_no;
    bool d_block_no_valid;
    size_t d_blocks_missed;

public:
    fill_missing_blocks_impl();
    ~fill_missing_blocks_impl();

    void forecast(int noutput_items, gr_vector_int& ninput_items_required);

    int general_work(int noutput_items,
                     gr_vector_int& ninput_items,
                     gr_vector_const_void_star& input_items,
                     gr_vector_void_star& output_items);
};

} // namespace linrad
} // namespace gr

#endif /* INCLUDED_LINRAD_FILL_MISSING_BLOCKS_IMPL_H */
