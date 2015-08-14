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
     */
    class MER_API probe_ai_cf : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<probe_ai_cf> sptr;

      /*!
       * \brief Receives the symbol table and the filter parameter alpha.

	   * AMPLITUDE IMBALANCE ERROR. 
 	   * We estimate the amplitude imbalance error finding the  contraction or expansion vector of the constellation. 
 	   * We assume that the displacement of the cosntellation points has the following axes symmetry.
 	   * If the constellation has for example these two points: x+jy and -x+jy, an amplitud imabalance error on the real axe moves the points to x+u+jy and -x-u+jy. 
 	   * In order to estimate the ai error we use the four outer constellation points. 
 	   * We estimates the average expansion (contraction) of these four points. We average this contraction (expansion) over the four outer points.
       */
      static sptr make(const std::vector<gr_complex> &symbol_table, double alpha);
    };

  } // namespace mer
} // namespace gr

#endif /* INCLUDED_MER_PROBE_AI_CF_H */

