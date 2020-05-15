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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "filter_frame_cvc_impl.h"

namespace gr {
  namespace ofdmAux {

    filter_frame_cvc::sptr
    filter_frame_cvc::make(int number_of_symbols, int symbol_length,int guard_interval_length)
    {
      return gnuradio::get_initial_sptr
        (new filter_frame_cvc_impl(number_of_symbols, symbol_length, guard_interval_length));
    }

    /*
     * The private constructor
     */
    filter_frame_cvc_impl::filter_frame_cvc_impl(int number_of_symbols, int symbol_length,int guard_interval_length)
      : gr::block("filter_frame_cvc",
              gr::io_signature::make2(2, 2, sizeof(gr_complex), sizeof(char)),
              gr::io_signature::make(1, 1, symbol_length*sizeof(gr_complex))),
        d_state_found(false), 
        d_guard_interval_length(guard_interval_length),
        d_symbol_length(symbol_length),
        d_number_of_symbols(number_of_symbols),
        d_itemsize(sizeof(gr_complex))
    {
    	set_tag_propagation_policy(TPP_DONT); 
    	d_input_symbol_length = d_symbol_length + d_guard_interval_length;
    	d_total_output_size   = d_symbol_length*d_number_of_symbols*d_itemsize;
    	d_total_input_size    = (d_symbol_length+d_guard_interval_length)*d_number_of_symbols;
    	set_relative_rate(1/(uint64_t)( d_input_symbol_length)); 
    	
    }

    /*
     * Our virtual destructor.
     */
    filter_frame_cvc_impl::~filter_frame_cvc_impl()
    {
    }

    void
    filter_frame_cvc_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
    	int n = 0;
    	if (!d_state_found)
    	{
    		n = d_input_symbol_length*noutput_items;
    	}
    	else 
    	{
    		n = d_input_symbol_length*d_number_of_symbols;
    	}
    	for (unsigned i = 0; i < ninput_items_required.size(); i++) 
    	{
        	ninput_items_required[i] = n;
    	}
      /* <+forecast+> e.g. ninput_items_required[0] = noutput_items */
    }
    bool
    filter_frame_cvc_impl::check_buffers(int noutput_items_recq, int ninput_items_reqd, int noutput_items, int ninput_items, int nitems_read)
    {
    	if( noutput_items_recq  > noutput_items)
    	{
    		return false; 
    	}
    	if(ninput_items_reqd > (ninput_items-nitems_read))
    	{
    		return false; 
    	}
    	return true;
    }
    
    int 
    filter_frame_cvc_impl::search_trigger_signal(const unsigned char * signal, int max_index)
    { 
    	int result_offset = max_index;
    	for(int offset = 0; offset < max_index; offset++)
    	{
    		if(signal[offset])
    		{
    			result_offset = offset; 
    			break;
    		}
    	}
    	return result_offset; 
    }
    
    void
    filter_frame_cvc_impl::copy_to_output(const unsigned char * in, unsigned char * out)
    {
    	for(int i=0; i <  d_number_of_symbols;  i++)
    	{
            memcpy((void*)out,
                   (void*)(in + d_guard_interval_length * d_itemsize),
                   			d_symbol_length * d_itemsize);
            in += d_itemsize * (d_input_symbol_length);
            out += d_itemsize * d_symbol_length;
    	}
    }
    int
    filter_frame_cvc_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const unsigned char  *in_sample  = (const unsigned char *)  input_items[0];
      const unsigned char  *in_trigger = (const unsigned char *)  input_items[1];
      unsigned char  *out              = (unsigned char *)       output_items[0];
      
      const int ninput  = std::min(ninput_items[0], ninput_items[1]); 
      
      if (!d_state_found)
      {
      	const int trigger_offset = search_trigger_signal(in_trigger, ninput);
      	if( trigger_offset >= ninput)
      	{
      		consume_each(ninput);
      		return 0;  
      	}
      	consume_each(trigger_offset);
      	bool buffers_ready = check_buffers(d_number_of_symbols, d_total_input_size, noutput_items, ninput, trigger_offset );
      	if (buffers_ready)
      	{
      		copy_to_output((const unsigned char *) in_sample+(trigger_offset*d_itemsize),out); 
      		consume_each((d_symbol_length + d_guard_interval_length)*d_number_of_symbols);
      		set_min_noutput_items(1);
      		return d_number_of_symbols; 
      	}
      	d_state_found = true;
      	return 0; 
      }
      bool buffers_ready = check_buffers(d_number_of_symbols, d_total_input_size, noutput_items, ninput, 0 );
      if (buffers_ready)
      {
      		d_state_found = false; 
       		copy_to_output(in_sample,out); 
      		consume_each((d_symbol_length + d_guard_interval_length)*d_number_of_symbols);
      		set_min_noutput_items(1);
      		return d_number_of_symbols;      	
      }
      return 0;      

      // Tell runtime system how many output items we produced.
    }

  } /* namespace ofdmAux */
} /* namespace gr */

