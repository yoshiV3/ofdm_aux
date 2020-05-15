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
#include "decoder_reed_solomon_bb_impl.h"

namespace gr {
  namespace ofdmAux {

    decoder_reed_solomon_bb::sptr
    decoder_reed_solomon_bb::make()
    {
      return gnuradio::get_initial_sptr
        (new decoder_reed_solomon_bb_impl());
    }


    /*
     * The private constructor
     */
    decoder_reed_solomon_bb_impl::decoder_reed_solomon_bb_impl()
      : gr::sync_decimator("decoder_reed_solomon_bb",
              gr::io_signature::make(1, 1, sizeof(char)),
              gr::io_signature::make(2, 2, sizeof(char)), 2)
    {
    	d_prime = 19;
    	unsigned char exponent = 1; 
    	d_table_log[0] = (unsigned char) 255;
    	for(unsigned char log = 0; log < 15; log++)
    	{
    		d_table_log[exponent]        = log;
    		d_table_exp[log]             = exponent;
    		d_table_exp[15+log]          = exponent;
    		exponent                     = exponent<<1; 
    		if (exponent >= 16)
    		{
    			exponent = (unsigned char) exponent ^ d_prime; 	
    		}
			d_table_exp[31] = d_table_exp[16];
			d_table_exp[30] = d_table_exp[15];				
    	}
    }

    /*
     * Our virtual destructor.
     */
    decoder_reed_solomon_bb_impl::~decoder_reed_solomon_bb_impl()
    { 
    }
    
    
    unsigned char 
    decoder_reed_solomon_bb_impl::inverse(unsigned char x)
    {
    	return d_table_exp[15 - d_table_log[x]]; 
    }
    
    unsigned char 
    decoder_reed_solomon_bb_impl::discrete_log(unsigned char x)
    {
    	return d_table_log[x]; 
    }
    unsigned char 
    decoder_reed_solomon_bb_impl::multiplication(unsigned char x, unsigned char y)
    {
	 	if( (x == 0) || (y == 0))
	 	{
			return 0;
		}
		return d_table_exp[d_table_log[x] + d_table_log[y]];  	
	}

    int
    decoder_reed_solomon_bb_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const unsigned char  *in           = (const unsigned char *) input_items[0];
      unsigned char        *out_data     = (unsigned char *)       output_items[0];
	  unsigned char        *out_meta	 = (unsigned char *)       output_items[1];
      // Do <+signal processing+>
      for (int word =0; word < noutput_items; word++)
      {
		  unsigned char synd[2]; 
		  unsigned char highest_one = (in[word*2]&240) >>4;
		  unsigned char highest_two = (in[word*2+1]&240) >>4;
		  unsigned char lowest_one  = in[word*2]&15 ;
		  unsigned char lowest_two  = in[word*2+1]&15;     
		  synd[1] = highest_one ^ lowest_one ^ highest_two ^ lowest_two;
		  synd[0] = multiplication(highest_one,8) ^ multiplication(lowest_one ,4) ^ multiplication(highest_two,2) ^ lowest_two;
		  if( (synd[1] == 0) && (synd[0] == 0))
		  {
		  	 out_data[word] = (highest_one << 4) +  lowest_one; 
		  	 out_meta[word] = 1;
		  } 
		  else if ((synd[1] == 0) || (synd[1] == 0))
		  {
		  	 out_data[word] = (highest_one << 4) +  lowest_one; 
		  	 out_meta[word] = 0;		  	
		  }
		  else 
		  {
		  	unsigned char position = 3-discrete_log(multiplication(synd[0], inverse(synd[1])));
		  	if ((position < 0) | (position > 3))
		  	{
			  	 out_data[word] = (highest_one << 4) +  lowest_one; 
			  	 out_meta[word] = 0;		  		
		  	}
		  	else
		  	{
		  		if(position == 0)
		  		{
		  			highest_one = highest_one ^ synd[1];
		  		}
		  		else if(position == 1)
		  		{
		  			lowest_one = lowest_one ^ synd[1];
		  		}
		  	    out_data[word] = (highest_one << 4) +  lowest_one; 
		  	    out_meta[word] = 1;		  		
		  	}
		  }
      } 

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace ofdmAux */
} /* namespace gr */

