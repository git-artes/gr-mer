#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 
# Copyright 2015
# Pablo Belzarena <belza@fing.edu.uy>, Gabriel Gomez,  Victor Gonzalez-Barbone, Pablo Flores Guridi, Federico Larroca. 
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

# MODULATION ERROR RATE TEST
# Lets I[i],Q[i] the sample i received and I_{true}[i] and Q_{true}[i] the corresponding constellation point
# MER is defined as: lets  txsignal_power[i] = I^2_{true][i] + Q^2_{true}[i] and error_power[i]= (I_{true][i]-I[i])^2 + (Q_{true}[i]- Q[i])^2
# and lets d_avgtxsignal_power = average{txsignal_power[i]} and d_avgerror_power = average{error_power[i]}
# MER = 10*log10(d_avgtxsignal_power/ d_avgerror_power) in dbs
# This test analyze two different types of distorsions: Carrier Suppression Error (global traslation of the constellation) and Amplitud Imbalance Error ( expansion or contraction of the constellation).
# We compare the MER theoretical value for each distorsion with the probe_mer estimation of this value.



from gnuradio import gr, gr_unittest
from gnuradio import blocks
import mer as mer
import numpy as np

class qa_probe_mer_c (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
      	# to test a constant complex distorsion added to the symbols
	# Each vector has all constellation values
	number_of_vectors = 10
	dim_constellation = 16
	# real and imaginary part of the distorsion added to the symbols
	distorsion_real = 0.1
	distorsion_imag =0.15
	# call the probe_mer constructor with the symbol table and alpha value for averaging
 	self.mer_probe_mer_c_0 = mer.probe_mer_c((0.9487+0.9487j,0.9487+0.3162j, 0.3162+0.9487j, 0.3162 +0.3162j,0.9487-0.9487j,0.9487- 0.3162j, 0.3162-0.9487j, 0.3162- 0.3162j,-0.9487+0.9487j,-0.9487+ 0.3162j,- 0.3162+0.9487j,- 0.3162+ 0.3162j,-0.9487-0.9487j,-0.9487- 0.3162j,-0.3162-0.9487j,-0.3162- 0.3162j),0.005)
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
	print "result = ", result_data
	#Calculates the theorical MER for this constellation and this distorsion, the constellation has avg tx power equal 1
	error = distorsion_real*distorsion_real+distorsion_imag*distorsion_imag
	expected_result = 10*np.log10(1.0/error)
	print "expected result = ", expected_result
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
 	self.mer_probe_mer_c_0 = mer.probe_mer_c((0.9487+0.9487j,0.9487+0.3162j, 0.3162+0.9487j, 0.3162 +0.3162j,0.9487-0.9487j,0.9487- 0.3162j, 0.3162-0.9487j, 0.3162- 0.3162j,-0.9487+0.9487j,-0.9487+ 0.3162j,- 0.3162+0.9487j,- 0.3162+ 0.3162j,-0.9487-0.9487j,-0.9487- 0.3162j,-0.3162-0.9487j,-0.3162- 0.3162j),0.005)
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
	print "result = ", result_data
	#Calculates the theorical MER for this constellation and this distorsion, the constellation has avg tx power equal 1
	error2_real = np.sum((np.real(src_const)*np.real(src_const)))/dim_constellation/number_of_vectors * (distorsion_real-1)*(distorsion_real-1)    
	error2_imag = np.sum((np.imag(src_const)*np.imag(src_const)))/dim_constellation/number_of_vectors * (distorsion_imag-1)*(distorsion_imag-1)
	expected_result = 10*np.log10(1.0/(error2_real+error2_imag))
	print "expected result = ", expected_result
	# Thest that the estimation error is less than 0.1%
	self.assertLessEqual(abs((result_data-expected_result)/expected_result), 0.001 )



if __name__ == '__main__':
    gr_unittest.run(qa_probe_mer_c, "qa_probe_mer_c.xml")
