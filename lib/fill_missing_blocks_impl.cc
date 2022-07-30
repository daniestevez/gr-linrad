/* -*- c++ -*- */
/*
 * Copyright 2022 Daniel Estevez <daniel@destevez.net>.
 *
 * This file is part of gr-linrad
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "fill_missing_blocks_impl.h"
#include <gnuradio/io_signature.h>
#include <algorithm>
#include <cstdint>
#include <cstring>

#include "header.h"

#define IN_BLOCK_SIZE 1416
#define OUT_BLOCK_SIZE (IN_BLOCK_SIZE - HEADER_LEN)

namespace gr {
namespace linrad {

fill_missing_blocks::sptr fill_missing_blocks::make()
{
    return gnuradio::make_block_sptr<fill_missing_blocks_impl>();
}


fill_missing_blocks_impl::fill_missing_blocks_impl()
    : gr::block("fill_missing_blocks",
                gr::io_signature::make(1, 1, IN_BLOCK_SIZE),
                gr::io_signature::make(1, 1, OUT_BLOCK_SIZE)),
      d_block_no(0),
      d_block_no_valid(false),
      d_blocks_missed(0)
{
}

fill_missing_blocks_impl::~fill_missing_blocks_impl() {}

void fill_missing_blocks_impl::forecast(int noutput_items,
                                        gr_vector_int& ninput_items_required)
{
    ninput_items_required[0] = noutput_items;
}

int fill_missing_blocks_impl::general_work(int noutput_items,
                                           gr_vector_int& ninput_items,
                                           gr_vector_const_void_star& input_items,
                                           gr_vector_void_star& output_items)
{
    auto in = static_cast<const std::uint8_t*>(input_items[0]);
    auto out = static_cast<std::uint8_t*>(output_items[0]);

    auto offset = 0;
    auto produced = 0;
    auto consumed = 0;
    while ((consumed < ninput_items[0]) && (produced < noutput_items)) {
        if (d_blocks_missed) {
            // Output zeros if we need to restore missing blocks.  It is
            // possible that the restoration cannot be completed in this call to
            // work() if there is not enough spaced in the output buffer.
            auto n =
                std::min(d_blocks_missed, static_cast<size_t>(noutput_items - produced));
            auto size = n * OUT_BLOCK_SIZE;
            std::memset(out, 0, size);
            out += size;
            produced += n;
            d_blocks_missed -= n;
            if (produced == noutput_items) {
                break;
            }
        }

        auto block_hdr = reinterpret_cast<const struct header*>(&in[0]);
        auto block_no = block_hdr->block_no;
        if (!d_block_no_valid) {
            // This only happens for the first block that we process.
            d_block_no_valid = true;
            d_block_no = block_no;
        } else if (d_block_no != block_no) {
            // Missed some blocks. We will try to restore them in the next loop
            // iteration.
            d_blocks_missed =
                (static_cast<size_t>(0x10000) + static_cast<size_t>(block_no) -
                 static_cast<size_t>(d_block_no)) &
                0xffff;
            d_block_no = block_no;
            d_logger->warn("lost {:d} Linrad blocks", d_blocks_missed);
            continue;
        }

        // No lost blocks. Copy block to output.
        std::memcpy(out, &in[HEADER_LEN], OUT_BLOCK_SIZE);
        in += IN_BLOCK_SIZE;
        out += OUT_BLOCK_SIZE;
        ++consumed;
        ++produced;
        ++d_block_no;
    }

    consume_each(consumed);
    return produced;
}

} /* namespace linrad */
} /* namespace gr */
