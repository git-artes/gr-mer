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
# CARRIER SUPPRESSION ERROR TEST
# We estimate the carrier suppression error finding the DC offset of the samples. The constellation is systematically translated  by a fixed vector.
# We estimates the average translation vector.The cs value is the residual carrier power normalized to the tx average power.
# # This test analize a global traslation of the constellation.
# We compare the theoretical CS value  with the probe_cs estimation.



from gnuradio import gr, gr_unittest
from gnuradio import blocks
import mer as mer
import numpy as np

class qa_probe_cs_cf (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
      	# to test a complex distorsion added to the symbols that translates all symbols by a constant value
	# Each vector has all constellation values
	number_of_vectors = 5000
	dim_constellation = 16
	# real and imaginary part of the distorsion added to the symbols
	distorsion_real = 0.1
	distorsion_imag =0.1
	# call the probe_mer constructor with the symbol table and alpha value for averaging
 	self.mer_probe_cs_cf_0 = mer.probe_cs_cf((0.9487+0.9487j,0.9487+0.3162j, 0.3162+0.9487j, 0.3162 +0.3162j,0.9487-0.9487j,0.9487- 0.3162j, 0.3162-0.9487j, 0.3162- 0.3162j,-0.9487+0.9487j,-0.9487+ 0.3162j,- 0.3162+0.9487j,- 0.3162+ 0.3162j,-0.9487-0.9487j,-0.9487- 0.3162j,-0.3162-0.9487j,-0.3162- 0.3162j),0.005)
        #source data to test is a vector of the cosntellation table * number_of_vectors
        src_data = (0.9487+0.9487j,0.9487+0.3162j, 0.3162+0.9487j, 0.3162 +0.3162j,0.9487-0.9487j,0.9487- 0.3162j, 0.3162-0.9487j, 0.3162- 0.3162j,-0.9487+0.9487j,-0.9487+ 0.3162j,- 0.3162+0.9487j,- 0.3162+ 0.3162j,-0.9487-0.9487j,-0.9487- 0.3162j,-0.3162-0.9487j,-0.3162- 0.3162j)*number_of_vectors
	# Add the aditive distorsion to the source data
	src_data = [x+distorsion_real+distorsion_imag*(1j) for x in src_data]
	# create a vector source with the source data and a vector sink block to receive the CS value
        self.src = blocks.vector_source_c(src_data,False)
	self.dst0 = blocks.vector_sink_f()
	#Connect the blocks
        self.tb.connect((self.src, 0), (self.mer_probe_cs_cf_0, 0))    
        self.tb.connect((self.mer_probe_cs_cf_0, 0),(self.dst0, 0))    
	self.tb.run ()   
	# The CS result is the average of the last values of received in the destination vector	
	result_data1 = np.mean(self.dst0.data()[number_of_vectors*dim_constellation-dim_constellation:number_of_vectors*dim_constellation])
	print " result cs = ", result_data1
	#Calculate the theoretical CS error from the distorsion values	
	cs = distorsion_real*distorsion_real+distorsion_imag*distorsion_imag
	print " expected result = ", cs
	expected_result1 = cs
	#Tests that the error is less than 0.1%
	self.assertLessEqual(abs((result_data1-expected_result1)/expected_result1), 0.001 )


if __name__ == '__main__':
    gr_unittest.run(qa_probe_cs_cf, "qa_probe_cs_cf.xml")
