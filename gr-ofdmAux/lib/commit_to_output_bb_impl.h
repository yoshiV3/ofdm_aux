/* -*- c++ -*- */
/*
 * Copyright 2020 Yoshi Vermeire.
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

#ifndef INCLUDED_OFDMAUX_COMMIT_TO_OUTPUT_BB_IMPL_H
#define INCLUDED_OFDMAUX_COMMIT_TO_OUTPUT_BB_IMPL_H

#include <ofdmAux/commit_to_output_bb.h>

namespace gr {
  namespace ofdmAux {

    class commit_to_output_bb_impl : public commit_to_output_bb
    {
     private:
     unsigned char calculate_drops(unsigned char index);
     unsigned char d_last_index;
     bool          d_first_byte;
     public:
      commit_to_output_bb_impl();
      ~commit_to_output_bb_impl();

      // Where all the action really happens
      void forecast (int noutput_items, gr_vector_int &ninput_items_required);

      int general_work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);

    };

  } // namespace ofdmAux
} // namespace gr

#endif /* INCLUDED_OFDMAUX_COMMIT_TO_OUTPUT_BB_IMPL_H */

