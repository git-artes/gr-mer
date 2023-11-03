/* -*- c++ -*- */
/*
 * Copyright 2023,2015
 *   Pablo Belzarena <belza@fing.edu.uy>, Gabriel Gomez, Victor Gonzalez-Barbone, Pablo
 * Flores Guridi, Federico Larroca, Gonzalo Belcredi. ARTES Group
 *   http://iie.fing.edu.uy/investigacion/grupos/artes/ingles/index.php3
 *   Instituto de Ingenieria Electrica, Facultad de Ingenieria,
 *   Universidad de la Republica, Uruguay.
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
 *
 */

#ifndef INCLUDED_MER_QAM_DESROTATOR_CF_IMPL_H
#define INCLUDED_MER_QAM_DESROTATOR_CF_IMPL_H

#include <mer/qam_desrotator_cf.h>

namespace gr {
namespace mer {

class qam_desrotator_cf_impl : public qam_desrotator_cf
{
private:
    int d_cell_size;
    double d_rotation_angle;
    // Nothing to declare in this block.

public:
    qam_desrotator_cf_impl(int mod_index, int cell_size);
    ~qam_desrotator_cf_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace mer
} // namespace gr

#endif /* INCLUDED_MER_QAM_DESROTATOR_CF_IMPL_H */
