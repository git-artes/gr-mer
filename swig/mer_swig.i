/* -*- c++ -*- */

#define MER_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "mer_swig_doc.i"

%{
#include "mer/probe_mer_c.h"
#include "mer/demapper.h"
#include "mer/mer.h"
#include "mer/probe_ste_cf.h"
#include "mer/ste.h"
#include "mer/probe_cs_cf.h"
#include "mer/carrier_suppression.h"
#include "mer/probe_ai_cf.h"
#include "mer/amplitude_imbalance.h"
#include "mer/probe_qe_cf.h"
#include "mer/quadrature_error.h"
#include "mer/probe_pj_cf.h"
#include "mer/phase_jitter.h"
#include "mer/probe_all_meassurements_cf.h"
%}


%include "mer/probe_mer_c.h"
GR_SWIG_BLOCK_MAGIC2(mer, probe_mer_c);
%include "mer/demapper.h"
%include "mer/mer.h"
%include "mer/probe_ste_cf.h"
GR_SWIG_BLOCK_MAGIC2(mer, probe_ste_cf);
%include "mer/ste.h"
%include "mer/probe_cs_cf.h"
GR_SWIG_BLOCK_MAGIC2(mer, probe_cs_cf);
%include "mer/carrier_suppression.h"
%include "mer/probe_ai_cf.h"
GR_SWIG_BLOCK_MAGIC2(mer, probe_ai_cf);
%include "mer/amplitude_imbalance.h"
%include "mer/probe_qe_cf.h"
GR_SWIG_BLOCK_MAGIC2(mer, probe_qe_cf);
%include "mer/quadrature_error.h"
%include "mer/probe_pj_cf.h"
GR_SWIG_BLOCK_MAGIC2(mer, probe_pj_cf);
%include "mer/phase_jitter.h"
%include "mer/probe_all_meassurements_cf.h"
GR_SWIG_BLOCK_MAGIC2(mer, probe_all_meassurements_cf);
