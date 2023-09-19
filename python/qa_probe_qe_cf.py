#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 
# Copyright 2023,2015
# Pablo Belzarena <belza@fing.edu.uy>, Gabriel Gomez,  Victor Gonzalez-Barbone, Pablo Flores Guridi, Federico Larroca, Gonzalo Belcredi. 
# ARTES Group
# http://iie.fing.edu.uy/investigacion/grupos/artes/ingles/index.php3
# Instituto de Ingenieria Electrica, Facultad de Ingenieria,
# Universidad de la Republica, Uruguay.
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
import numpy as np
try:
    from mer import probe_qe_cf
except ImportError:
    import os
    import sys
    dirname, filename = os.path.split(os.path.abspath(__file__))
    sys.path.append(os.path.join(dirname, "bindings"))
    from mer import probe_qe_cf

class qa_probe_qe_cf(gr_unittest.TestCase):

    def setUp(self):
        self.tb = gr.top_block()

    def tearDown(self):
        self.tb = None

    def test_instance(self):
        # FIXME: Test will fail until you pass sensible arguments to the constructor
        instance = probe_qe_cf((0.9487+0.9487j,0.9487+0.3162j, 0.3162+0.9487j, 0.3162 +0.3162j,0.9487-0.9487j,0.9487- 0.3162j, 0.3162-0.9487j, 0.3162- 0.3162j,-0.9487+0.9487j,-0.9487+ 0.3162j,- 0.3162+0.9487j,- 0.3162+ 0.3162j,-0.9487-0.9487j,-0.9487- 0.3162j,-0.3162-0.9487j,-0.3162- 0.3162j),0.005)

    def test_001_t(self):
        #The quadrature imabalnce is obtained by:  x.real + +x.imag * sin(phi_hor*3.1416/180)+ j (x.imag +x.real * sin(phi_vert*3.1416/180))
        # Each vector has all constellation values
        number_of_vectors = 1000
        dim_constellation = 16
        #distorsions in degrees
        phi_vert = 1 
        phi_hor =3
        # call the probe_qe constructor with the symbol table and alpha value for averaging
        self.mer_probe_qe_cf_0 = probe_qe_cf((0.9487+0.9487j,0.9487+0.3162j, 0.3162+0.9487j, 0.3162 +0.3162j,0.9487-0.9487j,0.9487- 0.3162j, 0.3162-0.9487j, 0.3162- 0.3162j,-0.9487+0.9487j,-0.9487+ 0.3162j,- 0.3162+0.9487j,- 0.3162+ 0.3162j,-0.9487-0.9487j,-0.9487- 0.3162j,-0.3162-0.9487j,-0.3162- 0.3162j),0.005)
        #source data to test is a vector of the cosntellation table * number_of_vectors
        src_const = (0.9487+0.9487j,0.9487+0.3162j, 0.3162+0.9487j, 0.3162 +0.3162j,0.9487-0.9487j,0.9487- 0.3162j, 0.3162-0.9487j, 0.3162- 0.3162j,-0.9487+0.9487j,-0.9487+ 0.3162j,- 0.3162+0.9487j,- 0.3162+ 0.3162j,-0.9487-0.9487j,-0.9487- 0.3162j,-0.3162-0.9487j,-0.3162- 0.3162j)*number_of_vectors
        #Add distosion to the source data 
        src_data = [x.real + +x.imag * np.sin(phi_hor*3.1416/180)+(x.imag +x.real * np.sin(phi_vert*3.1416/180))*(1j) for x in src_const]
        #create a vector source with the source data and two vector sink blocks to receive the horizontal and vertical QE values
        self.src = blocks.vector_source_c(src_data,False)
        self.dst0 = blocks.vector_sink_f()
        self.dst1 = blocks.vector_sink_f()
        #Connect the blocks
        self.tb.connect((self.src, 0), (self.mer_probe_qe_cf_0, 0))    
        self.tb.connect((self.mer_probe_qe_cf_0, 0),(self.dst0, 0))    
        self.tb.connect((self.mer_probe_qe_cf_0, 1),(self.dst1, 0))    
        self.tb.run ()   
        #The QE error result is the average of the last values of received in the destination vector	
        result_data1 = np.mean(self.dst0.data()[number_of_vectors*dim_constellation-dim_constellation:number_of_vectors*dim_constellation])
        result_data2 = np.mean(self.dst1.data()[number_of_vectors*dim_constellation-dim_constellation:number_of_vectors*dim_constellation])
        print("result horizontal angle = ", result_data1)
        print("result vertical angle = ",result_data2)

        expected_result1 = phi_vert
        expected_result2 = phi_hor
        print("expected result horizontal angle = ",expected_result1)
        print("expected result vertical angle = ",expected_result2)
        # test the error is less than 1%
        self.assertLessEqual(abs((result_data1-expected_result1)/expected_result1), 0.01 )
        self.assertLessEqual(abs((result_data2-expected_result2)/expected_result2), 0.01 )


if __name__ == '__main__':
    gr_unittest.run(qa_probe_qe_cf)
