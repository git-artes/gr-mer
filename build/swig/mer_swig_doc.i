
/*
 * This file was automatically generated using swig_doc.py.
 *
 * Any changes to it will be lost next time it is regenerated.
 */




%feature("docstring") gr::mer::amplitude_imbalance "<+description+>"

%feature("docstring") gr::mer::amplitude_imbalance::amplitude_imbalance "

Params: (demap)"

%feature("docstring") gr::mer::amplitude_imbalance::~amplitude_imbalance "

Params: (NONE)"

%feature("docstring") gr::mer::amplitude_imbalance::update_ai "

Params: (tx_power, di)"

%feature("docstring") gr::mer::carrier_suppression "<+description+>"

%feature("docstring") gr::mer::carrier_suppression::carrier_suppression "

Params: (demap)"

%feature("docstring") gr::mer::carrier_suppression::~carrier_suppression "

Params: (NONE)"

%feature("docstring") gr::mer::carrier_suppression::update_cs "

Params: (tx_power, di)"



%feature("docstring") gr::mer::demapper::max_min_axes "

Params: (NONE)"

%feature("docstring") gr::mer::demapper::demapper "

Params: (map)"

%feature("docstring") gr::mer::demapper::~demapper "

Params: (NONE)"

%feature("docstring") gr::mer::demapper::demap "

Params: (val)"

%feature("docstring") gr::mer::demapper::left_down_contellation "

Params: (decimal_point)"

%feature("docstring") gr::mer::demapper::left_up_contellation "

Params: (decimal_point)"

%feature("docstring") gr::mer::demapper::right_down_contellation "

Params: (decimal_point)"

%feature("docstring") gr::mer::demapper::right_up_contellation "

Params: (decimal_point)"

%feature("docstring") gr::mer::mer "<+description+>"

%feature("docstring") gr::mer::mer::mer "

Params: (alpha)"

%feature("docstring") gr::mer::mer::~mer "

Params: (NONE)"

%feature("docstring") gr::mer::mer::update_mer "

Params: (iq, iq_true)"

%feature("docstring") gr::mer::mer::update_avg_tx_power "

Params: (iq_true)"

%feature("docstring") gr::mer::mer::update_avg_error_power "

Params: (iq, iq_true)"

%feature("docstring") gr::mer::phase_jitter "<+description+>"

%feature("docstring") gr::mer::phase_jitter::phase_jitter "

Params: (dim_constellation, alpha, demap)"

%feature("docstring") gr::mer::phase_jitter::~phase_jitter "

Params: (NONE)"

%feature("docstring") gr::mer::phase_jitter::update_pj "

Params: (iq, cs, ai, qe, tx_power, snr)"

%feature("docstring") gr::mer::probe_ai_cf "<+description of block+>"

%feature("docstring") gr::mer::probe_ai_cf::make "Return a shared_ptr to a new instance of mer::probe_ai_cf.

To avoid accidental use of raw pointers, mer::probe_ai_cf's constructor is in a private implementation class. mer::probe_ai_cf::make is the public interface for creating new instances.

Params: (symbol_table, alpha)"

%feature("docstring") gr::mer::probe_all_meassurements_cf "<+description of block+>"

%feature("docstring") gr::mer::probe_all_meassurements_cf::make "Return a shared_ptr to a new instance of mer::probe_all_meassurements_cf.

To avoid accidental use of raw pointers, mer::probe_all_meassurements_cf's constructor is in a private implementation class. mer::probe_all_meassurements_cf::make is the public interface for creating new instances.

Params: (symbol_table, alpha)"

%feature("docstring") gr::mer::probe_cs_cf "<+description of block+>"

%feature("docstring") gr::mer::probe_cs_cf::make "Return a shared_ptr to a new instance of mer::probe_cs_cf.

To avoid accidental use of raw pointers, mer::probe_cs_cf's constructor is in a private implementation class. mer::probe_cs_cf::make is the public interface for creating new instances.

Params: (symbol_table, alpha)"

%feature("docstring") gr::mer::probe_mer_c "<+description of block+>"

%feature("docstring") gr::mer::probe_mer_c::make "Return a shared_ptr to a new instance of mer::probe_mer_c.

To avoid accidental use of raw pointers, mer::probe_mer_c's constructor is in a private implementation class. mer::probe_mer_c::make is the public interface for creating new instances.

Params: (symbol_table, alpha)"

%feature("docstring") gr::mer::probe_pj_cf "<+description of block+>"

%feature("docstring") gr::mer::probe_pj_cf::make "Return a shared_ptr to a new instance of mer::probe_pj_cf.

To avoid accidental use of raw pointers, mer::probe_pj_cf's constructor is in a private implementation class. mer::probe_pj_cf::make is the public interface for creating new instances.

Params: (symbol_table, alpha)"

%feature("docstring") gr::mer::probe_qe_cf "<+description of block+>"

%feature("docstring") gr::mer::probe_qe_cf::make "Return a shared_ptr to a new instance of mer::probe_qe_cf.

To avoid accidental use of raw pointers, mer::probe_qe_cf's constructor is in a private implementation class. mer::probe_qe_cf::make is the public interface for creating new instances.

Params: (symbol_table, alpha)"

%feature("docstring") gr::mer::probe_ste_cf "<+description of block+>"

%feature("docstring") gr::mer::probe_ste_cf::make "Return a shared_ptr to a new instance of mer::probe_ste_cf.

To avoid accidental use of raw pointers, mer::probe_ste_cf's constructor is in a private implementation class. mer::probe_ste_cf::make is the public interface for creating new instances.

Params: (symbol_table, alpha)"

%feature("docstring") gr::mer::quadrature_error "<+description+>"

%feature("docstring") gr::mer::quadrature_error::quadrature_error "

Params: (dim_constellation, alpha, demap)"

%feature("docstring") gr::mer::quadrature_error::~quadrature_error "

Params: (NONE)"

%feature("docstring") gr::mer::quadrature_error::update_qe "

Params: (tx_power, di, angleh, anglev)"

%feature("docstring") gr::mer::ste "<+description+>"

%feature("docstring") gr::mer::ste::ste "

Params: (dim_constellation, alpha)"

%feature("docstring") gr::mer::ste::~ste "

Params: (NONE)"

%feature("docstring") gr::mer::ste::update_ste "

Params: (iq, iq_true, constellation_value)"

%feature("docstring") gr::mer::ste::update_stem "

Params: (iq, iq_true, constellation_value, tx_power)"

%feature("docstring") gr::mer::ste::update_sted "

Params: (iq, iq_true, constellation_value, tx_power)"

%feature("docstring") gr::mer::ste::update_di "

Params: (iq, iq_true, constellation_value)"