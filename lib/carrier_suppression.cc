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


#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include <mer/carrier_suppression.h>

namespace gr {
  namespace mer {
    carrier_suppression::carrier_suppression(demapper *demap)
    {
	// with the demapper object we find the outer constellation points
	d_demapper = demap;
	d_demapper->right_down_contellation(decimal_right_down);
	d_demapper->right_up_contellation(decimal_right_up);
	d_demapper->left_down_contellation(decimal_left_down);
	d_demapper->left_up_contellation(decimal_left_up);
	// we store the carrier suppression error as a complex number in a public variable
	d_cs =0;
    }

    carrier_suppression::~carrier_suppression()
    {
    }

    double
    carrier_suppression::update_cs(double tx_power, gr_complex *di)
    {
	// di vector has the distance between the theoretical symbol point and the corresponding mean point of the cloud of this symbol point.
	// In order to estimate the cs error we use the four outer constellation points. We estimate the average translation vector of these four outer points. 
	d_cs.real( real(di[decimal_right_up]) + real(di[decimal_right_down])+real(di[decimal_left_down])+real(di[decimal_left_up]) );

    d_cs.imag( imag(di[decimal_right_up]) + imag(di[decimal_right_down])+imag(di[decimal_left_down])+imag(di[decimal_left_up]) );
	
    
    //We average this translation over the four outer points.
	d_cs.real(real(d_cs)/4);
	d_cs.imag(imag(d_cs)/4);
	// returns the residual carrier power normalized to the tx average power.
        return (real(d_cs)*real(d_cs)+imag(d_cs)*imag(d_cs))/tx_power;
    }
  } /* namespace mer */
} /* namespace gr */

