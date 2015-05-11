/* -*- c++ -*- */
/* 
 * Copyright 2015
 * Pablo Belzarena <belza@fing.edu.uy>, Gabriel Gomez,  Victor Gonzalez-Barbone, Pablo Flores Guridi, Federico Larroca. 
 * ARTES Group
 * http://iie.fing.edu.uy/investigacion/grupos/artes/ingles/index.php3
 * Instituto de Ingenieria Electrica, Facultad de Ingenieria,
 * Universidad de la Republica, Uruguay.
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



/* AMPLITUDE IMBALANCE ERROR
 * This block uses mer.cc to calculate the average tx_power, uses the ste.cc to update d_di vector, uses amplitude_imbalance.cc to calculate the ai error. 
 * Please read first ste.cc and amplitude_imbalance.cc files.
 * With each new sample updates di,tx power and the ai error in the real  and imaginary axes and outs its values. This block has two outputs the ai error over the real and imaginary axes.
 * AI is the real part and the imaginary part of the expansion or contraction vector applied to the constellation.
 * Each  d_nsamples sends a message with the last ai estimations for the corresponding message port.
 * This class uses demapper.cc class to clasify to the constellation points of the received samples.
 */


#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "probe_ai_cf_impl.h"

namespace gr {
  namespace mer {

    probe_ai_cf::sptr
    probe_ai_cf::make(const std::vector<gr_complex> &symbol_table, double alpha)
    {
      return gnuradio::get_initial_sptr
        (new probe_ai_cf_impl(symbol_table, alpha));
    }

 /*
    * The private constructor
    * Receives the symbol table and the averaging parameter alpha
    * The symbol table is used by the demapper.cc class 
    * The parameter alpha is used by ste.cc class to average d_di vector and mer class to average the tx power 
    */
    probe_ai_cf_impl::probe_ai_cf_impl(const std::vector<gr_complex> &symbol_table, double alpha)
      : gr::sync_block("probe_ai_cf",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(2, 2, sizeof(float)))
    {
        d_nsamples = 1000;// number of samples to send a message with MER value
        d_count = 0;// sample's counter
	// filter parameter to average the di vector in ste object and the tx power.
	d_alpha = alpha;
	// create the message port to send the ai error (complex)
      	d_ai_port = pmt::string_to_symbol("ai_msg");
      	message_port_register_out(d_ai_port);
	// create the objects that are necessary to update the measures
      	d_dim_constellation = symbol_table.size();
      	d_demapper = new demapper(symbol_table);
        d_ste = new ste(d_dim_constellation,d_alpha);
	d_ai = new amplitude_imbalance(d_demapper);
	d_mer = new mer(d_alpha);
     }
    /*
     * Our virtual destructor.
     */
    probe_ai_cf_impl::~probe_ai_cf_impl()
    {
    }

    int
    probe_ai_cf_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
 	const gr_complex *in = (const gr_complex*)input_items[0];
      	float *ai_real_out = NULL,*ai_imag_out = NULL;
        ai_real_out = (float *) output_items[0];
        ai_imag_out = (float *) output_items[1];

	double tx_power;
     	gr_complex iq_true, ai;
	gr_complex *di;
	// constellation value is the constellation point decimal value
      	int constellation_value=0;
	for(int j=0; j < noutput_items; j++) {
	      	iq_true = d_demapper->demap(in[j],constellation_value);
		tx_power = d_mer->update_avg_tx_power(iq_true);
		di = d_ste->update_di(in[j],iq_true,constellation_value);
		ai = d_ai->update_ai(tx_power,di);
		ai_real_out[j] = real(ai);
		ai_imag_out[j] = imag(ai);
		d_count ++;
		if(d_count > d_nsamples) {
			// Post a message with the latest AI error value
			message_port_pub(d_ai_port, pmt::from_complex(ai));
			d_count =0;	
        	}
	}
        // Tell runtime system how many output items we produced.
        return noutput_items;
    }

  } /* namespace mer */
} /* namespace gr */

