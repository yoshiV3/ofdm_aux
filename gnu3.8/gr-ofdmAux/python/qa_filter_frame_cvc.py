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

class qa_filter_frame_cvc(gr_unittest.TestCase):

    def setUp(self):
        self.tb = gr.top_block()

    def tearDown(self):
        self.tb = None

    def test_001_t(self):
        # set up fg
        nb_sym         = 3
        symb_length    = 2
        guard_interval = 2
        payload_length = nb_sym*(symb_length+guard_interval)
        pre_length     = 12
        trigger_signal = [0]*pre_length + [1] + [0]*(payload_length -1)
        data_source    = [x for x in range(payload_length + pre_length)]
        trigger_src    = blocks.vector_source_b(trigger_signal, False)
        data_src       = blocks.vector_source_c(data_source, False)
        discovery      = ofdmAux.filter_frame_cvc(nb_sym, symb_length, guard_interval)
        destination    = blocks.vector_sink_c(symb_length)
        self.tb.connect(data_src,(discovery,0))
        self.tb.connect(trigger_src,(discovery,1))
        self.tb.connect(discovery, destination)
        print("test one")
        self.tb.run()
        received     = destination.data()
        # check data
        expected_data = [14,15,18,19,22,23]
        self.assertEqual(len(received), nb_sym*symb_length)
        for recv_sample in range(nb_sym*symb_length):
                self.assertEqual(expected_data[recv_sample], received[recv_sample])
    def test_001_two_blocks(self):
        print('test two')
        # set up fg
        nb_sym         = 3
        symb_length    = 2
        guard_interval = 2
        payload_length = nb_sym*(symb_length+guard_interval)
        pre_length     = 12
        trigger_signal = [0]*pre_length + [1] + [0]*(payload_length -1) + [1] +  [0]*(payload_length -1) 
        data_source    = [x for x in range(2*payload_length + pre_length)]
        trigger_src    = blocks.vector_source_b(trigger_signal, False)
        data_src       = blocks.vector_source_c(data_source, False)
        discovery      = ofdmAux.filter_frame_cvc(nb_sym, symb_length, guard_interval)
        destination    = blocks.vector_sink_c(symb_length)
        self.tb.connect(data_src,(discovery,0))
        self.tb.connect(trigger_src,(discovery,1))
        self.tb.connect(discovery, destination)
        self.tb.run()
        received     = destination.data()
        # check data
        expected_data = [14,15,18,19,22,23,26,27,30,31,34,35]
        self.assertEqual(len(received), 2*nb_sym*symb_length)
        for recv_sample in range(2*nb_sym*symb_length):
                self.assertEqual(expected_data[recv_sample], received[recv_sample])
    def test_001_two_blocks_with_space(self):
        # set up fg
        nb_sym         = 3
        symb_length    = 2
        guard_interval = 2
        payload_length = nb_sym*(symb_length+guard_interval)
        pre_length     = 12
        trigger_signal = [0]*pre_length + [1] + [0]*(payload_length -1) + [0]*pre_length + [1] +  [0]*(payload_length -1) 
        data_source    = [x for x in range(2*payload_length + 2*pre_length)]
        trigger_src    = blocks.vector_source_b(trigger_signal, False)
        data_src       = blocks.vector_source_c(data_source, False)
        discovery      = ofdmAux.filter_frame_cvc(nb_sym, symb_length, guard_interval)
        destination    = blocks.vector_sink_c(symb_length)
        self.tb.connect(data_src,(discovery,0))
        self.tb.connect(trigger_src,(discovery,1))
        self.tb.connect(discovery, destination)
        self.tb.run()
        received     = destination.data()
        # check data
        expected_data = [14,15,18,19,22,23,38,39,42,43,46,47]
        self.assertEqual(len(received), 2*nb_sym*symb_length)
        for recv_sample in range(2*nb_sym*symb_length):
                self.assertEqual(expected_data[recv_sample], received[recv_sample])


if __name__ == '__main__':
    gr_unittest.run(qa_filter_frame_cvc)
