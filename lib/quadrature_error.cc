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
#include <mer/quadrature_error.h>


namespace gr {
  namespace mer {

    quadrature_error::quadrature_error( demapper *demap)
    {
	d_demapper = demap;
	d_demapper->right_down_contellation(d_decimal_right_down);
	d_point_right_up= d_demapper->right_up_contellation(d_decimal_right_up);
	d_demapper->left_down_contellation(d_decimal_left_down);
	d_demapper->left_up_contellation(d_decimal_left_up);
    }

    quadrature_error::~quadrature_error()
    {
    }
    void
    quadrature_error::update_qe(double tx_power, gr_complex *di, double &angleh, double &anglev)
    {
	gr_complex qe_aux=0;
	// angles estimation
	qe_aux.real( (real(di[d_decimal_right_up])-real(di[d_decimal_right_down]))/2 );
	qe_aux.imag( (imag(di[d_decimal_right_up])-imag(di[d_decimal_left_up]))/2 );
	angleh = atan(imag(qe_aux)/real(d_point_right_up));	
	anglev = atan(real(qe_aux)/imag(d_point_right_up));	
    }
  } /* namespace mer */
} /* namespace gr */

