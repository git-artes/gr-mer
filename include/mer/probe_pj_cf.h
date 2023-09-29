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

#ifndef INCLUDED_MER_PROBE_PJ_CF_H
#define INCLUDED_MER_PROBE_PJ_CF_H

#include <gnuradio/sync_block.h>
#include <mer/api.h>
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

     * PHASE JITTER ERROR. 
     *
     * This block uses mer.cc to calculate the average tx_power, uses the ste.cc to update d_di vector, uses quadrature_error.cc to calculate the qe error, uses the carrier_suppression.cc to calculate the cs error,  uses the  amplitude_imbalance.cc to calculate the ai error and the phase_jitter.cc to calculate the pj error and the snr. 
     * Please read first ste.cc, quadrature_error.cc, amplitude_imbalance.cc and carrier_suppression.cc  files. 
     *
     * Each new sample updates di, tx power, ai, cs, qe and the pj and snr values. This block has two outputs the pj error and the snr. 
     * PJ is the the phase noise. 
     *
     * Each  d_nsamples sends a message with the last pj and snr estimations for the corresponding message port. 
     *
     * This class uses demapper.cc class to clasify to the constellation points of the received samples. 
     */
class MER_API probe_pj_cf : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<probe_pj_cf> sptr;

    /*!
     * \brief Phase Jitter Error. 
     * \ingroup mer

     * PHASE JITTER ERROR. 
     *
     * This block uses mer.cc to calculate the average tx_power, uses the ste.cc to update d_di vector, uses quadrature_error.cc to calculate the qe error, uses the carrier_suppression.cc to calculate the cs error,  uses the  amplitude_imbalance.cc to calculate the ai error and the phase_jitter.cc to calculate the pj error and the snr. 
     * Please read first ste.cc, quadrature_error.cc, amplitude_imbalance.cc and carrier_suppression.cc  files. 
     *
     * Each new sample updates di, tx power, ai, cs, qe and the pj and snr values. This block has two outputs the pj error and the snr. 
     * PJ is the the phase noise. 
     *
     * Each  d_nsamples sends a message with the last pj and snr estimations for the corresponding message port. 
     *
     * This class uses demapper.cc class to clasify to the constellation points of the received samples. 
     */
    static sptr make(const std::vector<gr_complex>& symbol_table, double alpha);
};

} // namespace mer
} // namespace gr

#endif /* INCLUDED_MER_PROBE_PJ_CF_H */
