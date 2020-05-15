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

#ifndef INCLUDED_OFDMAUX_ADD_ZEROS_CC_H
#define INCLUDED_OFDMAUX_ADD_ZEROS_CC_H

#include <ofdmAux/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace ofdmAux {

    /*!
     * \brief <+description of block+>
     * \ingroup ofdmAux
     *
     */
    class OFDMAUX_API add_zeros_cc : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<add_zeros_cc> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of ofdmAux::add_zeros_cc.
       *
       * To avoid accidental use of raw pointers, ofdmAux::add_zeros_cc's
       * constructor is in a private implementation
       * class. ofdmAux::add_zeros_cc::make is the public interface for
       * creating new instances.
       */
      static sptr make(int nb_z_frames, int frame_length);
    };

  } // namespace ofdmAux
} // namespace gr

#endif /* INCLUDED_OFDMAUX_ADD_ZEROS_CC_H */

