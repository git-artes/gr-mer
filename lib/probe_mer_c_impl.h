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

#ifndef INCLUDED_MER_PROBE_MER_C_IMPL_H
#define INCLUDED_MER_PROBE_MER_C_IMPL_H

#include <mer/probe_mer_c.h>

namespace gr {
  namespace mer {

    class probe_mer_c_impl : public probe_mer_c
    {
     private:
      int d_nsamples, d_count;
      double d_alpha;
      demapper *d_demapper;
      mer *d_mer;
      int d_dim_constellation;
      // Message port name
      pmt::pmt_t d_mer_port;
 
     public:
      probe_mer_c_impl(const std::vector<gr_complex> &symbol_table, double alpha);
      ~probe_mer_c_impl();

      // Where all the action really happens
      int work(int noutput_items,
	       gr_vector_const_void_star &input_items,
	       gr_vector_void_star &output_items);
    };

  } // namespace mer
} // namespace gr

#endif /* INCLUDED_MER_PROBE_MER_C_IMPL_H */

