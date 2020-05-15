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

#ifndef INCLUDED_OFDMAUX_FILTER_FRAME_CVC_IMPL_H
#define INCLUDED_OFDMAUX_FILTER_FRAME_CVC_IMPL_H

#include <ofdmAux/filter_frame_cvc.h>

namespace gr {
  namespace ofdmAux {

    class filter_frame_cvc_impl : public filter_frame_cvc
    {
     private:
      size_t d_itemsize;
      bool   d_state_found; 
      size_t d_input_symbol_length; 
      int    d_number_of_symbols; 
      int    d_symbol_length; 
      int    d_guard_interval_length;
      int    d_total_output_size;
      int    d_total_input_size;
      int    search_trigger_signal(const unsigned char * signal, int max_index); 
      bool    check_buffers(int noutput_items_recq, int ninput_items_reqd, int noutput_items, int ninput_items, int nitems_read);
      void   copy_to_output(const unsigned char * in, unsigned char * out); 

     public:
      filter_frame_cvc_impl(int number_of_symbols, int symbol_length, int guard_interval);
      ~filter_frame_cvc_impl();

      // Where all the action really happens
      void forecast (int noutput_items, gr_vector_int &ninput_items_required);

      int general_work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);

    };

  } // namespace ofdmAux
} // namespace gr

#endif /* INCLUDED_OFDMAUX_FILTER_FRAME_CVC_IMPL_H */

