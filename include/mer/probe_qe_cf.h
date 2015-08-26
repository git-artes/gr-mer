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


#ifndef INCLUDED_MER_PROBE_QE_CF_H
#define INCLUDED_MER_PROBE_QE_CF_H

#include <mer/api.h>
#include <gnuradio/sync_block.h>
#include <mer/demapper.h>
#include <mer/ste.h>
#include <mer/mer.h>
#include <mer/quadrature_error.h>
namespace gr {
  namespace mer {

    /*!
     * \brief Quadrature Imbalance Error for QAM. 
     * \ingroup mer
     *
     * AMPLITUDE IMBALANCE ERROR. 
     *
     * This block uses mer.cc to calculate the average tx_power, uses the ste.cc to update d_di vector, uses quadrature_error.cc to calculate the qe error. 
     * Please read first ste.cc and quadrature_error.cc files. 
     *
     * With each new sample updates di,tx power and the qe error in the real  and imaginary axes and outs its values. This block has two outputs the qe error over the real and imaginary axes. 
     * QE is the angular displacement of the constellation on the real and the imaginary axes. 
     * Each  d_nsamples sends a message with the last qe estimations for the corresponding message port. 
     *
     * This class uses demapper.cc class to clasify to the constellation points of the received samples. 
*/
    class MER_API probe_qe_cf : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<probe_qe_cf> sptr;

      /*!
       * \brief Receives the symbol table and the filter parameter alpha.
       * 
       * QUADRATURE IMBALANCE ERROR FOR QAM. 
       *
       * We estimate the quadrature imbalance error qe finding the horizontal and vertical angle of the constellation displacement. 
       * We assume that the displacement of the cosntellation points has the following axes symmetry. 
       * If the constellation has for example these two points: x+jy and -x+jy, a vertical quadrature error moves the points to x+j(y+u) and -x+j(y-u). 
       *
       * In order to estimate the qe error we use the following outer constellation points: right up point,right down point, left up point. 
       * With the first and the second ones we estimate the vertical angle and with the first and the third ones we estimate the horizontal angle. 
       *
       * The block gives the angles in radians. 
       * If there are other linear distorsions (carrier suppression and amplitude imbalance) do not influence the calculation of qe errors.  
       */
      static sptr make(const std::vector<gr_complex> &symbol_table, double alpha);
    };

  } // namespace mer
} // namespace gr

#endif /* INCLUDED_MER_PROBE_QE_CF_H */

