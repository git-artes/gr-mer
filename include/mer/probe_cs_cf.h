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


#ifndef INCLUDED_MER_PROBE_CS_CF_H
#define INCLUDED_MER_PROBE_CS_CF_H

#include <mer/api.h>
#include <gnuradio/sync_block.h>
#include <mer/demapper.h>
#include <mer/ste.h>
#include <mer/mer.h>
#include <mer/carrier_suppression.h>

namespace gr {
  namespace mer {

    /*!
     * \brief Carrier suppression error.  
     * \ingroup mer
     *
     * This block uses mer.cc to calculate the average tx_power, uses the ste.cc to update d_di vector, uses carrier_suppression.cc to calculate the cs error. 
     * Please read first ste.cc and carrier_suppression.cc files. 
     *
     * With each new sample updates di, tx power, and cs, and outputs their values. CS is the power of the carrier suppression error normalized to the avergae tx power. 
     * Each  d_nsamples send a message with the last cs estimations for the corresponding message port. 
     *
     * This class uses demapper.cc class to classify the constellation points of the received samples. 
     */
    class MER_API probe_cs_cf : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<probe_cs_cf> sptr;

      /*!
       * \brief Receives the symbol table and the filter parameter alpha.

       * CARRIER SUPPRESSION ERROR. 
       *
       * We estimate the carrier suppression error finding the DC offset of the samples. The constellation is systematically translated  by a fixed vector. 
       * We assume that the displacement of the cosntellation points has the following axes symmetry. 
       * If the constellation has for example these two points: x+jy and -x+jy, a carrier suppression error on the real axe moves the points to x+u+jy and -x+u+jy. 
       * 
       * In order to estimate the cs error we use the four outer constellation points. We estimate the average translation vector of these four points. We average this translation over the four outer points. 
       */
      static sptr make(const std::vector<gr_complex> &symbol_table, double alpha);
    };

  } // namespace mer
} // namespace gr

#endif /* INCLUDED_MER_PROBE_CS_CF_H */

