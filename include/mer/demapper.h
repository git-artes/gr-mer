/* -*- c++ -*- */
/*
 * Copyright 2023,2015
 * Pablo Belzarena <belza@fing.edu.uy>, Gabriel Gomez,  Victor Gonzalez-Barbone, Pablo Flores Guridi, Federico Larroca, Gonzalo Belcredi. 
 * ARTES Group
 * http://iie.fing.edu.uy/investigacion/grupos/artes/ingles/index.php3
 * Instituto de Ingenieria Electrica, Facultad de Ingenieria,
 * Universidad de la Republica, Uruguay.
 *
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_DEMAPPER_H
#define INCLUDED_DEMAPPER_H

#include <mer/api.h>
#include <gnuradio/gr_complex.h>
#include <stdio.h>
#include <vector>

namespace gr {
  namespace mer {
  
      /*!
     * \brief Probe Digital Modulation measurements.
     * \ingroup mer
     *
     * MER API demapper.
     */
	class  MER_API demapper
	{
	protected:
	    static const gr_complex d_constellation_qpsk[]; 
        static const gr_complex d_constellation_16qam[]; 
        static const gr_complex d_constellation_64qam[];
        int d_const_size;
		double d_re_min;
		double d_im_min;
		double d_re_max;
		double d_im_max;
	 	void max_min_axes();

                //const gr_complex * d_constellation; 

	public:
		demapper(const std::vector<gr_complex> map);
        	~demapper();
		//std::vector<gr_complex>  d_map;
        	int demap(gr_complex val);
 		gr_complex demap(gr_complex val, int &index);
		std::vector<gr_complex> d_constellation; 
		gr_complex left_down_contellation(int &decimal_point);
		gr_complex left_up_contellation(int &decimal_point);
		gr_complex right_down_contellation(int &decimal_point);
		gr_complex right_up_contellation(int &decimal_point);
	
	};

   } /* namespace mer */
} /* namespace gr */



#endif /* INCLUDED_DEMAPPER_H */
