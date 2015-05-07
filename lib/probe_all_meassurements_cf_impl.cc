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
#include "probe_all_meassurements_cf_impl.h"

namespace gr {
  namespace mer {

    probe_all_meassurements_cf::sptr
    probe_all_meassurements_cf::make(const std::vector<gr_complex> &symbol_table, double alpha)
    {
      return gnuradio::get_initial_sptr
        (new probe_all_meassurements_cf_impl(symbol_table, alpha));
    }

    /*
     * The private constructor
     */
    probe_all_meassurements_cf_impl::probe_all_meassurements_cf_impl(const std::vector<gr_complex> &symbol_table, double alpha)
      : gr::sync_block("probe_all_meassurements_cf",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(9, 9, sizeof(float)))
    {
        d_nsamples = 1000;// number of samples to send a message with MER value
        d_count = 0;// sample's counter

	d_alpha = alpha;

      	d_dim_constellation = symbol_table.size();
      	d_demapper = new demapper(symbol_table);
	d_pj = new phase_jitter(d_dim_constellation,d_alpha,d_demapper);
	d_ai = new amplitude_imbalance(d_demapper);
	d_qe = new quadrature_error(d_dim_constellation,d_alpha,d_demapper);
	d_cs = new carrier_suppression(d_demapper);
	d_mer = new mer(d_alpha);
	d_ste = new ste(d_dim_constellation,d_alpha);
    }
    /*
     * Our virtual destructor.
     */
    probe_all_meassurements_cf_impl::~probe_all_meassurements_cf_impl()
    {
    }

    int
    probe_all_meassurements_cf_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
 	const gr_complex *in = (const gr_complex*)input_items[0];
      	float *angleh_out = NULL,*anglev_out = NULL, *pj_out=NULL,*snr_out=NULL,*ai_real_out=NULL,*ai_imag_out=NULL,*cs_out=NULL,*mer_out=NULL,*ste_out=NULL;
        mer_out = (float *) output_items[0];
	ste_out = (float *) output_items[1];
	cs_out = (float *) output_items[2];
	ai_real_out = (float *) output_items[3];
	ai_imag_out = (float *) output_items[4];
	angleh_out = (float *) output_items[5];
	anglev_out = (float *) output_items[6];
	pj_out = (float *) output_items[7];
        snr_out = (float *) output_items[8];

	double tx_power;
     	gr_complex iq_true,ai,*di,qe,cs;
	double ste;
      	int constellation_value=0;
	for(int j=0; j < noutput_items; j++) {
	      	iq_true = d_demapper->demap(in[j],constellation_value);
		tx_power = d_mer->update_avg_tx_power(iq_true);
		mer_out[j]=d_mer->update_mer(in[j],iq_true);

		di = d_ste->update_di(in[j],iq_true,constellation_value);
		ste_out[j]=d_ste->update_ste(in[j],iq_true,constellation_value);

		ai = d_ai->update_ai(tx_power,di);
		ai_real_out[j] = real(ai);
		ai_imag_out[j] = imag(ai);

		double angle1, angle2;
		d_qe->update_qe(tx_power,di,angle1,angle2);
		angleh_out[j] = angle1*180/3.1416;
		anglev_out[j] = angle2*180/3.1416;
		qe= gr_complex(angle1,angle2);
		cs_out[j] = d_cs->update_cs(tx_power,di);
		cs = d_cs->d_cs;
		// as we use the right up constellation cloud to estimate the pj, it is not necessary to interpolate the angle neither the ai
		double snr;
		pj_out[j] = d_pj->update_pj(in[j],cs,ai,qe,tx_power,snr);
		snr_out[j] = snr;
		d_count ++;

		if(d_count > d_nsamples) {
			// Post a message with the latest  value
			// for the moment this block is not sending messages
			d_count =0;	
        	}
	}
        // Tell runtime system how many output items we produced.
        return noutput_items;
    }

  } /* namespace mer */
} /* namespace gr */
