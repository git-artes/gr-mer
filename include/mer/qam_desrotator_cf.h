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

#ifndef INCLUDED_MER_QAM_DESROTATOR_CF_H
#define INCLUDED_MER_QAM_DESROTATOR_CF_H

#include <gnuradio/sync_block.h>
#include <mer/api.h>

namespace gr {
namespace mer {

/*!
 * \brief <+description of block+>
 * \ingroup mer
 *
 */
class MER_API qam_desrotator_cf : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<qam_desrotator_cf> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of mer::qam_desrotator_cf.
     *
     * To avoid accidental use of raw pointers, mer::qam_desrotator_cf's
     * constructor is in a private implementation
     * class. mer::qam_desrotator_cf::make is the public interface for
     * creating new instances.
     */
    static sptr make(int mod_index, int cell_size);
};

} // namespace mer
} // namespace gr

#endif /* INCLUDED_MER_QAM_DESROTATOR_CF_H */
