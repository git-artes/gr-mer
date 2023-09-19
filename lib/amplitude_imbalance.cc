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
#include <mer/amplitude_imbalance.h>

namespace gr {
  namespace mer {

    amplitude_imbalance::amplitude_imbalance(demapper *demap)
    {
	//with the demapper object we find the outer constellation points
	d_demapper = demap;
	d_demapper->right_down_contellation(decimal_right_down);
	point_right_up = d_demapper->right_up_contellation(decimal_right_up);
	d_demapper->left_down_contellation(decimal_left_down);
	d_demapper->left_up_contellation(decimal_left_up);
	
    }

    amplitude_imbalance::~amplitude_imbalance()
    {
    }

    gr_complex
    amplitude_imbalance::update_ai(double tx_power, gr_complex *di)
    {
	gr_complex ai=0;
	// estimates the amplitude imbalance by meassuring the expansion or the contraction of the outer points of the constellation
	ai.real( real(di[decimal_right_up]) + real(di[decimal_right_down])-real(di[decimal_left_down])-real(di[decimal_left_up]) );

    ai.imag( imag(di[decimal_right_up]) - imag(di[decimal_right_down])-imag(di[decimal_left_down])+imag(di[decimal_left_up]) );	
	
    // divide by 4 because we estimate using the 4 outer points of the constellation
	ai.real( real(ai)/4/real(point_right_up) );
	ai.imag( imag(ai)/4/imag(point_right_up) );
        return ai;
    }


  } /* namespace mer */
} /* namespace gr */

