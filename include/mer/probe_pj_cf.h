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


#ifndef INCLUDED_MER_PROBE_PJ_CF_H
#define INCLUDED_MER_PROBE_PJ_CF_H

#include <mer/api.h>
#include <gnuradio/sync_block.h>
#include <mer/demapper.h>
#include <mer/ste.h>
#include <mer/mer.h>
#include <mer/quadrature_error.h>
#include <mer/phase_jitter.h>
#include <mer/amplitude_imbalance.h>
#include <mer/carrier_suppression.h>

namespace gr {
  namespace mer {

    /*!
     * \brief Phase Jitter Error.
     * \ingroup mer
     *
     */
    class MER_API probe_pj_cf : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<probe_pj_cf> sptr;

      /*!
       * \brief Receives the symbol table and the filter parameter alpha.
       *
       * PHASE JITTER ERROR.
       * We estimate the phase jitter error using the outer right up constellation cloud.The model is that if x is a transmitted symbol the phase jitter plus additive noise is modeled as: y = x exp(j \phi) + n, 
       * where phi and n are gaussian random variables. If we define E{error^2}=(y-x)*(y-x)^*.
       * It can be proved that E{error^2} is approx equal to N_0+\sigma_{\phi}^2 E_s where N_0 is the variance of the additive gaussian noise, sigma_{\phi}^2 is the variance of the jitter noise and E_s is the energy of the symbol.
       * This class estimates \sigma_{\phi}^2 and the snr after the constellation points are corrected of the other linear impairments (cs,ai,qe).
       * This block outputs  \sigma_{\phi}^2  and the snr as a flow of floats and as periodic messages.
       */
      static sptr make(const std::vector<gr_complex> &symbol_table, double alpha);
    };

  } // namespace mer
} // namespace gr

#endif /* INCLUDED_MER_PROBE_PJ_CF_H */

