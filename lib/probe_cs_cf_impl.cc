/* -*- c++ -*- */
/* 
 * Copyright 2015 <ARTES Group, Universidad de la República, Uruguay>.
 * http://iie.fing.edu.uy/investigacion/grupos/artes/ingles/index.php3
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

/* CARRIER SUPPRESSION ERROR
 * This block uses mer.cc to calculate the average tx_power, uses the ste.cc to update d_di vector, uses carrier_suppression.cc to calculate the cs error. 
 * Please read first ste.cc and carrier_suppression.cc files.
 * With each new sample updates di,tx power and cs and outs its values. CS is the power of the carrier suppression error normalized to the avergae tx power.
 * Each  d_nsamples send a message with the last cs estimations for the corresponding message port.
 * This class uses demapper.cc class to clasify to the constellation points of the received samples.
 */


#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "probe_cs_cf_impl.h"

namespace gr {
  namespace mer {

    probe_cs_cf::sptr
    probe_cs_cf::make(const std::vector<gr_complex> &symbol_table, double alpha)
    {
      return gnuradio::get_initial_sptr
        (new probe_cs_cf_impl(symbol_table, alpha));
    }

    /*
    * The private constructor
    * Receives the symbol table and the averaging parameter alpha
    * The symbol table is used by the demapper.cc class 
    * The parameter alpha is used by ste.cc class to average d_di vector and mer class to average the tx power 
    */
    probe_cs_cf_impl::probe_cs_cf_impl(const std::vector<gr_complex> &symbol_table, double alpha)
      : gr::sync_block("probe_cs_cf",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(float)))
    {
        d_nsamples = 1000;// number of samples to send a message with MER value
        d_count = 0;// sample's counter
	// filter parameter
	d_alpha = alpha;
	//creates the message port
      	d_cs_port = pmt::string_to_symbol("cs_msg");
      	message_port_register_out(d_cs_port);
      	d_dim_constellation = symbol_table.size();
	// creates the objects
      	d_demapper = new demapper(symbol_table);
        d_ste = new ste(d_dim_constellation,d_alpha);
	d_cs = new carrier_suppression(d_demapper);
	d_mer = new mer(d_alpha);
    }
    /*
     * Our virtual destructor.
     */
    probe_cs_cf_impl::~probe_cs_cf_impl()
    {
    }

    int
    probe_cs_cf_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
	const gr_complex *in = (const gr_complex*)input_items[0];
      	float *cs_out = NULL;
        cs_out = (float *) output_items[0];
	double tx_power;
     	gr_complex iq_true;
	gr_complex *di;
	// constellation value is the constellation point decimal value
      	int constellation_value=0;
	for(int j=0; j < noutput_items; j++) {
	      	iq_true = d_demapper->demap(in[j],constellation_value);
		tx_power = d_mer->update_avg_tx_power(iq_true);
		di = d_ste->update_di(in[j],iq_true,constellation_value);
		cs_out[j] = d_cs->update_cs(tx_power,di);
		d_count ++;
		if(d_count > d_nsamples) {
			// Post a message with the latest CS value
			message_port_pub(d_cs_port, pmt::from_double(cs_out[j]));
			d_count =0;	
        	}
	}
        // Tell runtime system how many output items we produced.
        return noutput_items;
    }

  } /* namespace mer */
} /* namespace gr */

