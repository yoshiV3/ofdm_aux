# Copyright 2011 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.

install(FILES
    ofdmAux_add_zeros_cc.xml
    ofdmAux_commit_to_output_bb.xml
    ofdmAux_decoder_reed_solomon_bb.xml
    ofdmAux_encoder_reed_solomon_bb.xml
    ofdmAux_filter_frame_cvc.xml
    ofdmAux_insert_sequence_numbers_bb.xml DESTINATION share/gnuradio/grc/blocks
)
