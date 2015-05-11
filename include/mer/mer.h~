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


#ifndef INCLUDED_MER_MER_H
#define INCLUDED_MER_MER_H

#include <mer/api.h>

namespace gr {
  namespace mer {

    /*!
     * \brief <+description+>
     *
     */
    class MER_API mer
    {
    public:
    	mer(double alpha);
    	~mer();
        double update_mer(gr_complex iq,gr_complex iq_true);
	double update_avg_tx_power(gr_complex iq_true);
	double update_avg_error_power(gr_complex iq,gr_complex iq_true);
    private:
	double d_alpha;	
      	double d_avgtxsignal_power;
      	double d_avgerror_power;
    };

  } // namespace mer
} // namespace gr

#endif /* INCLUDED_MER_MER_H */

