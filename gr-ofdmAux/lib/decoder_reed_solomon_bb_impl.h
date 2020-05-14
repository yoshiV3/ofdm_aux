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

#ifndef INCLUDED_OFDMAUX_DECODER_REED_SOLOMON_BB_IMPL_H
#define INCLUDED_OFDMAUX_DECODER_REED_SOLOMON_BB_IMPL_H

#include <ofdmAux/decoder_reed_solomon_bb.h>


namespace gr {
  namespace ofdmAux {

    class decoder_reed_solomon_bb_impl : public decoder_reed_solomon_bb
    {
     private:
      unsigned char             d_table_exp[32];
      unsigned char             d_table_log[16];
      unsigned char             d_prime;
      unsigned char multiplication(unsigned char x, unsigned char y); 
      unsigned char inverse(unsigned char x);
      unsigned char discrete_log(unsigned char x); 
      

     public:
      decoder_reed_solomon_bb_impl();
      ~decoder_reed_solomon_bb_impl();

      // Where all the action really happens
      int work(
              int noutput_items,
              gr_vector_const_void_star &input_items,
              gr_vector_void_star &output_items
      );
    };

  } // namespace ofdmAux
} // namespace gr

#endif /* INCLUDED_OFDMAUX_DECODER_REED_SOLOMON_BB_IMPL_H */

