/* -*- c++ -*- */
/* 
 * Copyright 2020 <+YOU OR YOUR COMPANY+>.
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

#ifndef INCLUDED_OFDMAUX_INSERT_SEQUENCE_NUMBERS_BB_IMPL_H
#define INCLUDED_OFDMAUX_INSERT_SEQUENCE_NUMBERS_BB_IMPL_H

#include <ofdmAux/insert_sequence_numbers_bb.h>

namespace gr {
  namespace ofdmAux {

    class insert_sequence_numbers_bb_impl : public insert_sequence_numbers_bb
    {
     private:
      unsigned char d_current_number; 

     public:
      insert_sequence_numbers_bb_impl();
      ~insert_sequence_numbers_bb_impl();

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
    };

  } // namespace ofdmAux
} // namespace gr

#endif /* INCLUDED_OFDMAUX_INSERT_SEQUENCE_NUMBERS_BB_IMPL_H */

