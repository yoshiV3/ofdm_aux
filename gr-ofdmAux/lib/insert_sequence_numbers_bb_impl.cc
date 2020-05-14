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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "insert_sequence_numbers_bb_impl.h"

namespace gr {
  namespace ofdmAux {

    insert_sequence_numbers_bb::sptr
    insert_sequence_numbers_bb::make()
    {
      return gnuradio::get_initial_sptr
        (new insert_sequence_numbers_bb_impl());
    }


    /*
     * The private constructor
     */
    insert_sequence_numbers_bb_impl::insert_sequence_numbers_bb_impl()
      : gr::sync_interpolator("insert_sequence_numbers_bb",
              gr::io_signature::make(1, 1, sizeof(char)),
              gr::io_signature::make(1, 1, sizeof(char)), 2)
    {
    	d_current_number  = 0; //initialize counter 
    }

    /*
     * Our virtual destructor.
     */
    insert_sequence_numbers_bb_impl::~insert_sequence_numbers_bb_impl()
    {
    }

    int
    insert_sequence_numbers_bb_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const unsigned char *in  = (const unsigned char *) input_items[0];
      unsigned char       *out = (unsigned char *)       output_items[0];

      // Do <+signal processing+>
      int ninput_items = noutput_items>>1;
      for(int i; i<ninput_items;i++)
      {
      	out[i*2]   = d_current_number;
      	out[i*2+1] = in[i];
      	d_current_number++;
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace ofdmAux */
} /* namespace gr */

