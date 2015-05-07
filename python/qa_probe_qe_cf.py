#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 
# Copyright 2015 <+YOU OR YOUR COMPANY+>.
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

from gnuradio import gr, gr_unittest
from gnuradio import blocks
import mer as mer
import numpy as np
class qa_probe_qe_cf (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):

  	#to test a constat multiplicative distosion to the symbols
	number_of_vectors = 1000
	dim_constellation = 16
	#distorsions in degrees
	phi_vert = 1 
	phi_hor =3

 	self.mer_probe_qe_cf_0 = mer.probe_qe_cf((0.9487+0.9487j,0.9487+0.3162j, 0.3162+0.9487j, 0.3162 +0.3162j,0.9487-0.9487j,0.9487- 0.3162j, 0.3162-0.9487j, 0.3162- 0.3162j,-0.9487+0.9487j,-0.9487+ 0.3162j,- 0.3162+0.9487j,- 0.3162+ 0.3162j,-0.9487-0.9487j,-0.9487- 0.3162j,-0.3162-0.9487j,-0.3162- 0.3162j),0.005)
        
        src_const = (0.9487+0.9487j,0.9487+0.3162j, 0.3162+0.9487j, 0.3162 +0.3162j,0.9487-0.9487j,0.9487- 0.3162j, 0.3162-0.9487j, 0.3162- 0.3162j,-0.9487+0.9487j,-0.9487+ 0.3162j,- 0.3162+0.9487j,- 0.3162+ 0.3162j,-0.9487-0.9487j,-0.9487- 0.3162j,-0.3162-0.9487j,-0.3162- 0.3162j)*number_of_vectors

	src_data = [x.real + +x.imag * np.sin(phi_hor*3.1416/180)+(x.imag +x.real * np.sin(phi_vert*3.1416/180))*(1j) for x in src_const]
	
        self.src = blocks.vector_source_c(src_data,False)
	self.dst0 = blocks.vector_sink_f()
        self.dst1 = blocks.vector_sink_f()
        self.tb.connect((self.src, 0), (self.mer_probe_qe_cf_0, 0))    
        self.tb.connect((self.mer_probe_qe_cf_0, 0),(self.dst0, 0))    
        self.tb.connect((self.mer_probe_qe_cf_0, 1),(self.dst1, 0))    
	self.tb.run ()   
	result_data1 = np.mean(self.dst0.data()[number_of_vectors*dim_constellation-dim_constellation:number_of_vectors*dim_constellation])
	result_data2 = np.mean(self.dst1.data()[number_of_vectors*dim_constellation-dim_constellation:number_of_vectors*dim_constellation])
	print result_data1
	print result_data2

	expected_result1 = phi_vert
	expected_result2 = phi_hor
	print expected_result1
	print expected_result2

	self.assertLessEqual(abs((result_data1-expected_result1)/expected_result1), 0.01 )
	self.assertLessEqual(abs((result_data2-expected_result2)/expected_result2), 0.01 )



if __name__ == '__main__':
    gr_unittest.run(qa_probe_qe_cf, "qa_probe_qe_cf.xml")
