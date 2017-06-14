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


#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include <mer/phase_jitter.h>

namespace gr {
  namespace mer {

    phase_jitter::phase_jitter(int dim_constellation,demapper *demap)
    {
	//with the demapper object we find the outer constellation points
	d_dim_constellation = dim_constellation;
	d_demapper = demap;
	d_demapper->right_down_contellation(d_decimal_right_down);
	d_point_right_up= d_demapper->right_up_contellation(d_decimal_right_up);
	d_demapper->left_down_contellation(d_decimal_left_down);
	d_demapper->left_up_contellation(d_decimal_left_up);
	// the following variables are used by update method to store mean and variance  of the cloud and the additive noise
	d_mean_cloud=0;
	d_var_cloud =0;
	d_mean_noise =0;
	d_var_noise =0;
    }

    phase_jitter::~phase_jitter()
    {
    }
    // this method receives the values of the imparirments cs,ai,qe to cancel its effects on the iq value before pj estimation
    // average tx_power is used to estimate the snr
    double
    phase_jitter::update_pj(gr_complex iq,gr_complex cs,gr_complex ai,gr_complex qe,double tx_power, double & snr)
    {

		// check if iq is not a number
		// if something went wrong just return
		if (iq!=iq) return 0;

	double aux_mean=0;
	double aux=0;
	// the phase jitter modify the cloud in the (-1,1) and (1,-1) direction and the additive noise is not affected in the (1,1) direction
	// in order to estimate the noise we use the (1,1) direction using and epsilon-band on that direction
	double epsilon = real(d_point_right_up)/sqrt(d_dim_constellation)/40.0;
	double decimal_point = d_demapper->demap(iq);
	// estimate the phase jitter and snr using the outer right up constelation cloud
	if(decimal_point == d_decimal_right_up){
		// move the right up cloud to the origin
		// correct que impairmants cs, qe and ai
		gr_complex pj_aux= iq - d_point_right_up-cs-ai-qe;
		// estimate the additive noise variance over  the points of the cloud in (1,1) direction
		if( (imag(pj_aux) >= real(pj_aux)-epsilon) && (imag(pj_aux) <= real(pj_aux)+epsilon) ){
			if (real(pj_aux) >= 0){
				aux = abs(pj_aux);			
			}else{
				aux = -abs(pj_aux);
			}	
			// we average the estimations using a one pole iir filter with alpha = 0.001
			d_mean_noise = d_mean_noise *(1-0.001) + aux * 0.001;
			d_var_noise = d_var_noise*(1-0.001)+ (abs(pj_aux) -d_mean_noise)* (abs(pj_aux) -d_mean_noise)*0.001;		
		} 
		// estimate the variance of the error of the cloud
		d_mean_cloud.real( real(d_mean_cloud) *(1-0.001) + real(pj_aux) * 0.001 );	
		d_mean_cloud.imag( imag(d_mean_cloud) *(1-0.001) + imag(pj_aux) * 0.001 );	
		d_var_cloud = d_var_cloud*(1-0.001)+ norm(pj_aux-d_mean_cloud)*0.001; 
			
	}
	if(d_var_noise >= 0.0000000001) 
		snr = tx_power/d_var_noise/2;
	else
		snr =0;

	if(d_var_cloud-d_var_noise*2>=0)
		return (d_var_cloud-2 *d_var_noise)/norm(d_point_right_up);
	else	
		return 0;
    }


  } /* namespace mer */
} /* namespace gr */

