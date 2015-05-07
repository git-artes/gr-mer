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


/* SYSTEM TARGET ERROR
 * This block uses mer.cc to calculate the average tx_power, uses the ste.cc to update d_di vector and to calculate the ste, stem and sted as defined in ste.cc. Please read first ste.cc file.
 * With each new sample updates STE,STEM,STED and outs its values, the block has one input float and three output flows.
 * Each  d_nsamples send a message with the last STE,STEM,STED estimations for the corresponding messages ports.
 * This class uses demapper.cc class to clasify to the constellation points of the received samples.
 */


#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "probe_ste_cf_impl.h"

namespace gr {
  namespace mer {

    probe_ste_cf::sptr
    probe_ste_cf::make(const std::vector<gr_complex> &symbol_table, double alpha)
    {
      return gnuradio::get_initial_sptr
        (new probe_ste_cf_impl(symbol_table, alpha));
    }

   /*
    * The private constructor
    * Receives the symbol table and the averaging parameter alpha
    * The symbol table is used by the demapper.cc class 
    * The parameter alpha is used by ste.cc class to average d_di vector  
    */
    probe_ste_cf_impl::probe_ste_cf_impl(const std::vector<gr_complex> &symbol_table, double alpha)
      : gr::sync_block("probe_ste_cf",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(3, 3, sizeof(float)))
    {
        d_nsamples = 1000;// number of samples to send a message with STE,STEM and STED values
        d_count = 0;// sample's counter
	// filter parameter passed to ste.cc to average the d_di vector
	d_alpha = alpha;
	// create the messages ports
      	d_ste_port = pmt::string_to_symbol("ste_msg");
      	message_port_register_out(d_ste_port);
	d_stem_port = pmt::string_to_symbol("stem_msg");
      	message_port_register_out(d_stem_port);
	d_sted_port = pmt::string_to_symbol("sted_msg");
      	message_port_register_out(d_sted_port);
	// creates the demapper, ste and mer objects
      	d_dim_constellation = symbol_table.size();
      	d_demapper = new demapper(symbol_table);
        d_ste = new ste(d_dim_constellation,d_alpha);
	d_mer = new mer(d_alpha);
    }

    /*
     * Our virtual destructor.
     */
    probe_ste_cf_impl::~probe_ste_cf_impl()
    {
    }

    int
    probe_ste_cf_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
	const gr_complex *in = (const gr_complex*)input_items[0];
      	float *ste_out = NULL,*stem_out = NULL,*sted_out = NULL;
        ste_out = (float *) output_items[0];
        stem_out = (float *) output_items[1];
        sted_out = (float *) output_items[2];
	double tx_power;
     	gr_complex iq_true;
	// constellation value is the constellation point decimal value
      	int constellation_value=0;
	for(int j=0; j < noutput_items; j++) {
		// for each sample calculate the iq_true and the corresponding decimal point of the constellation
	      	iq_true = d_demapper->demap(in[j],constellation_value);
		// estimate the average tx power
		tx_power = d_mer->update_avg_tx_power(iq_true);
		ste_out[j] = d_ste->update_ste(in[j],iq_true,constellation_value);
		stem_out[j] = d_ste->update_stem(in[j],iq_true,constellation_value,tx_power);
		sted_out[j] = d_ste->update_sted(in[j],iq_true,constellation_value,tx_power);
		d_count ++;
		if(d_count > d_nsamples) {
			// Post a message with the latest STE,STEM, STED values
			message_port_pub(d_ste_port, pmt::from_double(ste_out[j]));
			message_port_pub(d_stem_port, pmt::from_double(stem_out[j] ));
			message_port_pub(d_sted_port, pmt::from_double(sted_out[j] ));

			d_count =0;	
        	}
	}
        // Tell runtime system how many output items we produced.
        return noutput_items;
    }


	
  } /* namespace mer */
} /* namespace gr */

