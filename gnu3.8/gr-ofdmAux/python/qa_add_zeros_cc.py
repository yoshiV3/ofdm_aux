#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Copyright 2020 Yoshi Vermeire.
#
# This is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this software; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
#

from gnuradio import gr, gr_unittest
from gnuradio import blocks
import ofdmAux_swig as ofdmAux

class qa_add_zeros_cc(gr_unittest.TestCase):

    def setUp(self):
        self.tb = gr.top_block()

    def tearDown(self):
        self.tb = None

    def test_001_t(self):
        frame_length    = 4
        nb_of_z_frames  = 2
        data_source     = [1]*frame_length
        expected_data   = [0]*(nb_of_z_frames*frame_length) + [1]*frame_length + [0]*(nb_of_z_frames*frame_length)
        data_src        = blocks.vector_source_c(data_source, False)
        burst_shaper    = ofdmAux.add_zeros_cc(nb_of_z_frames,frame_length)
        destination     = blocks.vector_sink_c(1)
        self.tb.connect(data_src,burst_shaper)
        self.tb.connect(burst_shaper, destination)
        self.tb.run()
        dest_data = destination.data()
        self.assertEqual(len(dest_data), frame_length*(2*nb_of_z_frames+1))
        # check data
        self.assertEqual(len(dest_data), len(expected_data))
        for recv_sample in range(len(dest_data)):
                self.assertEqual(expected_data[recv_sample], dest_data[recv_sample])
    def test_multiple_frames_001_t(self):
        frame_length    = 4
        nb_of_z_frames  = 2
        repetions       = 100
        data_source     = [1]*frame_length*repetions
        exp             = [0]*(nb_of_z_frames*frame_length) +[1]*frame_length + [0]*(nb_of_z_frames*frame_length)
        expected_data   = []
        for i in range(repetions):
        	expected_data = expected_data + exp
        data_src        = blocks.vector_source_c(data_source, False)
        burst_shaper    = ofdmAux.add_zeros_cc(nb_of_z_frames,frame_length)
        destination     = blocks.vector_sink_c(1)
        self.tb.connect(data_src,burst_shaper)
        self.tb.connect(burst_shaper, destination)
        self.tb.run()
        dest_data = destination.data()
        self.assertEqual(len(dest_data), repetions*frame_length*(2*nb_of_z_frames+1))
        # check data
        self.assertEqual(len(dest_data), len(expected_data))
        for recv_sample in range(len(dest_data)):
                self.assertEqual(expected_data[recv_sample], dest_data[recv_sample])
    def test_other_numbers_001_t(self):
        frame_length    = 15
        nb_of_z_frames  = 23
        data_source     = [1]*frame_length
        expected_data   = [0]*(nb_of_z_frames*frame_length) + [1]*frame_length + [0]*(nb_of_z_frames*frame_length)
        data_src        = blocks.vector_source_c(data_source, False)
        burst_shaper    = ofdmAux.add_zeros_cc(nb_of_z_frames,frame_length)
        destination     = blocks.vector_sink_c(1)
        self.tb.connect(data_src,burst_shaper)
        self.tb.connect(burst_shaper, destination)
        self.tb.run()
        dest_data = destination.data()
        self.assertEqual(len(dest_data), frame_length*(2*nb_of_z_frames+1))
        # check data
        self.assertEqual(len(dest_data), len(expected_data))
        for recv_sample in range(len(dest_data)):
                self.assertEqual(expected_data[recv_sample], dest_data[recv_sample])
if __name__ == '__main__':
    gr_unittest.run(qa_add_zeros_cc)
