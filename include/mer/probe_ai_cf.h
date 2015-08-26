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


#ifndef INCLUDED_MER_PROBE_AI_CF_H
#define INCLUDED_MER_PROBE_AI_CF_H

#include <mer/api.h>
#include <gnuradio/sync_block.h>
#include <mer/demapper.h>
#include <mer/ste.h>
#include <mer/mer.h>
#include <mer/amplitude_imbalance.h>
namespace gr {
  namespace mer {

    /*!
     * \brief Amplitude imabalance error. 
     * \ingroup mer
     *
     * This block uses mer.cc to calculate the average tx_power, uses the ste.cc to update d_di vector, uses amplitude_imbalance.cc to calculate the ai error. 
     * Please read first ste.cc and amplitude_imbalance.cc files. 
     *
     * With each new sample updates di,tx power and the ai error in the real  and imaginary axes and outs its values. This block has two outputs the ai error over the real and imaginary axes. 
     * AI is the real part and the imaginary part of the expansion or contraction vector applied to the constellation. 
     * Each  d_nsamples sends a message with the last ai estimations for the corresponding message port. 
     *
     * This class uses demapper.cc class to clasify to the constellation points of the received samples.
     */
    class MER_API probe_ai_cf : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<probe_ai_cf> sptr;

      /*!
       * \brief Receives the symbol table and the filter parameter alpha.
       *
	   * AMPLITUDE IMBALANCE ERROR. 
	   *
 	   * We estimate the amplitude imbalance error finding the  contraction or expansion vector of the constellation. 
 	   * We assume that the displacement of the cosntellation points has the following axes symmetry. 
 	   * If the constellation has for example these two points: x+jy and -x+jy, an amplitud imabalance error on the real axe moves the points to x+u+jy and -x-u+jy. 
 	   * In order to estimate the ai error we use the four outer constellation points. 
 	   * We estimate the average expansion (contraction) of these four points. We average this contraction (expansion) over the four outer points.
       */
      static sptr make(const std::vector<gr_complex> &symbol_table, double alpha);
    };

  } // namespace mer
} // namespace gr

#endif /* INCLUDED_MER_PROBE_AI_CF_H */

