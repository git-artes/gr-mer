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
     * \brief Quadrature Imbalance Error for QAM. 

     * QUADRATURE IMBALANCE ERROR FOR QAM. 
     *
     * We estimate the quadrature imbalance error qe finding the horizontal and vertical angle of the constellation displacement. 
     * We assume that the displacement of the cosntellation points has the following axes symmetry. 
     * If the constellation has for example these two points: x+jy and -x+jy, a vertical quadrature error moves the points to x+j(y+u) and -x+j(y-u). 
     *
     * In order to estimate the qe error we use the following outer constellation points: right up point,right down point, left up point. 
     * With the first and the second ones we estimate the vertical angle and with the first and the third ones we estimate the horizontal angle. 
     * We give the angles in radians. 
     *
     * The estimation of the qe error uses the di vector (see ste.cc). 
     * This vector has the distance between the theoretical symbol point and the corresponding mean point of the cloud of this symbol point. 
     * If there are other linear distorsions (carrier suppression and amplitude imbalance) do not influence the calculation of qe errors. 
     * update_qe returns void but the angles are passed by reference to the function. 
     * quadrature error object is called  to update qe with each sample received. 
     *
     * This class uses the demapper class to find the four outer constellation points. 
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

