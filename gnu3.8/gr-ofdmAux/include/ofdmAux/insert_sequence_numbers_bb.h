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

#ifndef INCLUDED_OFDMAUX_INSERT_SEQUENCE_NUMBERS_BB_H
#define INCLUDED_OFDMAUX_INSERT_SEQUENCE_NUMBERS_BB_H

#include <ofdmAux/api.h>
#include <gnuradio/sync_interpolator.h>

namespace gr {
  namespace ofdmAux {

    /*!
     * \brief <+description of block+>
     * \ingroup ofdmAux
     *
     */
    class OFDMAUX_API insert_sequence_numbers_bb : virtual public gr::sync_interpolator
    {
     public:
      typedef boost::shared_ptr<insert_sequence_numbers_bb> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of ofdmAux::insert_sequence_numbers_bb.
       *
       * To avoid accidental use of raw pointers, ofdmAux::insert_sequence_numbers_bb's
       * constructor is in a private implementation
       * class. ofdmAux::insert_sequence_numbers_bb::make is the public interface for
       * creating new instances.
       */
      static sptr make();
    };

  } // namespace ofdmAux
} // namespace gr

#endif /* INCLUDED_OFDMAUX_INSERT_SEQUENCE_NUMBERS_BB_H */

