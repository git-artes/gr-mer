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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <mer/demapper.h>
#include <stdexcept>
#include<stdlib.h>
#include <cstdio>

namespace gr {
  namespace mer {
		  
		const float d_th_16qam = 2.0/sqrt(10.0); 
        const float d_th_64qam = 2.0/sqrt(42.0); 
		bool d_isdbt_constellation;

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
            d_isdbt_constellation=true;
			d_const_size = map.size(); 
            d_constellation = map; //d_constellation_16qam;

			switch (d_const_size){
			
				case 4:
						for(int i=0;i<d_const_size;i++)
							if (d_constellation[i]!=d_constellation_qpsk[i])
									d_isdbt_constellation = false;
						break;
				case 16:
						for(int i=0;i<d_const_size;i++)
							if (d_constellation[i]!=d_constellation_16qam[i])
									d_isdbt_constellation = false;
						break;
				case 64:
						for(int i=0;i<d_const_size;i++)
							if (d_constellation[i]!=d_constellation_64qam[i])
									d_isdbt_constellation = false;
						break;			
				default:
						d_isdbt_constellation = false;
						break;
			}
			
			if (d_isdbt_constellation) printf("Detected ISDB-T's %s constellation\n", (d_const_size==4)?"QPSK":(d_const_size==16)?"16QAM":"64QAM");
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
    	demapper::demap(gr_complex val){
			
			if (d_isdbt_constellation){
			
				switch(d_const_size){
					case 4:
                		return (val.real()<0)<<1 | (val.imag()<0); 
						break;

					case 16:
                		return ((val.real()<0)<<3) | ((val.real()<d_th_16qam & val.real()>-d_th_16qam)<<1) | ((val.imag()<0)<<2) | ((val.imag()<d_th_16qam & val.imag()>-d_th_16qam)); 
						break;

					case 64:
                	   return ((val.real()<0)<<5) | ((val.real()<2*d_th_64qam & val.real()>-2*d_th_64qam)<<3) | (( (val.real()>d_th_64qam & val.real()<3*d_th_64qam)|(val.real()<-d_th_64qam & val.real()>-3*d_th_64qam) )<<1) \
                    | ((val.imag()<0)<<4) | ((val.imag()<2*d_th_64qam & val.imag()>-2*d_th_64qam)<<2) | (( (val.imag()>d_th_64qam & val.imag()<3*d_th_64qam)|(val.imag()<-d_th_64qam & val.imag()>-3*d_th_64qam) )) ; 
						break;

					default:
						printf("ERROR! Something went wrong, this cannot be an ISDB-T constellation if it size if different from 4, 16 or 64.\n");
						exit(1);
				}
			}else{
        		float min_dist = std::norm(val - d_constellation[0]);
        		int min_index = 0;
        		for (int i = 0; i < d_const_size; i++){
        	    
					float dist = std::norm(val - d_constellation[i]);
					if (dist < min_dist){
        	        	min_dist = dist;
        	        	min_index = i;
				   	}
				}	
        		return min_index;
			}
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
		aux.real(d_re_min);
		aux.imag(d_im_min); 	
		decimal_point = demap(aux);	
		return aux;
   	}


    gr_complex
    	demapper::right_down_contellation(int &decimal_point){
		gr_complex aux=0; 
		aux.real(d_re_max);
		aux.imag(d_im_min);
		decimal_point = demap(aux);	 
		return aux;   
	}

    gr_complex
    	demapper::right_up_contellation(int &decimal_point){
		gr_complex aux=0; 
		aux.real(d_re_max);
		aux.imag(d_im_max); 
		decimal_point = demap(aux);	
		return aux;
   	}

    gr_complex
    	demapper::left_up_contellation(int &decimal_point){
		gr_complex aux=0; 
		aux.real(d_re_min);
		aux.imag(d_im_max); 
		decimal_point = demap(aux);	
		return aux;
   	}


    } /* namespace mer */
} /* namespace gr */

