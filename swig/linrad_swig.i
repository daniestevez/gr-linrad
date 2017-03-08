/* -*- c++ -*- */

#define LINRAD_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "linrad_swig_doc.i"

%{
#include "linrad/send_raw24.h"
%}


%include "linrad/send_raw24.h"
GR_SWIG_BLOCK_MAGIC2(linrad, send_raw24);
