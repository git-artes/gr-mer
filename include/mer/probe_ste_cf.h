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


#ifndef INCLUDED_MER_PROBE_STE_CF_H
#define INCLUDED_MER_PROBE_STE_CF_H

#include <mer/api.h>
#include <gnuradio/sync_block.h>
#include <mer/demapper.h>
#include <mer/ste.h>
#include <mer/mer.h>
namespace gr {
  namespace mer {

    /*!
     * \brief System Target Error - STE.
     * \ingroup mer
     *
     */
    class MER_API probe_ste_cf : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<probe_ste_cf> sptr;

      /*!
       * \brief Receives the symbol table and the filter parameter alpha.
       *
       * SYSTEM TARGET ERROR - STE.
       * For each of the dim_constellation symbol points calculate the distance d_di between the theoretical symbol point and the corresponding mean point of the cloud of this symbol point. 
       * d_di is called Target Error Vector (TEV).This vector indicates the presence of distortions like Carrier Suppression, Amplitude Imbalance, Quadrature Error and may be other non-linear distortions.
       * We define the first output of the block STE as the average of abs(d_di) over the constellation points : sum_{i=0}^{dim_constellation-1}(abs(d_di[i]))/d_dim_constellation.
       * We define the second output: System Target Error Mean STEM as the STE normalized to the average Tx power STE/tx_power.
       * We define the third output System Target Error Deviation as the standard deviation over the constellation points: STED = sqrt(sum_{i=0}^{dim_constellation-1}abs(d_di[i])/d_dim_constellation/tx_power^2- STEM^2). 
       * Averaging of the d_di vector is implemented with a first order IIR filter with parameter d_alpha.
       */
      static sptr make(const std::vector<gr_complex> &symbol_table, double alpha);
    };

  } // namespace mer
} // namespace gr

#endif /* INCLUDED_MER_PROBE_STE_CF_H */

