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
#include "encoder_reed_solomon_bb_impl.h"


namespace gr {
  namespace ofdmAux {

    encoder_reed_solomon_bb::sptr
    encoder_reed_solomon_bb::make()
    {
      return gnuradio::get_initial_sptr
        (new encoder_reed_solomon_bb_impl());
    }


    /*
     * The private constructor
     */
    encoder_reed_solomon_bb_impl::encoder_reed_solomon_bb_impl()
      : gr::sync_interpolator("encoder_reed_solomon_bb",
              gr::io_signature::make(1, 1, sizeof(char)),
              gr::io_signature::make(1, 1, sizeof(char)), 2)
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
    	d_generator[0] = 1;
    	d_generator[1] = 3;
    	d_generator[2] = 2;
    }

    /*
     * Our virtual destructor.
     */
    encoder_reed_solomon_bb_impl::~encoder_reed_solomon_bb_impl()
    {
    }
    unsigned char 
    encoder_reed_solomon_bb_impl::multiplication(unsigned char x, unsigned char y)
    {
	 	if( (x == 0) || (y == 0))
	 	{
			return 0;
		}
		return d_table_exp[d_table_log[x] + d_table_log[y]];  	
	}

    int
    encoder_reed_solomon_bb_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const unsigned char  *in  = (const unsigned char *) input_items[0];
      unsigned char        *out = (unsigned char *)       output_items[0];
	  int ninput_items = noutput_items >> 1;
      // Do <+signal processing+>
      for(int index =0; index < ninput_items; index++)
      {
      	unsigned char lowest  = in[index]&15;
      	unsigned char highest = (in[index]&240)>>4;
      	unsigned char msg_out[4];
      	msg_out[0] = highest; 
      	msg_out[1] = lowest; 
      	msg_out[2] = 0;
      	msg_out[3] = 0;
      	for(int i=0; i < 2; i++)
      	{
      		unsigned char coef = msg_out[i]; 
      		if(coef)
      		{
      			for(int j=1; j<3;j++)
      			{
      				unsigned char multipl = multiplication(d_generator[j], coef); 
      				msg_out[i+j] = msg_out[i+j] ^ multipl; 
      			} 
      		}
      	}
      	out[index*2  ]   = (highest << 4)   +  lowest; 
      	out[index*2+1]   = (msg_out[2]<< 4) +  msg_out[3];  
      }
      

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace ofdmAux */
} /* namespace gr */

