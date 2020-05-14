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

#ifndef INCLUDED_OFDMAUX_FILTER_FRAME_CVC_H
#define INCLUDED_OFDMAUX_FILTER_FRAME_CVC_H

#include <ofdmAux/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace ofdmAux {

    /*!
     * \brief <+description of block+>
     * \ingroup ofdmAux
     *
     */
    class OFDMAUX_API filter_frame_cvc : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<filter_frame_cvc> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of ofdmAux::filter_frame_cvc.
       *
       * To avoid accidental use of raw pointers, ofdmAux::filter_frame_cvc's
       * constructor is in a private implementation
       * class. ofdmAux::filter_frame_cvc::make is the public interface for
       * creating new instances.
       */
      static sptr make(int number_of_symbols, int symbol_length, int guard_interval);
    };

  } // namespace ofdmAux
} // namespace gr

#endif /* INCLUDED_OFDMAUX_FILTER_FRAME_CVC_H */

