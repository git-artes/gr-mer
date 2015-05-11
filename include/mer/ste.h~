/* -*- c++ -*- */
/* 
 * Copyright 2015 <+YOU OR YOUR COMPANY+>.
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


#ifndef INCLUDED_MER_STE_H
#define INCLUDED_MER_STE_H

#include <mer/api.h>

namespace gr {
  namespace mer {

    /*!
     * \brief <+description+>
     *
     */
    class MER_API ste
    {
    public:
    	ste(int dim_constellation,double alpha);
    	~ste();
	double update_ste(gr_complex iq,gr_complex iq_true,int constellation_value);
	double update_stem(gr_complex iq,gr_complex iq_true,int constellation_value,double tx_power);
	double update_sted(gr_complex iq,gr_complex iq_true,int constellation_value,double tx_power);
	gr_complex * update_di(gr_complex iq,gr_complex iq_true,int constellation_value);
    private:
	double d_alpha;
	// di is a vector with the average distance of each cloud center to the corresponding constellation point	
	gr_complex *d_di;
	int d_dim_constellation;
    };

  } // namespace mer
} // namespace gr

#endif /* INCLUDED_MER_STE_H */

