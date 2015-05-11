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


#ifndef INCLUDED_MER_QUADRATURE_ERROR_H
#define INCLUDED_MER_QUADRATURE_ERROR_H

#include <mer/api.h>
#include <mer/demapper.h>
namespace gr {
  namespace mer {

    /*!
     * \brief <+description+>
     *
     */
    class MER_API quadrature_error
    {
    public:
      quadrature_error(demapper *demap);
      ~quadrature_error();
      void update_qe(double tx_power, gr_complex *di, double &angleh, double &anglev);
    private:
	int d_decimal_right_down;
	int d_decimal_right_up;
	int d_decimal_left_down;
	int d_decimal_left_up;
	gr_complex d_point_right_up;
	demapper * d_demapper;
    };

  } // namespace mer
} // namespace gr

#endif /* INCLUDED_MER_QUADRATURE_ERROR_H */

