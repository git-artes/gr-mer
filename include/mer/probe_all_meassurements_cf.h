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


#ifndef INCLUDED_MER_PROBE_ALL_MEASSUREMENTS_CF_H
#define INCLUDED_MER_PROBE_ALL_MEASSUREMENTS_CF_H

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
     * \brief Probe Digital Modulation measurements. 
     * \ingroup mer
     * 
     * This block estimates the Modulation Error Ratio, System Target Error, Carrier Suppression error, Amplitud Imbalance error, Quadrature Eerror and Phase Jitter error.
     *
     * This block uses mer.cc to calculate the MER and average tx_power, uses the ste.cc to update d_di vector and to estimate the STE value, uses quadrature_error.cc to calculate the qe error, uses the carrier_suppression.cc to calculate the cs error,  uses the amplitude_imbalance.cc to calculate the ai error and the phase_jitter.cc to calculate the pj error and the snr. 
     * Please read first mer.cc, ste.cc, quadrature_error.cc, amplitude_imbalance.cc, carrier_suppression.cc and phase_jitter.cc  files.
     *
     * With each new sample updates di, tx power, ai, cs, qe and the pj and snr values. This block has nine outputs. 
     *
     * This class uses demapper.cc class to clasify to the constellation points of the received samples.
     */
    class MER_API probe_all_meassurements_cf : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<probe_all_meassurements_cf> sptr;

      /*!
       * \brief Receives the symbol table and the averaging parameter alpha.
       * 
       * The symbol table is used by the demapper.cc class.  
       * The parameter alpha is used by ste.cc class to average d_di vector and mer class to average the tx power.
       */
      static sptr make(const std::vector<gr_complex> &symbol_table, double alpha);
    };

  } // namespace mer
} // namespace gr

#endif /* INCLUDED_MER_PROBE_ALL_MEASSUREMENTS_CF_H */

