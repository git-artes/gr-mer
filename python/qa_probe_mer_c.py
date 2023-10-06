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
    from mer import probe_mer_c
except ImportError:
    import os
    import sys
    dirname, filename = os.path.split(os.path.abspath(__file__))
    sys.path.append(os.path.join(dirname, "bindings"))
    from mer import probe_mer_c

class qa_probe_mer_c(gr_unittest.TestCase):

    def setUp(self):
        self.tb = gr.top_block()

    def tearDown(self):
        self.tb = None

    def test_instance(self):
        # FIXME: Test will fail until you pass sensible arguments to the constructor
        instance = probe_mer_c((0.9487+0.9487j,0.9487+0.3162j, 0.3162+0.9487j, 0.3162 +0.3162j,0.9487-0.9487j,0.9487- 0.3162j, 0.3162-0.9487j, 0.3162- 0.3162j,-0.9487+0.9487j,-0.9487+ 0.3162j,- 0.3162+0.9487j,- 0.3162+ 0.3162j,-0.9487-0.9487j,-0.9487- 0.3162j,-0.3162-0.9487j,-0.3162- 0.3162j),0.005)

    def test_001_t(self):
      	# to test a constant complex distorsion added to the symbols
        # Each vector has all constellation values
        number_of_vectors = 10
        dim_constellation = 16
        # real and imaginary part of the distorsion added to the symbols
        distorsion_real = 0.1
        distorsion_imag =0.15
        # call the probe_mer constructor with the symbol table and alpha value for averaging
        self.mer_probe_mer_c_0 = probe_mer_c((0.9487+0.9487j,0.9487+0.3162j, 0.3162+0.9487j, 0.3162 +0.3162j,0.9487-0.9487j,0.9487- 0.3162j, 0.3162-0.9487j, 0.3162- 0.3162j,-0.9487+0.9487j,-0.9487+ 0.3162j,- 0.3162+0.9487j,- 0.3162+ 0.3162j,-0.9487-0.9487j,-0.9487- 0.3162j,-0.3162-0.9487j,-0.3162- 0.3162j),0.005)
        #source data to test is a vector of the cosntellation table * number_of_vectors
        src_data = (0.9487+0.9487j,0.9487+0.3162j, 0.3162+0.9487j, 0.3162 +0.3162j,0.9487-0.9487j,0.9487- 0.3162j, 0.3162-0.9487j, 0.3162- 0.3162j,-0.9487+0.9487j,-0.9487+ 0.3162j,- 0.3162+0.9487j,- 0.3162+ 0.3162j,-0.9487-0.9487j,-0.9487- 0.3162j,-0.3162-0.9487j,-0.3162- 0.3162j)*number_of_vectors
        # Add the aditive distorsion to the source data
        src_data = [x+distorsion_real+distorsion_imag*(1j) for x in src_data]
        # create a vector source with the source data and a vector sink to receive the MER values
        self.src = blocks.vector_source_c(src_data,False)
        self.dst = blocks.vector_sink_f()
        #Connect the blocks 
        self.tb.connect((self.src, 0), (self.mer_probe_mer_c_0, 0))    
        self.tb.connect((self.mer_probe_mer_c_0, 0),(self.dst, 0))    
        self.tb.run ()   
        # The MER is the average of the last values of MER received
        result_data = np.mean(self.dst.data()[number_of_vectors*dim_constellation-dim_constellation:number_of_vectors*dim_constellation])
        print("result = ", result_data)
        #Calculates the theorical MER for this constellation and this distorsion, the constellation has avg tx power equal 1
        error = distorsion_real*distorsion_real+distorsion_imag*distorsion_imag
        expected_result = 10*np.log10(1.0/error)
        print("expected result = ", expected_result)
        # Thest that the estimation error is less than 0.1%
        self.assertLessEqual(abs((result_data-expected_result)/expected_result), 0.001 )


    def test_002_t (self):
        #to test a  multiplicative distosion to the symbols
        # Each vector has all constellation values
        number_of_vectors = 10
        dim_constellation = 16
        # real and imaginary part of the distorsion that will multiply each symbols
        distorsion_real = 1.1
        distorsion_imag = 1.15
        # call the probe_mer constructor with the symbol table and alpha value for averaging
        self.mer_probe_mer_c_0 = probe_mer_c((0.9487+0.9487j,0.9487+0.3162j, 0.3162+0.9487j, 0.3162 +0.3162j,0.9487-0.9487j,0.9487- 0.3162j, 0.3162-0.9487j, 0.3162- 0.3162j,-0.9487+0.9487j,-0.9487+ 0.3162j,- 0.3162+0.9487j,- 0.3162+ 0.3162j,-0.9487-0.9487j,-0.9487- 0.3162j,-0.3162-0.9487j,-0.3162- 0.3162j),0.005)
        #source data to test is a vector of the cosntellation table * number_of_vectors
        src_const = (0.9487+0.9487j,0.9487+0.3162j, 0.3162+0.9487j, 0.3162 +0.3162j,0.9487-0.9487j,0.9487- 0.3162j, 0.3162-0.9487j, 0.3162- 0.3162j,-0.9487+0.9487j,-0.9487+ 0.3162j,- 0.3162+0.9487j,- 0.3162+ 0.3162j,-0.9487-0.9487j,-0.9487- 0.3162j,-0.3162-0.9487j,-0.3162- 0.3162j)*number_of_vectors
        # Multiply by the distorsion the source data
        src_data = [x.real*distorsion_real+x.imag * distorsion_imag*(1j) for x in src_const]
        # create a vector source with the source data and a vector sink to receive the MER values
        self.src = blocks.vector_source_c(src_data,False)
        self.dst = blocks.vector_sink_f()
        #Connect the blocks 
        self.tb.connect((self.src, 0), (self.mer_probe_mer_c_0, 0))    
        self.tb.connect((self.mer_probe_mer_c_0, 0),(self.dst, 0))    
        self.tb.run ()  
        # The MER is the average of the last values of MER received
        result_data = np.mean(self.dst.data()[number_of_vectors*dim_constellation-dim_constellation:number_of_vectors*dim_constellation])
        print("result = ", result_data)
        #Calculates the theorical MER for this constellation and this distorsion, the constellation has avg tx power equal 1
        error2_real = np.sum((np.real(src_const)*np.real(src_const)))/dim_constellation/number_of_vectors * (distorsion_real-1)*(distorsion_real-1)    
        error2_imag = np.sum((np.imag(src_const)*np.imag(src_const)))/dim_constellation/number_of_vectors * (distorsion_imag-1)*(distorsion_imag-1)
        expected_result = 10*np.log10(1.0/(error2_real+error2_imag))
        print("expected result = ", expected_result)
        # Thest that the estimation error is less than 0.1%
        self.assertLessEqual(abs((result_data-expected_result)/expected_result), 0.001 )

    def test_003_t(self):
        # test MER for 256QAM
        src_const = [(1.1504475+1.1504475j),(1.1504475+0.9970545j),(0.9970545+1.1504475j),(0.9970545+0.9970545j),(1.1504475+0.6902685j),(1.1504475+0.8436615j),(0.9970545+0.6902685j),(0.9970545+0.8436615j),(0.6902685+1.1504475j),(0.6902685+0.9970545j),(0.8436615+1.1504475j),(0.8436615+0.9970545j),(0.6902685+0.6902685j),(0.6902685+0.8436615j),(0.8436615+0.6902685j),(0.8436615+0.8436615j),(1.1504475+0.0766965j),(1.1504475+0.2300895j),(0.9970545+0.0766965j),(0.9970545+0.2300895j),(1.1504475+0.5368755j),(1.1504475+0.38348252j),(0.9970545+0.5368755j),(0.9970545+0.38348252j),(0.6902685+0.0766965j),(0.6902685+0.2300895j),(0.8436615+0.0766965j),(0.8436615+0.2300895j),(0.6902685+0.5368755j),(0.6902685+0.38348252j),(0.8436615+0.5368755j),(0.8436615+0.38348252j),(0.0766965+1.1504475j),(0.0766965+0.9970545j),(0.2300895+1.1504475j),(0.2300895+0.9970545j),(0.0766965+0.6902685j),(0.0766965+0.8436615j),(0.2300895+0.6902685j),(0.2300895+0.8436615j),(0.5368755+1.1504475j),(0.5368755+0.9970545j),(0.38348252+1.1504475j),(0.38348252+0.9970545j),(0.5368755+0.6902685j),(0.5368755+0.8436615j),(0.38348252+0.6902685j),(0.38348252+0.8436615j),(0.0766965+0.0766965j),(0.0766965+0.2300895j),(0.2300895+0.0766965j),(0.2300895+0.2300895j),(0.0766965+0.5368755j),(0.0766965+0.38348252j),(0.2300895+0.5368755j),(0.2300895+0.38348252j),(0.5368755+0.0766965j),(0.5368755+0.2300895j),(0.38348252+0.0766965j),(0.38348252+0.2300895j),(0.5368755+0.5368755j),(0.5368755+0.38348252j),(0.38348252+0.5368755j),(0.38348252+0.38348252j),(1.1504475-1.1504475j),(1.1504475-0.9970545j),(0.9970545-1.1504475j),(0.9970545-0.9970545j),(1.1504475-0.6902685j),(1.1504475-0.8436615j),(0.9970545-0.6902685j),(0.9970545-0.8436615j),(0.6902685-1.1504475j),(0.6902685-0.9970545j),(0.8436615-1.1504475j),(0.8436615-0.9970545j),(0.6902685-0.6902685j),(0.6902685-0.8436615j),(0.8436615-0.6902685j),(0.8436615-0.8436615j),(1.1504475-0.0766965j),(1.1504475-0.2300895j),(0.9970545-0.0766965j),(0.9970545-0.2300895j),(1.1504475-0.5368755j),(1.1504475-0.38348252j),(0.9970545-0.5368755j),(0.9970545-0.38348252j),(0.6902685-0.0766965j),(0.6902685-0.2300895j),(0.8436615-0.0766965j),(0.8436615-0.2300895j),(0.6902685-0.5368755j),(0.6902685-0.38348252j),(0.8436615-0.5368755j),(0.8436615-0.38348252j),(0.0766965-1.1504475j),(0.0766965-0.9970545j),(0.2300895-1.1504475j),(0.2300895-0.9970545j),(0.0766965-0.6902685j),(0.0766965-0.8436615j),(0.2300895-0.6902685j),(0.2300895-0.8436615j),(0.5368755-1.1504475j),(0.5368755-0.9970545j),(0.38348252-1.1504475j),(0.38348252-0.9970545j),(0.5368755-0.6902685j),(0.5368755-0.8436615j),(0.38348252-0.6902685j),(0.38348252-0.8436615j),(0.0766965-0.0766965j),(0.0766965-0.2300895j),(0.2300895-0.0766965j),(0.2300895-0.2300895j),(0.0766965-0.5368755j),(0.0766965-0.38348252j),(0.2300895-0.5368755j),(0.2300895-0.38348252j),(0.5368755-0.0766965j),(0.5368755-0.2300895j),(0.38348252-0.0766965j),(0.38348252-0.2300895j),(0.5368755-0.5368755j),(0.5368755-0.38348252j),(0.38348252-0.5368755j),(0.38348252-0.38348252j),(-1.1504475+1.1504475j),(-1.1504475+0.9970545j),(-0.9970545+1.1504475j),(-0.9970545+0.9970545j),(-1.1504475+0.6902685j),(-1.1504475+0.8436615j),(-0.9970545+0.6902685j),(-0.9970545+0.8436615j),(-0.6902685+1.1504475j),(-0.6902685+0.9970545j),(-0.8436615+1.1504475j),(-0.8436615+0.9970545j),(-0.6902685+0.6902685j),(-0.6902685+0.8436615j),(-0.8436615+0.6902685j),(-0.8436615+0.8436615j),(-1.1504475+0.0766965j),(-1.1504475+0.2300895j),(-0.9970545+0.0766965j),(-0.9970545+0.2300895j),(-1.1504475+0.5368755j),(-1.1504475+0.38348252j),(-0.9970545+0.5368755j),(-0.9970545+0.38348252j),(-0.6902685+0.0766965j),(-0.6902685+0.2300895j),(-0.8436615+0.0766965j),(-0.8436615+0.2300895j),(-0.6902685+0.5368755j),(-0.6902685+0.38348252j),(-0.8436615+0.5368755j),(-0.8436615+0.38348252j),(-0.0766965+1.1504475j),(-0.0766965+0.9970545j),(-0.2300895+1.1504475j),(-0.2300895+0.9970545j),(-0.0766965+0.6902685j),(-0.0766965+0.8436615j),(-0.2300895+0.6902685j),(-0.2300895+0.8436615j),(-0.5368755+1.1504475j),(-0.5368755+0.9970545j),(-0.38348252+1.1504475j),(-0.38348252+0.9970545j),(-0.5368755+0.6902685j),(-0.5368755+0.8436615j),(-0.38348252+0.6902685j),(-0.38348252+0.8436615j),(-0.0766965+0.0766965j),(-0.0766965+0.2300895j),(-0.2300895+0.0766965j),(-0.2300895+0.2300895j),(-0.0766965+0.5368755j),(-0.0766965+0.38348252j),(-0.2300895+0.5368755j),(-0.2300895+0.38348252j),(-0.5368755+0.0766965j),(-0.5368755+0.2300895j),(-0.38348252+0.0766965j),(-0.38348252+0.2300895j),(-0.5368755+0.5368755j),(-0.5368755+0.38348252j),(-0.38348252+0.5368755j),(-0.38348252+0.38348252j),(-1.1504475-1.1504475j),(-1.1504475-0.9970545j),(-0.9970545-1.1504475j),(-0.9970545-0.9970545j),(-1.1504475-0.6902685j),(-1.1504475-0.8436615j),(-0.9970545-0.6902685j),(-0.9970545-0.8436615j),(-0.6902685-1.1504475j),(-0.6902685-0.9970545j),(-0.8436615-1.1504475j),(-0.8436615-0.9970545j),(-0.6902685-0.6902685j),(-0.6902685-0.8436615j),(-0.8436615-0.6902685j),(-0.8436615-0.8436615j),(-1.1504475-0.0766965j),(-1.1504475-0.2300895j),(-0.9970545-0.0766965j),(-0.9970545-0.2300895j),(-1.1504475-0.5368755j),(-1.1504475-0.38348252j),(-0.9970545-0.5368755j),(-0.9970545-0.38348252j),(-0.6902685-0.0766965j),(-0.6902685-0.2300895j),(-0.8436615-0.0766965j),(-0.8436615-0.2300895j),(-0.6902685-0.5368755j),(-0.6902685-0.38348252j),(-0.8436615-0.5368755j),(-0.8436615-0.38348252j),(-0.0766965-1.1504475j),(-0.0766965-0.9970545j),(-0.2300895-1.1504475j),(-0.2300895-0.9970545j),(-0.0766965-0.6902685j),(-0.0766965-0.8436615j),(-0.2300895-0.6902685j),(-0.2300895-0.8436615j),(-0.5368755-1.1504475j),(-0.5368755-0.9970545j),(-0.38348252-1.1504475j),(-0.38348252-0.9970545j),(-0.5368755-0.6902685j),(-0.5368755-0.8436615j),(-0.38348252-0.6902685j),(-0.38348252-0.8436615j),(-0.0766965-0.0766965j),(-0.0766965-0.2300895j),(-0.2300895-0.0766965j),(-0.2300895-0.2300895j),(-0.0766965-0.5368755j),(-0.0766965-0.38348252j),(-0.2300895-0.5368755j),(-0.2300895-0.38348252j),(-0.5368755-0.0766965j),(-0.5368755-0.2300895j),(-0.38348252-0.0766965j),(-0.38348252-0.2300895j),(-0.5368755-0.5368755j),(-0.5368755-0.38348252j),(-0.38348252-0.5368755j),(-0.38348252-0.38348252j)]
        # to test a  multiplicative distosion to the symbols
        # Each vector has all constellation values
        number_of_vectors = 1
        dim_constellation = 256
        # real and imaginary part of the distorsion that will multiply each symbols
        distorsion_real = 1.0023
        distorsion_imag = 1.0015
        src_data = src_const*number_of_vectors
        # call the probe_mer constructor with the symbol table and alpha value for averaging
        self.mer_probe_mer_c_0 = probe_mer_c(src_const,0.005)
        # Multiply by the distorsion the source data
        src_data = [x.real*distorsion_real+x.imag * distorsion_imag*(1j) for x in src_data]
        # create a vector source with the source data and a vector sink to receive the MER values
        self.src = blocks.vector_source_c(src_data,False)
        self.dst = blocks.vector_sink_f()
        #Connect the blocks 
        self.tb.connect((self.src, 0), (self.mer_probe_mer_c_0, 0))    
        self.tb.connect((self.mer_probe_mer_c_0, 0),(self.dst, 0))    
        self.tb.run ()  
        # The MER is the average of the last values of MER received
        result_data = np.mean(self.dst.data()[number_of_vectors*dim_constellation-dim_constellation:number_of_vectors*dim_constellation])
        print("result = ", result_data)
        #Calculates the theorical MER for this constellation and this distorsion, the constellation has avg tx power equal 1
        error2_real = np.sum((np.real(src_const)*np.real(src_const)))/dim_constellation/number_of_vectors * (distorsion_real-1)*(distorsion_real-1)    
        error2_imag = np.sum((np.imag(src_const)*np.imag(src_const)))/dim_constellation/number_of_vectors * (distorsion_imag-1)*(distorsion_imag-1)
        expected_result = 10*np.log10(1.0/(error2_real+error2_imag))
        print("expected result = ", expected_result)
        # Thest that the estimation error is less than 0.1%
        self.assertLessEqual(abs((result_data-expected_result)/expected_result), 0.001 )


if __name__ == '__main__':
    gr_unittest.run(qa_probe_mer_c)
