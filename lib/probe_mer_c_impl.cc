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


/* This block uses mer.cc to calculate the Modulation Error Rate
 * With each new sample updates MER and outs its value.
 * Each  d_nsamples send a message with the last MER estimation
 * This class uses demapper.cc class to clasify to the constellation points the received samples
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "probe_mer_c_impl.h"

namespace gr {
  namespace mer {

    probe_mer_c::sptr
    probe_mer_c::make(const std::vector<gr_complex> &symbol_table, double alpha)
    {
      return gnuradio::get_initial_sptr
        (new probe_mer_c_impl(symbol_table, alpha));
    }

    /*
     * The private constructor
     * Receives the symbol table and the averaging parameter alpha
     * The symbol table is used by the demapper.cc class 
     * The parameter alpha is used by mer.cc class to average MER  
     */
    probe_mer_c_impl::probe_mer_c_impl(const std::vector<gr_complex> &symbol_table, double alpha)
      : gr::sync_block("probe_mer_c",
          io_signature::make(1, 1, sizeof(gr_complex)),
		      io_signature::make(1, 1, sizeof(float)))
    {

        d_nsamples = 1000;// number of samples to send a message with MER value
        d_count = 0;// sample's counter

	d_alpha = alpha;
      	d_mer_port = pmt::string_to_symbol("mer_msg");
      	message_port_register_out(d_mer_port);
      	d_dim_constellation = symbol_table.size();
      	d_demapper = new demapper(symbol_table);
        d_mer = new mer(d_alpha);
    }

    /*
     * Our virtual destructor.
     */
    probe_mer_c_impl::~probe_mer_c_impl()
    {
    }

    int
    probe_mer_c_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
 	const gr_complex *in = (const gr_complex*)input_items[0];
      	float *mer_out = NULL;
        mer_out = (float *) output_items[0];
     	gr_complex iq_true;
	// cosntellation_value is the point of the constellation in decimal notation
      	int constellation_value=0;
      	double i,q,i_true,q_true;
	for(int j=0; j < noutput_items; j++) {
	      	iq_true = d_demapper->demap(in[j],constellation_value);
			mer_out[j]=d_mer->update_mer(in[j],iq_true);
			d_count ++;
			if(d_count > d_nsamples) {
				// Post a message with the latest MER value
				message_port_pub(d_mer_port, pmt::from_double(mer_out[j]));
				d_count =0;	
        	}
	}
        // Tell runtime system how many output items we produced.
        return noutput_items;
    }

  } /* namespace mer */
} /* namespace gr */

