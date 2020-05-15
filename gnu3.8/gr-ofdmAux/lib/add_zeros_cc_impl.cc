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
#include "add_zeros_cc_impl.h"

namespace gr {
  namespace ofdmAux {

    add_zeros_cc::sptr
    add_zeros_cc::make(int nb_z_frames, int frame_length)
    {
      return gnuradio::get_initial_sptr
        (new add_zeros_cc_impl(nb_z_frames, frame_length));
    }


    /*
     * The private constructor
     */
    add_zeros_cc_impl::add_zeros_cc_impl(int nb_z_frames, int frame_length)
      : gr::block("add_zeros_cc",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(gr_complex))),
        d_nb_z_frames(nb_z_frames),
        d_frame_length(frame_length)
    { 
    	d_required_output = (2*d_nb_z_frames+1)*d_frame_length;
    	set_tag_propagation_policy(TPP_DONT);
    	set_relative_rate(d_nb_z_frames,1); 
    	set_min_noutput_items(d_required_output);
    }

    /*
     * Our virtual destructor.
     */
    add_zeros_cc_impl::~add_zeros_cc_impl()
    {
    }

    void
    add_zeros_cc_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      ninput_items_required[0] = d_frame_length;
    }

    int
    add_zeros_cc_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const unsigned char *in = (const unsigned char *) input_items[0];
      unsigned char *out = (unsigned char *) output_items[0];
	  if( (noutput_items < d_required_output) || (ninput_items[0] < d_frame_length))
	  {
	  	return 0; 
	  }
      for(int index=0; index < d_nb_z_frames*8*d_frame_length;index++)
      {
      	out[index] = 0;
      } 
      memcpy((void*)(out+d_nb_z_frames*8*d_frame_length),
       			(void*)in,
       			d_frame_length*8);
      int offset = (d_nb_z_frames+1)*d_frame_length*8;
      for(int index=offset; index < offset + d_nb_z_frames*8*d_frame_length;index++)
      {
      	out[index] = 0;
      } 
      consume_each (d_frame_length);

      // Tell runtime system how many output items we produced.
      return d_required_output;
    }

  } /* namespace ofdmAux */
} /* namespace gr */

