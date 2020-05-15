#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 
# Copyright 2020 <+YOU OR YOUR COMPANY+>.
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

class qa_decoder_reed_solomon_bb (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t(self):
        msg             = [207,3,146,199,185,206]
        data_src        = blocks.vector_source_b(msg, False)
        decoder         = ofdmAux.decoder_reed_solomon_bb()
        destination     = blocks.vector_sink_b(1)
        correctness   = blocks.vector_sink_b(1)
        self.tb.connect(data_src, (decoder,0), destination)
        self.tb.connect((decoder,1),correctness)
        self.tb.run()
        expected_result = [207,146,185]
        result          = destination.data()
        self.assertEqual(len(expected_result), len(result))
        for answer in range(len(expected_result)):
        	self.assertEqual(expected_result[answer], result[answer])
        result = correctness.data()
        self.assertEqual(len(expected_result), len(result))
        for answer in range(len(expected_result)):
        	self.assertEqual(1, result[answer])
        	
    def test_correction_001_t(self):
        msg             = [206,3,146,200,185,207]
        data_src        = blocks.vector_source_b(msg, False)
        decoder         = ofdmAux.decoder_reed_solomon_bb()
        destination     = blocks.vector_sink_b(1)
        correctness   = blocks.vector_sink_b(1)
        self.tb.connect(data_src, (decoder,0), destination)
        self.tb.connect((decoder,1),correctness)
        self.tb.run()
        expected_result = [207,146,185]
        result          = destination.data()
        self.assertEqual(len(expected_result), len(result))
        for answer in range(len(expected_result)):
        	self.assertEqual(expected_result[answer], result[answer])
        result = correctness.data()
        self.assertEqual(len(expected_result), len(result))
        for answer in range(len(expected_result)):
        	self.assertEqual(1, result[answer])         
    def test_no_correction_001_t(self):
        msg             =  [30,3,0,199,0,206]
        data_src        = blocks.vector_source_b(msg, False)
        decoder         = ofdmAux.decoder_reed_solomon_bb()
        destination     = blocks.vector_sink_b(1)
        correctness   = blocks.vector_sink_b(1)
        self.tb.connect(data_src, (decoder,0), destination)
        self.tb.connect((decoder,1),correctness)
        self.tb.run()
        expected_result = [30,0,0]
        result          = destination.data()
        self.assertEqual(len(expected_result), len(result))
        for answer in range(len(expected_result)):
        	self.assertEqual(expected_result[answer], result[answer])
        result = correctness.data()
        self.assertEqual(len(expected_result), len(result))
        for answer in range(len(expected_result)):
        	self.assertEqual(0, result[answer]) 


if __name__ == '__main__':
    gr_unittest.run(qa_decoder_reed_solomon_bb, "qa_decoder_reed_solomon_bb.xml")
