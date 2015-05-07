/* -*- c++ -*- */
/*
 * Copyright 2011,2012 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <mer/demapper.h>
#include <stdexcept>
#include <cstdio>

namespace gr {
  namespace mer {
        const gr_complex demapper::d_constellation_qpsk[] = {
            gr_complex(1/sqrt(2),1/sqrt(2)),
            gr_complex(1/sqrt(2),-1/sqrt(2)), 
            gr_complex(-1/sqrt(2),1/sqrt(2)),
            gr_complex(-1/sqrt(2),-1/sqrt(2))
        }; 
        
        const gr_complex demapper::d_constellation_16qam[] = {
            gr_complex(3/sqrt(10),3/sqrt(10)),
            gr_complex(3/sqrt(10),1/sqrt(10)), 
            gr_complex(1/sqrt(10),3/sqrt(10)),
            gr_complex(1/sqrt(10),1/sqrt(10)),

            gr_complex(3/sqrt(10),-3/sqrt(10)),
            gr_complex(3/sqrt(10),-1/sqrt(10)), 
            gr_complex(1/sqrt(10),-3/sqrt(10)),
            gr_complex(1/sqrt(10),-1/sqrt(10)),

            gr_complex(-3/sqrt(10),3/sqrt(10)),
            gr_complex(-3/sqrt(10),1/sqrt(10)), 
            gr_complex(-1/sqrt(10),3/sqrt(10)),
            gr_complex(-1/sqrt(10),1/sqrt(10)),
            
            gr_complex(-3/sqrt(10),-3/sqrt(10)),
            gr_complex(-3/sqrt(10),-1/sqrt(10)), 
            gr_complex(-1/sqrt(10),-3/sqrt(10)),
            gr_complex(-1/sqrt(10),-1/sqrt(10))
        }; 
        
        const gr_complex demapper::d_constellation_64qam[] = {
            gr_complex(7/sqrt(42),7/sqrt(42)),
            gr_complex(7/sqrt(42),5/sqrt(42)), 
            gr_complex(5/sqrt(42),7/sqrt(42)),
            gr_complex(5/sqrt(42),5/sqrt(42)),

            gr_complex(7/sqrt(42),1/sqrt(42)),
            gr_complex(7/sqrt(42),3/sqrt(42)), 
            gr_complex(5/sqrt(42),1/sqrt(42)),
            gr_complex(5/sqrt(42),3/sqrt(42)),

            gr_complex(1/sqrt(42),7/sqrt(42)),
            gr_complex(1/sqrt(42),5/sqrt(42)), 
            gr_complex(3/sqrt(42),7/sqrt(42)),
            gr_complex(3/sqrt(42),5/sqrt(42)),

            gr_complex(1/sqrt(42),1/sqrt(42)),
            gr_complex(1/sqrt(42),3/sqrt(42)), 
            gr_complex(3/sqrt(42),1/sqrt(42)),
            gr_complex(3/sqrt(42),3/sqrt(42)),

            //////////////
            gr_complex(7/sqrt(42),-7/sqrt(42)),
            gr_complex(7/sqrt(42),-5/sqrt(42)), 
            gr_complex(5/sqrt(42),-7/sqrt(42)),
            gr_complex(5/sqrt(42),-5/sqrt(42)),

            gr_complex(7/sqrt(42),-1/sqrt(42)),
            gr_complex(7/sqrt(42),-3/sqrt(42)), 
            gr_complex(5/sqrt(42),-1/sqrt(42)),
            gr_complex(5/sqrt(42),-3/sqrt(42)),

            gr_complex(1/sqrt(42),-7/sqrt(42)),
            gr_complex(1/sqrt(42),-5/sqrt(42)), 
            gr_complex(3/sqrt(42),-7/sqrt(42)),
            gr_complex(3/sqrt(42),-5/sqrt(42)),

            gr_complex(1/sqrt(42),-1/sqrt(42)),
            gr_complex(1/sqrt(42),-3/sqrt(42)), 
            gr_complex(3/sqrt(42),-1/sqrt(42)),
            gr_complex(3/sqrt(42),-3/sqrt(42)),

            //////////////
            gr_complex(-7/sqrt(42),7/sqrt(42)),
            gr_complex(-7/sqrt(42),5/sqrt(42)), 
            gr_complex(-5/sqrt(42),7/sqrt(42)),
            gr_complex(-5/sqrt(42),5/sqrt(42)),

            gr_complex(-7/sqrt(42),1/sqrt(42)),
            gr_complex(-7/sqrt(42),3/sqrt(42)), 
            gr_complex(-5/sqrt(42),1/sqrt(42)),
            gr_complex(-5/sqrt(42),3/sqrt(42)),

            gr_complex(-1/sqrt(42),7/sqrt(42)),
            gr_complex(-1/sqrt(42),5/sqrt(42)), 
            gr_complex(-3/sqrt(42),7/sqrt(42)),
            gr_complex(-3/sqrt(42),5/sqrt(42)),

            gr_complex(-1/sqrt(42),1/sqrt(42)),
            gr_complex(-1/sqrt(42),3/sqrt(42)), 
            gr_complex(-3/sqrt(42),1/sqrt(42)),
            gr_complex(-3/sqrt(42),3/sqrt(42)),

            //////////////
            gr_complex(-7/sqrt(42),-7/sqrt(42)),
            gr_complex(-7/sqrt(42),-5/sqrt(42)), 
            gr_complex(-5/sqrt(42),-7/sqrt(42)),
            gr_complex(-5/sqrt(42),-5/sqrt(42)),

            gr_complex(-7/sqrt(42),-1/sqrt(42)),
            gr_complex(-7/sqrt(42),-3/sqrt(42)), 
            gr_complex(-5/sqrt(42),-1/sqrt(42)),
            gr_complex(-5/sqrt(42),-3/sqrt(42)),

            gr_complex(-1/sqrt(42),-7/sqrt(42)),
            gr_complex(-1/sqrt(42),-5/sqrt(42)), 
            gr_complex(-3/sqrt(42),-7/sqrt(42)),
            gr_complex(-3/sqrt(42),-5/sqrt(42)),

            gr_complex(-1/sqrt(42),-1/sqrt(42)),
            gr_complex(-1/sqrt(42),-3/sqrt(42)), 
            gr_complex(-3/sqrt(42),-1/sqrt(42)),
            gr_complex(-3/sqrt(42),-3/sqrt(42)),
        }; 
        demapper::demapper(const std::vector<gr_complex> map)
        {
            d_const_size = map.size(); 
            d_constellation = map; //d_constellation_16qam; 
	    d_re_min = 1e20;
	    d_im_min = 1e20;
	    d_re_max = -1e20;
	    d_im_max = -1e20;
	    max_min_axes();
        }


        demapper::~demapper()
        {
        }

        int 
    	demapper::demap(gr_complex val)
    	{
        	float min_dist = std::norm(val - d_constellation[0]);
        	int min_index = 0;
        	for (int i = 0; i < d_const_size; i++)
        	{
        	    float dist = std::norm(val - d_constellation[i]);
	
        	    if (dist < min_dist)
        	    {
        	        min_dist = dist;
        	        min_index = i;
        	    }
        	}	
        	return min_index;
    	}


 	gr_complex 
    	demapper::demap(gr_complex val, int &index)
    	{
		gr_complex ret;
		index = demap(val);
		ret = d_constellation[index];
        	return ret;
    	}


	void
	demapper::max_min_axes()
	{
      		// Find min/max of constellation for both real and imag axes.
      		d_re_min = 1e20;
      		d_im_min = 1e20;
      		d_re_max = -1e20;
      		d_im_max = -1e20;
      		for(size_t i = 0; i < d_constellation.size(); i++) {
        		if(d_constellation[i].real() > d_re_max)
          			d_re_max = d_constellation[i].real();
        		if(d_constellation[i].imag() > d_im_max)
          			d_im_max = d_constellation[i].imag();
		        if(d_constellation[i].real() < d_re_min)
          			d_re_min = d_constellation[i].real();
        		if(d_constellation[i].imag() < d_im_min)
          			d_im_min = d_constellation[i].imag();
      		}
      		if(d_im_min == 0)
        		d_im_min = d_re_min;
      		if(d_im_max == 0)
        		d_im_max = d_re_max;
      		if(d_re_min == 0)
        		d_re_min = d_im_min;
      		if(d_re_max == 0)
        		d_re_max = d_im_max;
    	}

 	gr_complex
    	demapper::left_down_contellation(int &decimal_point){
		gr_complex aux=0; 
		real(aux) = d_re_min;
		imag(aux) = d_im_min; 	
		decimal_point = demap(aux);	
		return aux;
   	}


    	gr_complex
    	demapper::right_down_contellation(int &decimal_point){
		gr_complex aux=0; 
		real(aux) = d_re_max;
		imag(aux) = d_im_min;
		decimal_point = demap(aux);	 
		return aux;   
	}

    	gr_complex
    	demapper::right_up_contellation(int &decimal_point){
		gr_complex aux=0; 
		real(aux) = d_re_max;
		imag(aux) = d_im_max; 
		decimal_point = demap(aux);	
		return aux;
   	}
    	gr_complex
    	demapper::left_up_contellation(int &decimal_point){
		gr_complex aux=0; 
		real(aux) = d_re_min;
		imag(aux) = d_im_max; 
		decimal_point = demap(aux);	
		return aux;
   	}


    } /* namespace mer */
} /* namespace gr */

