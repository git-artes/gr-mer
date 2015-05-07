/* -*- c++ -*- */
/* 
 * Copyright 2015 <+YOU OR YOUR COMPANY+>.
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
     */
    probe_ai_cf_impl::probe_ai_cf_impl(const std::vector<gr_complex> &symbol_table, double alpha)
      : gr::sync_block("probe_ai_cf",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(2, 2, sizeof(float)))
    {
        d_nsamples = 1000;// number of samples to send a message with MER value
        d_count = 0;// sample's counter

	d_alpha = alpha;
      	d_ai_port = pmt::string_to_symbol("ai_msg");
      	message_port_register_out(d_ai_port);

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
			// Post a message with the latest MER value
			message_port_pub(d_ai_port, pmt::from_complex(ai));
			d_count =0;	
        	}
	}
        // Tell runtime system how many output items we produced.
        return noutput_items;
    }

  } /* namespace mer */
} /* namespace gr */

