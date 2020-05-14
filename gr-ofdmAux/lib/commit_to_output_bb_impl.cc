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
#include <cstdlib>
#include "commit_to_output_bb_impl.h"

namespace gr {
  namespace ofdmAux {

    commit_to_output_bb::sptr
    commit_to_output_bb::make()
    {
      return gnuradio::get_initial_sptr
        (new commit_to_output_bb_impl());
    }


    /*
     * The private constructor
     */
    commit_to_output_bb_impl::commit_to_output_bb_impl()
      : gr::block("commit_to_output_bb",
              gr::io_signature::make(2, 2, sizeof(char)),
              gr::io_signature::make(1, 1, sizeof(char)))
    {
    	d_last_index = 0; 
    	d_first_byte = false;
    	set_tag_propagation_policy(TPP_DONT);
    }

    /*
     * Our virtual destructor.
     */
    commit_to_output_bb_impl::~commit_to_output_bb_impl()
    {
    }
   unsigned char 
   commit_to_output_bb_impl::calculate_drops(unsigned char index)
   {
   		unsigned char difference = index - d_last_index-1;
   		if (difference < 0)
   		{
   			difference = 256 + difference;
   		}
   		return difference;
   }
   void
   commit_to_output_bb_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
   {
      /* <+forecast+> e.g. ninput_items_required[0] = noutput_items */
      ninput_items_required[0] = noutput_items*2;
      ninput_items_required[1] = noutput_items*2;    
   }
   

   int
   commit_to_output_bb_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
   {
      const unsigned char *in_data  = (const unsigned char *) input_items[0];
      const unsigned char *in_state = (const unsigned char *) input_items[1];
      unsigned char       *out      = (unsigned char *)       output_items[0];
      int ninput = std::min(ninput_items[0],ninput_items[1]);
      int nb_committed = 0;
      int nb_consumed  = 0; 
      if(ninput%2)
      {
      	ninput = ninput - 1;
      }
      for(int index; index < ninput; index = index + 2)
      {
      	unsigned char da_value = in_data[index+1];
      	unsigned char da_state = in_state[index+1];
      	unsigned char sn_value = in_data[index];
      	unsigned char sn_state = in_state[index];
		int space_in_buffers   = noutput_items- nb_committed;
      	if(sn_state ==1)
      	{
      		if (!d_first_byte)
      		{
      					for(int i=0; i < sn_value  ; i++)
						{
							out[nb_committed] = 0;
							nb_committed      = nb_committed + 1;
						}
       		    	    out[nb_committed] = da_value; 
      		    		nb_committed      = nb_committed + 1; 
      		    		nb_consumed       = nb_consumed  + 2;
      		    		d_last_index      = sn_value;
      		    		d_first_byte      = true; 
      		    		     			
      		}
      		else if(sn_value == d_last_index)
      		{
      			nb_consumed = nb_consumed +2;//error occurred, last already commited so drop this sample
      		}
      		else
      		{//sn_value does not equal d_last_index
      			unsigned char nb_of_dropped = calculate_drops(sn_value);
      		    if (nb_of_dropped==0)
      		    {
      		    	if((space_in_buffers)>0)
      		    	{
      		    	    out[nb_committed] = da_value; 
      		    		nb_committed      = nb_committed + 1; 
      		    		nb_consumed       = nb_consumed  + 2;
      		    		d_last_index      = sn_value;
      		    		
      		    	}
      		    	else
      		    	{
      		    		break; 
      		    	} 
      		    }
      		    else
      		    {
					int space_shortage = ((int)nb_of_dropped+1)-space_in_buffers;
					if (space_shortage <=0) // at least enough space
					{
						d_last_index = sn_value;
						for(int i=0; i <  nb_of_dropped; i++)
						{
							out[nb_committed] = 0;
							nb_committed      = nb_committed + 1;
						}
						out[nb_committed] = da_value;
						nb_committed      = nb_committed + 1;
						nb_consumed       = nb_consumed  + 2;

 					}
					else 
					{
						for(int i=0; i <  nb_of_dropped-space_shortage+1; i++)
						{
							out[nb_committed] = 0;
							nb_committed      = nb_committed + 1;
							d_last_index      = d_last_index + 1;
						}
						break; 	// no enough space, so we cannot commit current sample (no change at consumed) or any other sample (break)				
					}   
      		    }
      		}
      	}
      	else
      	{
      		if(da_state==1) //here we assume that drops are rare and the bytes are sequential most of the time 
      		{
      				if((space_in_buffers)>0)
      				{
      		    		out[nb_committed] = da_value; 
      		    		nb_committed      = nb_committed + 1; 
      		    		nb_consumed       = nb_consumed  + 2;
      		    	}
      		    	if(!d_first_byte) 
      		    	{
      		    		d_last_index = 0; 
      		    		d_first_byte = true;
      		    	}
      		    	else
      		    	{
      		    		d_last_index      = d_last_index + 1; //sequential bytes assumed
      		    	}    				
      		}
      		else //byte is lost 
      		{    				
      				nb_consumed       = nb_consumed  + 2;
      		}
      	} 
    }

      // Do <+signal processing+>
      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (nb_consumed);

      // Tell runtime system how many output items we produced.
      return nb_committed;
   }

  } /* namespace ofdmAux */
} /* namespace gr */

