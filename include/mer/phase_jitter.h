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


#ifndef INCLUDED_MER_PHASE_JITTER_H
#define INCLUDED_MER_PHASE_JITTER_H

#include <mer/api.h>
#include <mer/demapper.h>
namespace gr {
  namespace mer {

    /*!
     * \brief Phase Jitter Error. 
     * \ingroup mer
     *
     * We estimate the phase jitter error using the outer right up constellation cloud. The model is that if x is a transmitted symbol the phase jitter plus noise is modeled as: y = x exp(j \phi) + n, where phi and n are gaussian random variables. If we define E{error^2}=(y-x)*(y-x)^*. 
     *
     * It can be proved that E{error^2} is approx. equal to N_0+\sigma_{\phi}^2 E_s where N_0 is the variance of the additive gaussian noise, sigma_{\phi}^2 is the variance of the jitter noise and E_s is the energy of the symbol. 
     * This class estimates \sigma_{\phi}^2 and the snr after the constellation points are corrected of the other linear impairments (cs,ai,qe). 
     *
     * update_pj returns  \sigma_{\phi}^2  and the snr is passed by reference. 
     *
     * A phase_jitter object is called to update pj with each sample received.  This class uses the demapper class to find the four outer constellation points.
     */
    class MER_API phase_jitter
    {
    public:
      phase_jitter(int dim_constellation, demapper *demap);
      ~phase_jitter();
      double update_pj(gr_complex iq,gr_complex cs,gr_complex ai,gr_complex qe,double tx_power, double & snr);

    private:
	int d_decimal_right_down;
	int d_decimal_right_up;
	int d_decimal_left_down;
	int d_decimal_left_up;
	gr_complex d_point_right_up;
	demapper * d_demapper;
	int d_dim_constellation;
	double d_var_cloud;
	gr_complex d_mean_cloud;
	double d_mean_noise;
	double d_var_noise;
    };

  } // namespace mer
} // namespace gr

#endif /* INCLUDED_MER_PHASE_JITTER_H */

