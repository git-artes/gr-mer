#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 
# Copyright 2015 <ARTES Group, Universidad de la República, Uruguay>.
# http://iie.fing.edu.uy/investigacion/grupos/artes/ingles/index.php3
# 
# This is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
# 
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this software; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
# 

#
# AMPLITUDE IMBALANCE ERROR TEST
# We estimate the amplitude imbalance error finding the  contraction or expansion vector of the constellation. 
# # This test analize a global contraction or expansion of the constellation.
# We compare the theoretical AI value  with the probe_ai estimation.
#

from gnuradio import gr, gr_unittest
from gnuradio import blocks
import mer as mer
import numpy as np

class qa_probe_ai_cf (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
  	#The amplitudo imabalnce is obtained multiplying all symbols by a constat multiplicative distosion
	# Each vector has all constellation values
	number_of_vectors = 1000
	dim_constellation = 16
	#constant multiplicative distorsion factor for real and imaginary part
	distorsion_real = 1.122
	distorsion_imag = 0.95
	# call the probe_mer constructor with the symbol table and alpha value for averaging
 	self.mer_probe_ai_cf_0 = mer.probe_ai_cf((0.9487+0.9487j,0.9487+0.3162j, 0.3162+0.9487j, 0.3162 +0.3162j,0.9487-0.9487j,0.9487- 0.3162j, 0.3162-0.9487j, 0.3162- 0.3162j,-0.9487+0.9487j,-0.9487+ 0.3162j,- 0.3162+0.9487j,- 0.3162+ 0.3162j,-0.9487-0.9487j,-0.9487- 0.3162j,-0.3162-0.9487j,-0.3162- 0.3162j),0.005)
        #source data to test is a vector of the cosntellation table * number_of_vectors
        src_const = (0.9487+0.9487j,0.9487+0.3162j, 0.3162+0.9487j, 0.3162 +0.3162j,0.9487-0.9487j,0.9487- 0.3162j, 0.3162-0.9487j, 0.3162- 0.3162j,-0.9487+0.9487j,-0.9487+ 0.3162j,- 0.3162+0.9487j,- 0.3162+ 0.3162j,-0.9487-0.9487j,-0.9487- 0.3162j,-0.3162-0.9487j,-0.3162- 0.3162j)*number_of_vectors
	#multiply the real and imaginary part of the the source data by the corresponding distorsion factor
	src_data = [x.real*distorsion_real+x.imag * distorsion_imag*(1j) for x in src_const]
	#create a vector source with the source data and two vector sink blocks to receive the real and imaginary AI values
        self.src = blocks.vector_source_c(src_data,False)
	self.dst0 = blocks.vector_sink_f()
        self.dst1 = blocks.vector_sink_f()
	#connect blocks
        self.tb.connect((self.src, 0), (self.mer_probe_ai_cf_0, 0))    
        self.tb.connect((self.mer_probe_ai_cf_0, 0),(self.dst0, 0))    
        self.tb.connect((self.mer_probe_ai_cf_0, 1),(self.dst1, 0))    
	self.tb.run () 
	#The AI error result is the average of the last values of received in the destination vector		  
	result_data1 = np.mean(self.dst0.data()[number_of_vectors*dim_constellation-dim_constellation:number_of_vectors*dim_constellation])+1
	result_data2 = np.mean(self.dst1.data()[number_of_vectors*dim_constellation-dim_constellation:number_of_vectors*dim_constellation])+1
	print " result real part = ", result_data1
	print " result imaginary part = ", result_data2

	expected_result1 = distorsion_real
	print " expected result real part = ", expected_result1
	expected_result2 = distorsion_imag
	print " expected result real part = ", expected_result2
	#test error less than 0.1%	
	self.assertLessEqual(abs((result_data1-expected_result1)/expected_result1), 0.001 )
	self.assertLessEqual(abs((result_data2-expected_result2)/expected_result2), 0.001 )

if __name__ == '__main__':
    gr_unittest.run(qa_probe_ai_cf, "qa_probe_ai_cf.xml")
