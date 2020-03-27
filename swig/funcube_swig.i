/* -*- c++ -*- */

#define FUNCUBE_API

%include "gnuradio.i"           // the common stuff

//load generated python docstrings
%include "funcube_swig_doc.i"

%{
#include "funcube/fcd.h"
%}

%include "funcube/fcd.h"
GR_SWIG_BLOCK_MAGIC2(funcube, fcd);
