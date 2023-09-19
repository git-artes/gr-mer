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


#ifndef INCLUDED_MER_AMPLITUDE_IMBALANCE_H
#define INCLUDED_MER_AMPLITUDE_IMBALANCE_H

#include <mer/api.h>
#include <mer/demapper.h>
namespace gr {
  namespace mer {

    /*!
     * \brief Amplitude Imbalance Error. 
     * \ingroup mer
     *
     * We estimate the amplitude imbalance error finding the  contraction or expansion vector of the constellation. 
     * 
     * We assume that the displacement of the cosntellation points has the following axes symmetry. 
     *
     * If the constellation has for example these two points: x+jy and -x+jy, an amplitude imabalance error on the real axe moves the points to x+u+jy and -x-u+jy. 
     *
     * In order to estimate the ai error we use the four outer constellation points we estimate the average expansion (contraction) of these four points. We average this contraction (expansion) over the four outer points. 
     * The estimation of the contraction (expansion) of the constellation uses the di vector (see ste.cc). 
     *
     * This vector has the distance between the theoretical symbol point and the corresponding mean point of the cloud of this symbol point. 
     * As we add the di vector of the four outer points but changing the sign of opposite points the other linear distorsions (Carrier suppression and the quadrature error)  are eliminated. 
     *  Function update_ai returns a complex number that has the real and imaginary expansion (contraction) values. 
     * An amplitude_imbalance object is called to update ai with each sample received. This class uses the demapper class to find the four outer constellation points. 
     */
    class MER_API amplitude_imbalance
    {
    public:
      amplitude_imbalance(demapper *demap);
      ~amplitude_imbalance();
       gr_complex update_ai(double tx_power, gr_complex *di);
    private:
	int decimal_right_down;
	int decimal_right_up;
	int decimal_left_down;
	int decimal_left_up;
	gr_complex point_right_up;
	demapper * d_demapper;
    };

  } // namespace mer
} // namespace gr

#endif /* INCLUDED_MER_AMPLITUDE_IMBALANCE_H */

