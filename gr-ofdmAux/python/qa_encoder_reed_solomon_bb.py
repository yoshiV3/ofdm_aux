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

class qa_encoder_reed_solomon_bb(gr_unittest.TestCase):

    def setUp(self):
        self.tb = gr.top_block()

    def tearDown(self):
        self.tb = None

    def test_001_t(self):
        msg             = [(12<<4) + 15, (9<<4)+2,(11<<4)+9]
        data_src        = blocks.vector_source_b(msg, False)
        encoder         = ofdmAux.encoder_reed_solomon_bb()
        destination     = blocks.vector_sink_b(1)
        self.tb.connect(data_src, encoder, destination)
        self.tb.run()
        expected_result = [207,3,146,199,185,206]
        result          = destination.data()
        self.assertEqual(len(expected_result), len(result))
        for answer in range(len(expected_result)):
        	self.assertEqual(expected_result[answer], result[answer])
        #self.tb.run()
        # check data


if __name__ == '__main__':
    gr_unittest.run(qa_encoder_reed_solomon_bb)
