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


#ifndef INCLUDED_MER_CARRIER_SUPPRESSION_H
#define INCLUDED_MER_CARRIER_SUPPRESSION_H

#include <mer/api.h>
#include <mer/demapper.h>
namespace gr {
  namespace mer {

    /*!
     * \brief Carrier Suppression Error.
     * \ingroup mer
     *
     * We estimate the carrier suppression error finding the DC offset of the samples. The constellation is systematically translated  by a fixed vector. 
     * We assume that the displacement of the cosntellation points has the following axes symmetry. 
     *
     * If the constellation has for example these two points: x+jy and -x+jy, a carrier suppression error on the real axe moves the points to x+u+jy and -x+u+jy. 
     *
     * In order to estimate the cs error we use the four outer constellation points. We estimates the average translation vector of these four points. We average this translation over the four outer points. 
     * The estimation of the translation of the constellation uses the di vector (see ste.cc) that has the distance between the theoretical symbol point and the corresponding mean point of the cloud of this symbol point. 
     * As we sum the translation vector of the four outer points the other linear distorsions (Amplitud Imbalance that is an expansion or contraction of the constellation and the quadrature error)  are eliminated because they have the same magnitud but different sign in the outer points. 
     *
     * The class has the vector d_cs that can be accessed and the update_cs returns the residual carrier power normalized to the tx average power. 
     *
     * A carrier_suppression object is called to update cs with each sample received. This class uses the demapper class to find the four outer constellation points. 
     */
    class MER_API carrier_suppression
    {
    public:
      carrier_suppression(demapper *demap);
      ~carrier_suppression();
      double update_cs(double tx_power, gr_complex *di);
      gr_complex d_cs;
    private:
	int decimal_right_down;
	int decimal_right_up;
	int decimal_left_down;
	int decimal_left_up;
	demapper * d_demapper;
    };

  } // namespace mer
} // namespace gr

#endif /* INCLUDED_MER_CARRIER_SUPPRESSION_H */

