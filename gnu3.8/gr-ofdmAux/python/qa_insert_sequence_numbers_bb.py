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

class qa_insert_sequence_numbers_bb(gr_unittest.TestCase):

    def setUp(self):
        self.tb = gr.top_block()

    def tearDown(self):
        self.tb = None

    def test_001_t(self):
        msg             = [x for x in range(256)] + [x for x in range(256)]
        data_src        = blocks.vector_source_b(msg, False)
        encoder         = ofdmAux.insert_sequence_numbers_bb()
        destination     = blocks.vector_sink_b(1)
        self.tb.connect(data_src, encoder, destination)
        self.tb.run()
        result = destination.data()
        self.assertEqual(len(result), 2*(256*2))
        for i in range(2*256):
        	self.assertEqual(result[2*i], result[2*i+1])
        # check data


if __name__ == '__main__':
    gr_unittest.run(qa_insert_sequence_numbers_bb)
