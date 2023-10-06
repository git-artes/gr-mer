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
		const float d_th_256qam = 2.0/sqrt(170.0); 

		bool d_isdbt_constellation;
		bool d_dvbt2_constellation;

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
        
		const gr_complex demapper::d_constellation_256qam[] = {
			gr_complex(15/sqrt(170),15/sqrt(170)), //00000000
			gr_complex(15/sqrt(170),13/sqrt(170)), //00000001
			gr_complex(13/sqrt(170),15/sqrt(170)), //00000010
			gr_complex(13/sqrt(170),13/sqrt(170)), //00000011
			gr_complex(15/sqrt(170),9/sqrt(170)), //00000100
			gr_complex(15/sqrt(170),11/sqrt(170)), //00000101
			gr_complex(13/sqrt(170),9/sqrt(170)), //00000110
			gr_complex(13/sqrt(170),11/sqrt(170)), //00000111
			gr_complex(9/sqrt(170),15/sqrt(170)), //00001000
			gr_complex(9/sqrt(170),13/sqrt(170)), //00001001
			gr_complex(11/sqrt(170),15/sqrt(170)), //00001010
			gr_complex(11/sqrt(170),13/sqrt(170)), //00001011
			gr_complex(9/sqrt(170),9/sqrt(170)), //00001100
			gr_complex(9/sqrt(170),11/sqrt(170)), //00001101
			gr_complex(11/sqrt(170),9/sqrt(170)), //00001110
			gr_complex(11/sqrt(170),11/sqrt(170)), //00001111
			gr_complex(15/sqrt(170),1/sqrt(170)), //00010000
			gr_complex(15/sqrt(170),3/sqrt(170)), //00010001
			gr_complex(13/sqrt(170),1/sqrt(170)), //00010010
			gr_complex(13/sqrt(170),3/sqrt(170)), //00010011
			gr_complex(15/sqrt(170),7/sqrt(170)), //00010100
			gr_complex(15/sqrt(170),5/sqrt(170)), //00010101
			gr_complex(13/sqrt(170),7/sqrt(170)), //00010110
			gr_complex(13/sqrt(170),5/sqrt(170)), //00010111
			gr_complex(9/sqrt(170),1/sqrt(170)), //00011000
			gr_complex(9/sqrt(170),3/sqrt(170)), //00011001
			gr_complex(11/sqrt(170),1/sqrt(170)), //00011010
			gr_complex(11/sqrt(170),3/sqrt(170)), //00011011
			gr_complex(9/sqrt(170),7/sqrt(170)), //00011100
			gr_complex(9/sqrt(170),5/sqrt(170)), //00011101
			gr_complex(11/sqrt(170),7/sqrt(170)), //00011110
			gr_complex(11/sqrt(170),5/sqrt(170)), //00011111
			gr_complex(1/sqrt(170),15/sqrt(170)), //00100000
			gr_complex(1/sqrt(170),13/sqrt(170)), //00100001
			gr_complex(3/sqrt(170),15/sqrt(170)), //00100010
			gr_complex(3/sqrt(170),13/sqrt(170)), //00100011
			gr_complex(1/sqrt(170),9/sqrt(170)), //00100100
			gr_complex(1/sqrt(170),11/sqrt(170)), //00100101
			gr_complex(3/sqrt(170),9/sqrt(170)), //00100110
			gr_complex(3/sqrt(170),11/sqrt(170)), //00100111
			gr_complex(7/sqrt(170),15/sqrt(170)), //00101000
			gr_complex(7/sqrt(170),13/sqrt(170)), //00101001
			gr_complex(5/sqrt(170),15/sqrt(170)), //00101010
			gr_complex(5/sqrt(170),13/sqrt(170)), //00101011
			gr_complex(7/sqrt(170),9/sqrt(170)), //00101100
			gr_complex(7/sqrt(170),11/sqrt(170)), //00101101
			gr_complex(5/sqrt(170),9/sqrt(170)), //00101110
			gr_complex(5/sqrt(170),11/sqrt(170)), //00101111
			gr_complex(1/sqrt(170),1/sqrt(170)), //00110000
			gr_complex(1/sqrt(170),3/sqrt(170)), //00110001
			gr_complex(3/sqrt(170),1/sqrt(170)), //00110010
			gr_complex(3/sqrt(170),3/sqrt(170)), //00110011
			gr_complex(1/sqrt(170),7/sqrt(170)), //00110100
			gr_complex(1/sqrt(170),5/sqrt(170)), //00110101
			gr_complex(3/sqrt(170),7/sqrt(170)), //00110110
			gr_complex(3/sqrt(170),5/sqrt(170)), //00110111
			gr_complex(7/sqrt(170),1/sqrt(170)), //00111000
			gr_complex(7/sqrt(170),3/sqrt(170)), //00111001
			gr_complex(5/sqrt(170),1/sqrt(170)), //00111010
			gr_complex(5/sqrt(170),3/sqrt(170)), //00111011
			gr_complex(7/sqrt(170),7/sqrt(170)), //00111100
			gr_complex(7/sqrt(170),5/sqrt(170)), //00111101
			gr_complex(5/sqrt(170),7/sqrt(170)), //00111110
			gr_complex(5/sqrt(170),5/sqrt(170)), //00111111
			gr_complex(15/sqrt(170),-15/sqrt(170)), //01000000
			gr_complex(15/sqrt(170),-13/sqrt(170)), //01000001
			gr_complex(13/sqrt(170),-15/sqrt(170)), //01000010
			gr_complex(13/sqrt(170),-13/sqrt(170)), //01000011
			gr_complex(15/sqrt(170),-9/sqrt(170)), //01000100
			gr_complex(15/sqrt(170),-11/sqrt(170)), //01000101
			gr_complex(13/sqrt(170),-9/sqrt(170)), //01000110
			gr_complex(13/sqrt(170),-11/sqrt(170)), //01000111
			gr_complex(9/sqrt(170),-15/sqrt(170)), //01001000
			gr_complex(9/sqrt(170),-13/sqrt(170)), //01001001
			gr_complex(11/sqrt(170),-15/sqrt(170)), //01001010
			gr_complex(11/sqrt(170),-13/sqrt(170)), //01001011
			gr_complex(9/sqrt(170),-9/sqrt(170)), //01001100
			gr_complex(9/sqrt(170),-11/sqrt(170)), //01001101
			gr_complex(11/sqrt(170),-9/sqrt(170)), //01001110
			gr_complex(11/sqrt(170),-11/sqrt(170)), //01001111
			gr_complex(15/sqrt(170),-1/sqrt(170)), //01010000
			gr_complex(15/sqrt(170),-3/sqrt(170)), //01010001
			gr_complex(13/sqrt(170),-1/sqrt(170)), //01010010
			gr_complex(13/sqrt(170),-3/sqrt(170)), //01010011
			gr_complex(15/sqrt(170),-7/sqrt(170)), //01010100
			gr_complex(15/sqrt(170),-5/sqrt(170)), //01010101
			gr_complex(13/sqrt(170),-7/sqrt(170)), //01010110
			gr_complex(13/sqrt(170),-5/sqrt(170)), //01010111
			gr_complex(9/sqrt(170),-1/sqrt(170)), //01011000
			gr_complex(9/sqrt(170),-3/sqrt(170)), //01011001
			gr_complex(11/sqrt(170),-1/sqrt(170)), //01011010
			gr_complex(11/sqrt(170),-3/sqrt(170)), //01011011
			gr_complex(9/sqrt(170),-7/sqrt(170)), //01011100
			gr_complex(9/sqrt(170),-5/sqrt(170)), //01011101
			gr_complex(11/sqrt(170),-7/sqrt(170)), //01011110
			gr_complex(11/sqrt(170),-5/sqrt(170)), //01011111
			gr_complex(1/sqrt(170),-15/sqrt(170)), //01100000
			gr_complex(1/sqrt(170),-13/sqrt(170)), //01100001
			gr_complex(3/sqrt(170),-15/sqrt(170)), //01100010
			gr_complex(3/sqrt(170),-13/sqrt(170)), //01100011
			gr_complex(1/sqrt(170),-9/sqrt(170)), //01100100
			gr_complex(1/sqrt(170),-11/sqrt(170)), //01100101
			gr_complex(3/sqrt(170),-9/sqrt(170)), //01100110
			gr_complex(3/sqrt(170),-11/sqrt(170)), //01100111
			gr_complex(7/sqrt(170),-15/sqrt(170)), //01101000
			gr_complex(7/sqrt(170),-13/sqrt(170)), //01101001
			gr_complex(5/sqrt(170),-15/sqrt(170)), //01101010
			gr_complex(5/sqrt(170),-13/sqrt(170)), //01101011
			gr_complex(7/sqrt(170),-9/sqrt(170)), //01101100
			gr_complex(7/sqrt(170),-11/sqrt(170)), //01101101
			gr_complex(5/sqrt(170),-9/sqrt(170)), //01101110
			gr_complex(5/sqrt(170),-11/sqrt(170)), //01101111
			gr_complex(1/sqrt(170),-1/sqrt(170)), //01110000
			gr_complex(1/sqrt(170),-3/sqrt(170)), //01110001
			gr_complex(3/sqrt(170),-1/sqrt(170)), //01110010
			gr_complex(3/sqrt(170),-3/sqrt(170)), //01110011
			gr_complex(1/sqrt(170),-7/sqrt(170)), //01110100
			gr_complex(1/sqrt(170),-5/sqrt(170)), //01110101
			gr_complex(3/sqrt(170),-7/sqrt(170)), //01110110
			gr_complex(3/sqrt(170),-5/sqrt(170)), //01110111
			gr_complex(7/sqrt(170),-1/sqrt(170)), //01111000
			gr_complex(7/sqrt(170),-3/sqrt(170)), //01111001
			gr_complex(5/sqrt(170),-1/sqrt(170)), //01111010
			gr_complex(5/sqrt(170),-3/sqrt(170)), //01111011
			gr_complex(7/sqrt(170),-7/sqrt(170)), //01111100
			gr_complex(7/sqrt(170),-5/sqrt(170)), //01111101
			gr_complex(5/sqrt(170),-7/sqrt(170)), //01111110
			gr_complex(5/sqrt(170),-5/sqrt(170)), //01111111
			gr_complex(-15/sqrt(170),15/sqrt(170)), //10000000
			gr_complex(-15/sqrt(170),13/sqrt(170)), //10000001
			gr_complex(-13/sqrt(170),15/sqrt(170)), //10000010
			gr_complex(-13/sqrt(170),13/sqrt(170)), //10000011
			gr_complex(-15/sqrt(170),9/sqrt(170)), //10000100
			gr_complex(-15/sqrt(170),11/sqrt(170)), //10000101
			gr_complex(-13/sqrt(170),9/sqrt(170)), //10000110
			gr_complex(-13/sqrt(170),11/sqrt(170)), //10000111
			gr_complex(-9/sqrt(170),15/sqrt(170)), //10001000
			gr_complex(-9/sqrt(170),13/sqrt(170)), //10001001
			gr_complex(-11/sqrt(170),15/sqrt(170)), //10001010
			gr_complex(-11/sqrt(170),13/sqrt(170)), //10001011
			gr_complex(-9/sqrt(170),9/sqrt(170)), //10001100
			gr_complex(-9/sqrt(170),11/sqrt(170)), //10001101
			gr_complex(-11/sqrt(170),9/sqrt(170)), //10001110
			gr_complex(-11/sqrt(170),11/sqrt(170)), //10001111
			gr_complex(-15/sqrt(170),1/sqrt(170)), //10010000
			gr_complex(-15/sqrt(170),3/sqrt(170)), //10010001
			gr_complex(-13/sqrt(170),1/sqrt(170)), //10010010
			gr_complex(-13/sqrt(170),3/sqrt(170)), //10010011
			gr_complex(-15/sqrt(170),7/sqrt(170)), //10010100
			gr_complex(-15/sqrt(170),5/sqrt(170)), //10010101
			gr_complex(-13/sqrt(170),7/sqrt(170)), //10010110
			gr_complex(-13/sqrt(170),5/sqrt(170)), //10010111
			gr_complex(-9/sqrt(170),1/sqrt(170)), //10011000
			gr_complex(-9/sqrt(170),3/sqrt(170)), //10011001
			gr_complex(-11/sqrt(170),1/sqrt(170)), //10011010
			gr_complex(-11/sqrt(170),3/sqrt(170)), //10011011
			gr_complex(-9/sqrt(170),7/sqrt(170)), //10011100
			gr_complex(-9/sqrt(170),5/sqrt(170)), //10011101
			gr_complex(-11/sqrt(170),7/sqrt(170)), //10011110
			gr_complex(-11/sqrt(170),5/sqrt(170)), //10011111
			gr_complex(-1/sqrt(170),15/sqrt(170)), //10100000
			gr_complex(-1/sqrt(170),13/sqrt(170)), //10100001
			gr_complex(-3/sqrt(170),15/sqrt(170)), //10100010
			gr_complex(-3/sqrt(170),13/sqrt(170)), //10100011
			gr_complex(-1/sqrt(170),9/sqrt(170)), //10100100
			gr_complex(-1/sqrt(170),11/sqrt(170)), //10100101
			gr_complex(-3/sqrt(170),9/sqrt(170)), //10100110
			gr_complex(-3/sqrt(170),11/sqrt(170)), //10100111
			gr_complex(-7/sqrt(170),15/sqrt(170)), //10101000
			gr_complex(-7/sqrt(170),13/sqrt(170)), //10101001
			gr_complex(-5/sqrt(170),15/sqrt(170)), //10101010
			gr_complex(-5/sqrt(170),13/sqrt(170)), //10101011
			gr_complex(-7/sqrt(170),9/sqrt(170)), //10101100
			gr_complex(-7/sqrt(170),11/sqrt(170)), //10101101
			gr_complex(-5/sqrt(170),9/sqrt(170)), //10101110
			gr_complex(-5/sqrt(170),11/sqrt(170)), //10101111
			gr_complex(-1/sqrt(170),1/sqrt(170)), //10110000
			gr_complex(-1/sqrt(170),3/sqrt(170)), //10110001
			gr_complex(-3/sqrt(170),1/sqrt(170)), //10110010
			gr_complex(-3/sqrt(170),3/sqrt(170)), //10110011
			gr_complex(-1/sqrt(170),7/sqrt(170)), //10110100
			gr_complex(-1/sqrt(170),5/sqrt(170)), //10110101
			gr_complex(-3/sqrt(170),7/sqrt(170)), //10110110
			gr_complex(-3/sqrt(170),5/sqrt(170)), //10110111
			gr_complex(-7/sqrt(170),1/sqrt(170)), //10111000
			gr_complex(-7/sqrt(170),3/sqrt(170)), //10111001
			gr_complex(-5/sqrt(170),1/sqrt(170)), //10111010
			gr_complex(-5/sqrt(170),3/sqrt(170)), //10111011
			gr_complex(-7/sqrt(170),7/sqrt(170)), //10111100
			gr_complex(-7/sqrt(170),5/sqrt(170)), //10111101
			gr_complex(-5/sqrt(170),7/sqrt(170)), //10111110
			gr_complex(-5/sqrt(170),5/sqrt(170)), //10111111
			gr_complex(-15/sqrt(170),-15/sqrt(170)), //11000000
			gr_complex(-15/sqrt(170),-13/sqrt(170)), //11000001
			gr_complex(-13/sqrt(170),-15/sqrt(170)), //11000010
			gr_complex(-13/sqrt(170),-13/sqrt(170)), //11000011
			gr_complex(-15/sqrt(170),-9/sqrt(170)), //11000100
			gr_complex(-15/sqrt(170),-11/sqrt(170)), //11000101
			gr_complex(-13/sqrt(170),-9/sqrt(170)), //11000110
			gr_complex(-13/sqrt(170),-11/sqrt(170)), //11000111
			gr_complex(-9/sqrt(170),-15/sqrt(170)), //11001000
			gr_complex(-9/sqrt(170),-13/sqrt(170)), //11001001
			gr_complex(-11/sqrt(170),-15/sqrt(170)), //11001010
			gr_complex(-11/sqrt(170),-13/sqrt(170)), //11001011
			gr_complex(-9/sqrt(170),-9/sqrt(170)), //11001100
			gr_complex(-9/sqrt(170),-11/sqrt(170)), //11001101
			gr_complex(-11/sqrt(170),-9/sqrt(170)), //11001110
			gr_complex(-11/sqrt(170),-11/sqrt(170)), //11001111
			gr_complex(-15/sqrt(170),-1/sqrt(170)), //11010000
			gr_complex(-15/sqrt(170),-3/sqrt(170)), //11010001
			gr_complex(-13/sqrt(170),-1/sqrt(170)), //11010010
			gr_complex(-13/sqrt(170),-3/sqrt(170)), //11010011
			gr_complex(-15/sqrt(170),-7/sqrt(170)), //11010100
			gr_complex(-15/sqrt(170),-5/sqrt(170)), //11010101
			gr_complex(-13/sqrt(170),-7/sqrt(170)), //11010110
			gr_complex(-13/sqrt(170),-5/sqrt(170)), //11010111
			gr_complex(-9/sqrt(170),-1/sqrt(170)), //11011000
			gr_complex(-9/sqrt(170),-3/sqrt(170)), //11011001
			gr_complex(-11/sqrt(170),-1/sqrt(170)), //11011010
			gr_complex(-11/sqrt(170),-3/sqrt(170)), //11011011
			gr_complex(-9/sqrt(170),-7/sqrt(170)), //11011100
			gr_complex(-9/sqrt(170),-5/sqrt(170)), //11011101
			gr_complex(-11/sqrt(170),-7/sqrt(170)), //11011110
			gr_complex(-11/sqrt(170),-5/sqrt(170)), //11011111
			gr_complex(-1/sqrt(170),-15/sqrt(170)), //11100000
			gr_complex(-1/sqrt(170),-13/sqrt(170)), //11100001
			gr_complex(-3/sqrt(170),-15/sqrt(170)), //11100010
			gr_complex(-3/sqrt(170),-13/sqrt(170)), //11100011
			gr_complex(-1/sqrt(170),-9/sqrt(170)), //11100100
			gr_complex(-1/sqrt(170),-11/sqrt(170)), //11100101
			gr_complex(-3/sqrt(170),-9/sqrt(170)), //11100110
			gr_complex(-3/sqrt(170),-11/sqrt(170)), //11100111
			gr_complex(-7/sqrt(170),-15/sqrt(170)), //11101000
			gr_complex(-7/sqrt(170),-13/sqrt(170)), //11101001
			gr_complex(-5/sqrt(170),-15/sqrt(170)), //11101010
			gr_complex(-5/sqrt(170),-13/sqrt(170)), //11101011
			gr_complex(-7/sqrt(170),-9/sqrt(170)), //11101100
			gr_complex(-7/sqrt(170),-11/sqrt(170)), //11101101
			gr_complex(-5/sqrt(170),-9/sqrt(170)), //11101110
			gr_complex(-5/sqrt(170),-11/sqrt(170)), //11101111
			gr_complex(-1/sqrt(170),-1/sqrt(170)), //11110000
			gr_complex(-1/sqrt(170),-3/sqrt(170)), //11110001
			gr_complex(-3/sqrt(170),-1/sqrt(170)), //11110010
			gr_complex(-3/sqrt(170),-3/sqrt(170)), //11110011
			gr_complex(-1/sqrt(170),-7/sqrt(170)), //11110100
			gr_complex(-1/sqrt(170),-5/sqrt(170)), //11110101
			gr_complex(-3/sqrt(170),-7/sqrt(170)), //11110110
			gr_complex(-3/sqrt(170),-5/sqrt(170)), //11110111
			gr_complex(-7/sqrt(170),-1/sqrt(170)), //11111000
			gr_complex(-7/sqrt(170),-3/sqrt(170)), //11111001
			gr_complex(-5/sqrt(170),-1/sqrt(170)), //11111010
			gr_complex(-5/sqrt(170),-3/sqrt(170)), //11111011
			gr_complex(-7/sqrt(170),-7/sqrt(170)), //11111100
			gr_complex(-7/sqrt(170),-5/sqrt(170)), //11111101
			gr_complex(-5/sqrt(170),-7/sqrt(170)), //11111110
			gr_complex(-5/sqrt(170),-5/sqrt(170)), //11111111
		};

        demapper::demapper(const std::vector<gr_complex> map)
        {
            d_isdbt_constellation=true;
			d_dvbt2_constellation=false;
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
				case 256:
						d_dvbt2_constellation = true;
						d_isdbt_constellation = false;
						break;		
				default:
						d_isdbt_constellation = false;
						break;
			}
			
			if (d_isdbt_constellation) printf("Detected ISDB-T's %s constellation\n", (d_const_size==4)?"QPSK":(d_const_size==16)?"16QAM":"64QAM");
			if (d_dvbt2_constellation) printf("Detected DVB-T2 %s constellation\n", "256QAM");
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

					case 256:
						return ((val.real()<0)<<7) | ((val.imag()<0)<<6) | ((val.real()>4*d_th_256qam & val.real()<4*d_th_256qam)<<5) | \
						((val.imag()>-4*d_th_256qam & val.imag()<4*d_th_256qam)<<4) |((val.real()>-6*d_th_256qam & val.real()<-2*d_th_256qam)<<3) | \
						((val.real()>2*d_th_256qam & val.real()<6*d_th_256qam)<<3) | ((val.imag()>2*d_th_256qam & val.imag()<6*d_th_256qam)<<2) | \
						((val.imag()<-2*d_th_256qam & val.imag()>-6*d_th_256qam)<<2) | ((val.real()<-d_th_256qam & val.real()>-7*d_th_256qam)<<1) | \
						((val.real()>d_th_256qam & val.real()<7*d_th_256qam)<<1) | ((val.imag()>5*d_th_256qam & val.imag()<7*d_th_256qam)) | \
						((val.imag()>d_th_256qam & val.imag()<3*d_th_256qam)) |((val.imag()>-3*d_th_256qam & val.imag()<-d_th_256qam)) | \
						((val.imag()>-7*d_th_256qam & val.imag()<-5*d_th_256qam));
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

