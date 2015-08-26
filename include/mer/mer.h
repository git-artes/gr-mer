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


#ifndef INCLUDED_MER_MER_H
#define INCLUDED_MER_MER_H

#include <mer/api.h>

namespace gr {
  namespace mer {

    /*!
     * \brief Modulator Error Rate. 
     * \ingroup mer 
     *
     * Lets I[i],Q[i] the sample i received and I_{true}[i] and Q_{true}[i] the corresponding constellation point. 
     *
     * MER is defined as: lets  txsignal_power[i] = I^2_{true][i] + Q^2_{true}[i] and error_power[i]= (I_{true][i]-I[i])^2 + (Q_{true}[i]- Q[i])^2 and lets d_avgtxsignal_power = average{txsignal_power[i]} and d_avgerror_power = average{error_power[i]}. 
     * 
     * MER = 10*log10(d_avgtxsignal_power/ d_avgerror_power) in dbs 
     *
     * Averaging is implemented with a first order IIR filter with parameter d_alpha. The mer object is called with each sample received in order to update the average tx power, the average error power and mer. 
     */
    class MER_API mer
    {
    public:
    	mer(double alpha);
    	~mer();
        double update_mer(gr_complex iq,gr_complex iq_true);
	double update_avg_tx_power(gr_complex iq_true);
	double update_avg_error_power(gr_complex iq,gr_complex iq_true);
    private:
	double d_alpha;	
      	double d_avgtxsignal_power;
      	double d_avgerror_power;
    };

  } // namespace mer
} // namespace gr

#endif /* INCLUDED_MER_MER_H */

