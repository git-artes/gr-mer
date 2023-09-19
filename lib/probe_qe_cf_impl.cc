/* -*- c++ -*- */
/* 
 * Copyright 2023,2015
 * Pablo Belzarena <belza@fing.edu.uy>, Gabriel Gomez,  Victor Gonzalez-Barbone, Pablo Flores Guridi, Federico Larroca, Gonzalo Belcredi. 
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

#include "probe_qe_cf_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace mer {

using input_type = float;
using output_type = float;
probe_qe_cf::sptr probe_qe_cf::make(const std::vector<gr_complex>& symbol_table,
                                    double alpha)
{
    return gnuradio::make_block_sptr<probe_qe_cf_impl>(symbol_table, alpha);
}


/*
 * The private constructor
 */
probe_qe_cf_impl::probe_qe_cf_impl(const std::vector<gr_complex>& symbol_table,
                                   double alpha)
    : gr::sync_block("probe_qe_cf",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(2, 2, sizeof(float)))
{
    d_nsamples = 1000;// number of samples to send a message with MER value
    d_count = 0;// sample's counter
    // filter parameter to average the di vector in ste object and the tx power.
    d_alpha = alpha;
    //creates the message ports
    d_angleh_port = pmt::string_to_symbol("angleh_msg");
    message_port_register_out(d_angleh_port);
    d_anglev_port = pmt::string_to_symbol("anglev_msg");
    message_port_register_out(d_anglev_port);
    //creates the objects
    d_dim_constellation = symbol_table.size();
    d_demapper = new demapper(symbol_table);
    d_ste = new ste(d_dim_constellation,d_alpha);
    d_qe = new quadrature_error(d_demapper);
    d_mer = new mer(d_alpha);
}

/*
 * Our virtual destructor.
 */
probe_qe_cf_impl::~probe_qe_cf_impl() {}

int probe_qe_cf_impl::work(int noutput_items,
                           gr_vector_const_void_star& input_items,
                           gr_vector_void_star& output_items)
{
    const gr_complex *in = (const gr_complex*)input_items[0];
    float *angleh_out = NULL,*anglev_out = NULL;
    angleh_out = (float *) output_items[0];
    anglev_out = (float *) output_items[1];
    double tx_power;
    gr_complex iq_true;
    gr_complex *di;
    // constellation value is the constellation point decimal value
    int constellation_value=0;
    for(int j=0; j < noutput_items; j++) {
        iq_true = d_demapper->demap(in[j],constellation_value);
        tx_power = d_mer->update_avg_tx_power(iq_true);
        di = d_ste->update_di(in[j],iq_true,constellation_value);
        double angle1, angle2;
        d_qe->update_qe(tx_power,di,angle1,angle2);
        anglev_out[j] = angle2*180/M_PI;
        angleh_out[j] = angle1*180/M_PI;
        d_count ++;
        if(d_count > d_nsamples) {
            // Post a message with the latest QE values
            message_port_pub(d_angleh_port, pmt::from_double(angle1*180/M_PI));
            message_port_pub(d_anglev_port, pmt::from_double(angle2*180/M_PI));
            d_count =0;	
        }
    }
    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace mer */
} /* namespace gr */
