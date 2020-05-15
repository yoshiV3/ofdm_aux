/* -*- c++ -*- */

#define OFDMAUX_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "ofdmAux_swig_doc.i"

%{
#include "ofdmAux/add_zeros_cc.h"
#include "ofdmAux/commit_to_output_bb.h"
#include "ofdmAux/decoder_reed_solomon_bb.h"
#include "ofdmAux/encoder_reed_solomon_bb.h"
#include "ofdmAux/filter_frame_cvc.h"
#include "ofdmAux/insert_sequence_numbers_bb.h"
%}


%include "ofdmAux/add_zeros_cc.h"
GR_SWIG_BLOCK_MAGIC2(ofdmAux, add_zeros_cc);
%include "ofdmAux/commit_to_output_bb.h"
GR_SWIG_BLOCK_MAGIC2(ofdmAux, commit_to_output_bb);
%include "ofdmAux/decoder_reed_solomon_bb.h"
GR_SWIG_BLOCK_MAGIC2(ofdmAux, decoder_reed_solomon_bb);
%include "ofdmAux/encoder_reed_solomon_bb.h"
GR_SWIG_BLOCK_MAGIC2(ofdmAux, encoder_reed_solomon_bb);
%include "ofdmAux/filter_frame_cvc.h"
GR_SWIG_BLOCK_MAGIC2(ofdmAux, filter_frame_cvc);
%include "ofdmAux/insert_sequence_numbers_bb.h"
GR_SWIG_BLOCK_MAGIC2(ofdmAux, insert_sequence_numbers_bb);
