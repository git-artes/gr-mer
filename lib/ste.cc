/* -*- c++ -*- */
/* 
 * Copyright 2023,2015
 * Pablo Belzarena <belza@fing.edu.uy>, Gabriel Gomez,  Victor Gonzalez-Barbone,Pablo Flores Guridi, Federico Larroca, Gonzalo Belcredi. 
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


#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include <mer/ste.h>
#include<stdio.h>

namespace gr {
  namespace mer {

    ste::ste(int dim_constellation, double alpha)
    {
	// averaging filter parameter
	d_alpha = alpha;
	d_dim_constellation = dim_constellation;
	// intialize d_di vector
	d_di = new gr_complex[d_dim_constellation]; 
        for (int i = 0; i < d_dim_constellation; i++)
    		d_di[i] = 0;
    }

    ste::~ste()
    {
    }
    // update d_di vector averaging over the sample points received 
    gr_complex *
    ste::update_di(gr_complex iq,gr_complex iq_true,int constellation_value)
    {
		double d=0;
        float aux = 0; 
		if (iq==iq){
            aux = real(iq-iq_true)*d_alpha +(1-d_alpha)* real(d_di[constellation_value]);
			d_di[constellation_value].real(aux);
            aux = imag(iq-iq_true)*d_alpha +(1-d_alpha)* imag(d_di[constellation_value]);
			d_di[constellation_value].imag(aux);
		}
		return d_di;
    }
    double
    ste::update_ste(gr_complex iq,gr_complex iq_true,int constellation_value)
    {
	double d=0;
	update_di(iq,iq_true, constellation_value);
	
	for (int i = 0; i < d_dim_constellation; i++)
		 	        		 	        		
		d= d + abs(d_di[i]); 	        		 	        		
        return d/d_dim_constellation;
    }
    double
    ste::update_stem(gr_complex iq,gr_complex iq_true,int constellation_value,double tx_power)
    {
	double d=0;
	update_di(iq,iq_true, constellation_value);
	for (int i = 0; i < d_dim_constellation; i++)
		d= d + abs(d_di[i]);
	if(tx_power > 0.000000001)        		
        	return d/tx_power/d_dim_constellation;
	else
		return 0;
    }

    double
    ste::update_sted(gr_complex iq,gr_complex iq_true,int constellation_value,double tx_power)
    {
	double d=0;
	double stem;
	        		 	        		
	update_di(iq,iq_true, constellation_value);
	stem = update_stem(iq,iq_true,constellation_value,tx_power);
	for (int i = 0; i < d_dim_constellation; i++)
		d= d + norm(d_di[i]); 
	// test for nan conditions
	if (tx_power > 0.000000001 && d/d_dim_constellation/tx_power/tx_power > stem*stem)         		
	        return sqrt(d/d_dim_constellation/tx_power/tx_power - stem*stem);
	else
		return 0;
    }
  } /* namespace mer */
} /* namespace gr */

