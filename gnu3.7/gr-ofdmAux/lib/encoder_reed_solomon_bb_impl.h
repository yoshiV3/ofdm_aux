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

#ifndef INCLUDED_OFDMAUX_ENCODER_REED_SOLOMON_BB_IMPL_H
#define INCLUDED_OFDMAUX_ENCODER_REED_SOLOMON_BB_IMPL_H

#include <ofdmAux/encoder_reed_solomon_bb.h>

namespace gr {
  namespace ofdmAux {

    class encoder_reed_solomon_bb_impl : public encoder_reed_solomon_bb
    {
     private:
      unsigned char             d_generator[3];
      unsigned char             d_prime;
      unsigned char             d_table_exp[32];
      unsigned char             d_table_log[16];
      unsigned char multiplication(unsigned char x, unsigned char y);

     public:
      encoder_reed_solomon_bb_impl();
      ~encoder_reed_solomon_bb_impl();

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
    };

  } // namespace ofdmAux
} // namespace gr

#endif /* INCLUDED_OFDMAUX_ENCODER_REED_SOLOMON_BB_IMPL_H */

