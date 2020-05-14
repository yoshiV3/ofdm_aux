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

class qa_commit_to_output_bb(gr_unittest.TestCase):

    def setUp(self):
        self.tb = gr.top_block()

    def tearDown(self):
        self.tb = None

    def test_all_correct_001_t(self):
        data_source     = [0,1,1,2,2,3]
        data_src        = blocks.vector_source_b(data_source, False)
        state_source    = [1,1,1,1,1,1]
        state_src       = blocks.vector_source_b(state_source, False)
        commit_unit     = ofdmAux.commit_to_output_bb()
        destination     = blocks.vector_sink_b(1)
        self.tb.connect(data_src,(commit_unit,0),destination)
        self.tb.connect(state_src,(commit_unit,1))
        self.tb.run()
        result = destination.data()
        self.assertEqual(len(result), 3)
        expected_result = [1,2,3]
        for index in range(3):
        	self.assertEqual(result[index], expected_result[index])
    def test_start_with_drop_001_t(self):
        data_source     = [3,1,4,2,5,3]
        data_src        = blocks.vector_source_b(data_source, False)
        state_source    = [1,1,1,1,1,1]
        state_src       = blocks.vector_source_b(state_source, False)
        commit_unit     = ofdmAux.commit_to_output_bb()
        destination     = blocks.vector_sink_b(1)
        self.tb.connect(data_src,(commit_unit,0),destination)
        self.tb.connect(state_src,(commit_unit,1))
        self.tb.run()
        result = destination.data()
        self.assertEqual(len(result), 3+3)
        expected_result = [0,0,0,1,2,3]
        for index in range(3+3):
        	self.assertEqual(result[index], expected_result[index])
    def test_intermediate_drop_001_t(self):
        data_source     = [0,1,1,2,5,3]
        data_src        = blocks.vector_source_b(data_source, False)
        state_source    = [1,1,1,1,1,1]
        state_src       = blocks.vector_source_b(state_source, False)
        commit_unit     = ofdmAux.commit_to_output_bb()
        destination     = blocks.vector_sink_b(1)
        self.tb.connect(data_src,(commit_unit,0),destination)
        self.tb.connect(state_src,(commit_unit,1))
        self.tb.run()
        result = destination.data()
        self.assertEqual(len(result), 3+3)
        expected_result = [1,2,0,0,0,3]
        for index in range(3+3):
        	self.assertEqual(result[index], expected_result[index])
    def test_error_start_drop_001_t(self):
        data_source     = [0,1,1,2,2,3]
        data_src        = blocks.vector_source_b(data_source, False)
        state_source    = [0,0,1,1,1,1]
        state_src       = blocks.vector_source_b(state_source, False)
        commit_unit     = ofdmAux.commit_to_output_bb()
        destination     = blocks.vector_sink_b(1)
        self.tb.connect(data_src,(commit_unit,0),destination)
        self.tb.connect(state_src,(commit_unit,1))
        self.tb.run()
        result = destination.data()
        self.assertEqual(len(result), 3)
        expected_result = [0,2,3]
        for index in range(3):
        	self.assertEqual(result[index], expected_result[index])
    def test_error_d_001_t(self):
        data_source     = [0,1,1,2,2,3]
        data_src        = blocks.vector_source_b(data_source, False)
        state_source    = [0,0,0,0,1,1]
        state_src       = blocks.vector_source_b(state_source, False)
        commit_unit     = ofdmAux.commit_to_output_bb()
        destination     = blocks.vector_sink_b(1)
        self.tb.connect(data_src,(commit_unit,0),destination)
        self.tb.connect(state_src,(commit_unit,1))
        self.tb.run()
        result = destination.data()
        self.assertEqual(len(result), 3)
        expected_result = [0,0,3]
        for index in range(3):
        	self.assertEqual(result[index], expected_result[index])
    def test_error_c_drop_001_t(self):
        data_source     = [0,1,1,2,2,3]
        data_src        = blocks.vector_source_b(data_source, False)
        state_source    = [1,1,0,0,1,1]
        state_src       = blocks.vector_source_b(state_source, False)
        commit_unit     = ofdmAux.commit_to_output_bb()
        destination     = blocks.vector_sink_b(1)
        self.tb.connect(data_src,(commit_unit,0),destination)
        self.tb.connect(state_src,(commit_unit,1))
        self.tb.run()
        result = destination.data()
        self.assertEqual(len(result), 3)
        expected_result = [1,0,3]
        for index in range(3):
        	self.assertEqual(result[index], expected_result[index])
    def test_error_bis_001_t(self):
        data_source     = [0,1,1,2,3,3]
        data_src        = blocks.vector_source_b(data_source, False)
        state_source    = [1,1,0,0,1,1]
        state_src       = blocks.vector_source_b(state_source, False)
        commit_unit     = ofdmAux.commit_to_output_bb()
        destination     = blocks.vector_sink_b(1)
        self.tb.connect(data_src,(commit_unit,0),destination)
        self.tb.connect(state_src,(commit_unit,1))
        self.tb.run()
        result = destination.data()
        self.assertEqual(len(result), 4)
        expected_result = [1,0,0,3]
        for index in range(4):
        	self.assertEqual(result[index], expected_result[index])
    def test_error_001_t(self):
        data_source     = [0,1,2,2,3,3]
        data_src        = blocks.vector_source_b(data_source, False)
        state_source    = [1,1,1,1,0,0]
        state_src       = blocks.vector_source_b(state_source, False)
        commit_unit     = ofdmAux.commit_to_output_bb()
        destination     = blocks.vector_sink_b(1)
        self.tb.connect(data_src,(commit_unit,0),destination)
        self.tb.connect(state_src,(commit_unit,1))
        self.tb.run()
        result = destination.data()
        self.assertEqual(len(result), 3)
        expected_result = [1,0,2]
        for index in range(3):
        	self.assertEqual(result[index], expected_result[index])
    def test_er_001_t(self):
        data_source     = [0,1,1,2,2,3,3,4]
        data_src        = blocks.vector_source_b(data_source, False)
        state_source    = [1,1,0,0,0,0,1,1]
        state_src       = blocks.vector_source_b(state_source, False)
        commit_unit     = ofdmAux.commit_to_output_bb()
        destination     = blocks.vector_sink_b(1)
        self.tb.connect(data_src,(commit_unit,0),destination)
        self.tb.connect(state_src,(commit_unit,1))
        self.tb.run()
        result = destination.data()
        self.assertEqual(len(result), 4)
        expected_result = [1,0,0,4]
        for index in range(4):
        	self.assertEqual(result[index], expected_result[index])
    def test_mix_001_t(self):
        data_source     = [0,1,1,2,2,3]
        data_src        = blocks.vector_source_b(data_source, False)
        state_source    = [1,1,1,0,1,1]
        state_src       = blocks.vector_source_b(state_source, False)
        commit_unit     = ofdmAux.commit_to_output_bb()
        destination     = blocks.vector_sink_b(1)
        self.tb.connect(data_src,(commit_unit,0),destination)
        self.tb.connect(state_src,(commit_unit,1))
        self.tb.run()
        result = destination.data()
        self.assertEqual(len(result), 3)
        expected_result = [1,2,3]
        for index in range(3):
        	self.assertEqual(result[index], expected_result[index])
    def test_mix2_001_t(self):
        data_source     = [0,1,1,2,2,3]
        data_src        = blocks.vector_source_b(data_source, False)
        state_source    = [1,1,0,1,1,1]
        state_src       = blocks.vector_source_b(state_source, False)
        commit_unit     = ofdmAux.commit_to_output_bb()
        destination     = blocks.vector_sink_b(1)
        self.tb.connect(data_src,(commit_unit,0),destination)
        self.tb.connect(state_src,(commit_unit,1))
        self.tb.run()
        result = destination.data()
        self.assertEqual(len(result), 3)
        expected_result = [1,2,3]
        for index in range(3):
        	self.assertEqual(result[index], expected_result[index])
    def test_mix3_001_t(self):
        data_source     = [0,1,1,2,2,3]
        data_src        = blocks.vector_source_b(data_source, False)
        state_source    = [0,1,1,1,1,1]
        state_src       = blocks.vector_source_b(state_source, False)
        commit_unit     = ofdmAux.commit_to_output_bb()
        destination     = blocks.vector_sink_b(1)
        self.tb.connect(data_src,(commit_unit,0),destination)
        self.tb.connect(state_src,(commit_unit,1))
        self.tb.run()
        result = destination.data()
        self.assertEqual(len(result), 3)
        expected_result = [1,2,3]
        for index in range(3):
        	self.assertEqual(result[index], expected_result[index])
    def test_mix4_001_t(self):
        data_source     = [0,1,1,2,2,3]
        data_src        = blocks.vector_source_b(data_source, False)
        state_source    = [1,1,1,1,0,1]
        state_src       = blocks.vector_source_b(state_source, False)
        commit_unit     = ofdmAux.commit_to_output_bb()
        destination     = blocks.vector_sink_b(1)
        self.tb.connect(data_src,(commit_unit,0),destination)
        self.tb.connect(state_src,(commit_unit,1))
        self.tb.run()
        result = destination.data()
        self.assertEqual(len(result), 3)
        expected_result = [1,2,3]
        for index in range(3):
        	self.assertEqual(result[index], expected_result[index])
    def test_mix5_001_t(self):
        data_source     = [0,1,1,2,2,3]
        data_src        = blocks.vector_source_b(data_source, False)
        state_source    = [1,1,1,1,1,0]
        state_src       = blocks.vector_source_b(state_source, False)
        commit_unit     = ofdmAux.commit_to_output_bb()
        destination     = blocks.vector_sink_b(1)
        self.tb.connect(data_src,(commit_unit,0),destination)
        self.tb.connect(state_src,(commit_unit,1))
        self.tb.run()
        result = destination.data()
        self.assertEqual(len(result), 3)
        expected_result = [1,2,3]
        for index in range(3):
        	self.assertEqual(result[index], expected_result[index])
    def test_noise_001_t(self):
        data_source     = [9,9,9,9,9,9,9,9,0,1,1,2,2,3]
        data_src        = blocks.vector_source_b(data_source, False)
        state_source    = [0,0,0,0,0,0,0,0,1,1,1,1,1,1]
        state_src       = blocks.vector_source_b(state_source, False)
        commit_unit     = ofdmAux.commit_to_output_bb()
        destination     = blocks.vector_sink_b(1)
        self.tb.connect(data_src,(commit_unit,0),destination)
        self.tb.connect(state_src,(commit_unit,1))
        self.tb.run()
        result = destination.data()
        self.assertEqual(len(result), 3)
        expected_result = [1,2,3]
        for index in range(3):
        	self.assertEqual(result[index], expected_result[index])
    def test_noise_and_drop__001_t(self):
        data_source     = [9,9,9,9,9,9,9,9,1,1,2,2,3,3]
        data_src        = blocks.vector_source_b(data_source, False)
        state_source    = [0,0,0,0,0,0,0,0,1,1,1,1,1,1]
        state_src       = blocks.vector_source_b(state_source, False)
        commit_unit     = ofdmAux.commit_to_output_bb()
        destination     = blocks.vector_sink_b(1)
        self.tb.connect(data_src,(commit_unit,0),destination)
        self.tb.connect(state_src,(commit_unit,1))
        self.tb.run()
        result = destination.data()
        self.assertEqual(len(result), 4)
        expected_result = [0,1,2,3]
        for index in range(4):
        	self.assertEqual(result[index], expected_result[index])
if __name__ == '__main__':
    gr_unittest.run(qa_commit_to_output_bb)
