/* -*- c++ -*- */

#define FUNCUBE_API

%include "gnuradio.i"           // the common stuff

//load generated python docstrings
%include "funcube_swig_doc.i"

%{
#include "funcube/fcd.h"
#include "funcube/fcd_control.h"
#include "funcube/fcdpp.h"
#include "funcube/fcdpp_control.h"
%}

%include "funcube/fcd.h"
GR_SWIG_BLOCK_MAGIC2(funcube, fcd);
%include "funcube/fcd_control.h"
GR_SWIG_BLOCK_MAGIC2(funcube, fcd_control);
%include "funcube/fcdpp.h"
GR_SWIG_BLOCK_MAGIC2(funcube, fcdpp);
%include "funcube/fcdpp_control.h"
GR_SWIG_BLOCK_MAGIC2(funcube, fcdpp_control);
