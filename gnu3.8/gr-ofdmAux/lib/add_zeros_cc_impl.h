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

#ifndef INCLUDED_OFDMAUX_ADD_ZEROS_CC_IMPL_H
#define INCLUDED_OFDMAUX_ADD_ZEROS_CC_IMPL_H

#include <ofdmAux/add_zeros_cc.h>

namespace gr {
  namespace ofdmAux {

    class add_zeros_cc_impl : public add_zeros_cc
    {
     private:
     int d_nb_z_frames;
     int d_frame_length;
     int d_required_output;

     public:
      add_zeros_cc_impl(int nb_z_frames, int frame_length);
      ~add_zeros_cc_impl();

      // Where all the action really happens
      void forecast (int noutput_items, gr_vector_int &ninput_items_required);

      int general_work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);

    };

  } // namespace ofdmAux
} // namespace gr

#endif /* INCLUDED_OFDMAUX_ADD_ZEROS_CC_IMPL_H */
