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

#include "qam_desrotator_cf_impl.h"
#include <gnuradio/io_signature.h>
#include <gnuradio/math.h>
#include <complex>

namespace gr {
namespace mer {

using input_type = float;
using output_type = float;
qam_desrotator_cf::sptr qam_desrotator_cf::make(int mod_index, int cell_size)
{
    return gnuradio::make_block_sptr<qam_desrotator_cf_impl>(mod_index,cell_size);
}


/*
 * The private constructor
 */
qam_desrotator_cf_impl::qam_desrotator_cf_impl(int mod_index,int cell_size)
    : gr::sync_block("qam_desrotator_cf",
                     gr::io_signature::make(1, 1, sizeof(gr_complex)),
                     gr::io_signature::make(1, 1, sizeof(gr_complex)))
{
    d_cell_size=cell_size;
    switch (mod_index)
    {
    case 4:
        d_rotation_angle = -(2.0 * GR_M_PI * 29.0) / 360.0;
        break;
    case 16:
        d_rotation_angle = -(2.0 * GR_M_PI * 16.8) / 360.0;
        break;
    case 64:
        d_rotation_angle = -(2.0 * GR_M_PI * 8.6) / 360.0;
        break;
    case 256:
        d_rotation_angle = -(2.0 * GR_M_PI * 3.576334375) / 360.0;
        break;    
    default:
        d_rotation_angle = -(2.0 * GR_M_PI * 3.576334375) / 360.0;
        break;
    }
    
    set_output_multiple(cell_size);
}

/*
 * Our virtual destructor.
 */
qam_desrotator_cf_impl::~qam_desrotator_cf_impl() {}

int qam_desrotator_cf_impl::work(int noutput_items,
                                 gr_vector_const_void_star& input_items,
                                 gr_vector_void_star& output_items)
{
    const gr_complex *in = (const gr_complex*)input_items[0];
    gr_complex* out = (gr_complex*)output_items[0];
    
    gr_complex temp;
    temp = std::exp(gr_complexd(0.0, d_rotation_angle));

    // Do <+signal processing+>
    for (int i = 0; i < noutput_items; i += d_cell_size) {
        for (int j = 0; j < d_cell_size; j++) {
            //gr_complex symbol = in[i + j];

            // Compensate for the rotation
            //gr_complex de_rotated_symbol = symbol * temp;

            // Use the real part of the received symbol to determine the imaginary part of the symbol from the previous position in the same cell
            gr_complex corrected_symbol;
            if (j == 0) {
                corrected_symbol = temp * gr_complex(in[i + d_cell_size - 1].real(), in[i + j].imag());
            } else {
                corrected_symbol = temp * gr_complex(in[i + j - 1].real(), in[i + j].imag());
            }
            out[i + j] = corrected_symbol;
        }
    }
    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace mer */
} /* namespace gr */
