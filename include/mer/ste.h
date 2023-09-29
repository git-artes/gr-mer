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


#ifndef INCLUDED_MER_STE_H
#define INCLUDED_MER_STE_H

#include <mer/api.h>

namespace gr {
  namespace mer {

    /*!
     * \brief System Target Error - STE. 
     *
     * SYSTEM TARGET ERROR - STE. 
     *
     * For each of the dim_constellation symbol points calculate the distance d_di between the theoretical symbol point and the corresponding mean point of the cloud of this symbol point. d_di is called Target Error Vector (TEV).This vector indicates the presence of distortions like Carrier Suppression, Amplitude Imbalance, Quadrature Error and may be other non-linear distortions. 
     *
     * We define the STE as the average of abs(d_di) over the constellation points : sum_{i=0}^{dim_constellation-1}(abs(d_di[i]))/d_dim_constellation. 
     * We define the System Target Error Mean STEM as the STE normalized to the average Tx power STE/tx_power. 
     * We define the System Target Error Deviation as the standard deviation over the constellation points: STED = sqrt(sum_{i=0}^{dim_constellation-1}abs(d_di[i])/d_dim_constellation/tx_power^2- STEM^2). 
     *
     * Averaging of the d_di vector is implemented with a first order IIR filter with parameter d_alpha. 
     *
     * An ste object is called by different probes to update d_di vector for each sample received. An ste object is called by probe_ste to update ste, stem and sted with each sample. 
     */
    class MER_API ste
    {
    public:
    	ste(int dim_constellation,double alpha);
    	~ste();
	double update_ste(gr_complex iq,gr_complex iq_true,int constellation_value);
	double update_stem(gr_complex iq,gr_complex iq_true,int constellation_value,double tx_power);
	double update_sted(gr_complex iq,gr_complex iq_true,int constellation_value,double tx_power);
	gr_complex * update_di(gr_complex iq,gr_complex iq_true,int constellation_value);
    private:
	double d_alpha;
	// di is a vector with the average distance of each cloud center to the corresponding constellation point	
	gr_complex *d_di;
	int d_dim_constellation;
    };

  } // namespace mer
} // namespace gr

#endif /* INCLUDED_MER_STE_H */

