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

# PHASE JITTER TEST
# We compare the PJ theoretical value of the model with the probe_mer estimation of this value.



from gnuradio import analog
from gnuradio import filter
from gnuradio.filter import firdes
from gnuradio import channels
from gnuradio import gr, gr_unittest
from gnuradio import blocks
import mer as mer
import numpy as np
import math
class qa_probe_pj_cf (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
	# to test we add gaussian phase jitter and additive gaussian noise to the source vector 
	# Each vector has all constellation values
	number_of_vectors = 50000
	dim_constellation = 16
	#Our phase jitter probe estimator, estimates the jitter variance and the snr. 
	#gaussian noise added in "volts", the channel add noise  with variance noise*noise to each axe I and Q 
	noise = 0.02
	# the variance of the phase jitter is math.pow(10.0,phase_noise_mag/20.0) * math.pow(10.0,phase_noise_mag/20.0)
	# the estimator works fine with an error of around 5-10% with additive noise with standard deviation of 0.01 to 0.03 and phase_noise_mag between -20 (standard deviation = 0.1 radians, approx 6 degrees) and -40 (phase_noise_mag = -40, standard deviation = 0.01 radians approx 0.6 degrees). These values are assuming that pj and snr are filtered. We are averaging the results but we are not filtering the phase jitter noise. If the additive noise is very low the snr estimator has errors and if the additive noise is very high or the phase jitter noise is very high there are many decision errors.
	phase_noise_mag = -30
	#In hardware impairments thre is a single pole iir filter to filter the gaussian noise, we are not filtering the noise using alpha  equal one	
	alpha = 1
	# creates the probe_pj object withe the symbol table and alpha
 	self.mer_probe_pj_cf_0 = mer.probe_pj_cf((0.9487+0.9487j,0.9487+0.3162j, 0.3162+0.9487j, 0.3162 +0.3162j,0.9487-0.9487j,0.9487- 0.3162j, 0.3162-0.9487j, 0.3162- 0.3162j,-0.9487+0.9487j,-0.9487+ 0.3162j,- 0.3162+0.9487j,- 0.3162+ 0.3162j,-0.9487-0.9487j,-0.9487- 0.3162j,-0.3162-0.9487j,-0.3162- 0.3162j),0.005)
        #creates a source with all possible symbols repited number_of_vectors 
        src_const = (0.9487+0.9487j,0.9487+0.3162j, 0.3162+0.9487j, 0.3162 +0.3162j,0.9487-0.9487j,0.9487- 0.3162j, 0.3162-0.9487j, 0.3162- 0.3162j,-0.9487+0.9487j,-0.9487+ 0.3162j,- 0.3162+0.9487j,- 0.3162+ 0.3162j,-0.9487-0.9487j,-0.9487- 0.3162j,-0.3162-0.9487j,-0.3162- 0.3162j)*number_of_vectors
	
	#creates the blocks and sinks to receive the estimations
        self.src = blocks.vector_source_c(src_const,False)
	self.dst0 = blocks.vector_sink_f()
	self.dst1 = blocks.vector_sink_f()
	# add a channel model to add additive gaussian noise
	self.channels_channel_model_0 = channels.channel_model(
        	noise_voltage=noise,
        	frequency_offset=0.0,
        	epsilon=1.0,
        	taps=(1, ),
        	noise_seed=0,
        	block_tags=False
        )
	# A gaussian noise w is generated and filtered w1,a complex signal a= cos(w1) + j sin(w1) is generated
	# Source data src is added with white noise src1,  the output signal with phase jitter and additive noise is  a * src1
	# the output signal a*src1 is send to the phase jitter probe and the pj and snr are estimated
	# to filter the gaussian noise added to the phase, we are using alpha equal 1 so we are not filtering 
        self.filter_single_pole_iir_filter_xx_0 = filter.single_pole_iir_filter_ff(alpha, 1)
        self.blocks_transcendental_0_0 = blocks.transcendental("sin", "float")
        self.blocks_transcendental_0 = blocks.transcendental("cos", "float")
	self.blocks_multiply_xx_0 = blocks.multiply_vcc(1)
        self.blocks_float_to_complex_0 = blocks.float_to_complex(1)
        self.analog_noise_source_x_0 = analog.noise_source_f(analog.GR_GAUSSIAN, math.pow(10.0,phase_noise_mag/20.0), 42)

        ##################################################
        # Connections
        ##################################################
	
        self.tb.connect((self.blocks_float_to_complex_0, 0), (self.blocks_multiply_xx_0, 1))
        self.tb.connect((self.analog_noise_source_x_0, 0), (self.filter_single_pole_iir_filter_xx_0, 0))
        self.tb.connect((self.blocks_multiply_xx_0, 0), (self.mer_probe_pj_cf_0, 0))
        self.tb.connect((self.src, 0), (self.channels_channel_model_0, 0))
	self.tb.connect((self.channels_channel_model_0, 0), (self.blocks_multiply_xx_0, 0))
        self.tb.connect((self.filter_single_pole_iir_filter_xx_0, 0), (self.blocks_transcendental_0, 0))
        self.tb.connect((self.filter_single_pole_iir_filter_xx_0, 0), (self.blocks_transcendental_0_0, 0))
        self.tb.connect((self.blocks_transcendental_0, 0), (self.blocks_float_to_complex_0, 0))
        self.tb.connect((self.blocks_transcendental_0_0, 0), (self.blocks_float_to_complex_0, 1))
	self.tb.connect((self.mer_probe_pj_cf_0, 0),(self.dst0, 0))
	self.tb.connect((self.mer_probe_pj_cf_0, 1),(self.dst1, 0))
	self.tb.run ()   
	result_data1 = np.mean(self.dst0.data()[number_of_vectors*dim_constellation-dim_constellation*10000:number_of_vectors*dim_constellation])
	result_data2 = np.mean(self.dst1.data()[number_of_vectors*dim_constellation-dim_constellation*10000:number_of_vectors*dim_constellation])
	print " result phase jitter variance = ",result_data1
	print " result snr =  ",result_data2
	expected_result1 = math.pow(10.0,phase_noise_mag/20.0) * math.pow(10.0,phase_noise_mag/20.0)
	print " expected result phase jitter variance = ", expected_result1
	expected_result2 = 10*np.log10(1.0/noise/noise/2)
	print " expected result snr =  ",expected_result2
	#test an error in the phase jitter variance less than 10 %, 
	self.assertLessEqual(abs((result_data1-expected_result1)/expected_result1), 0.1 )
	#test an error in the snr less than 10 %, 
	self.assertLessEqual(abs((result_data2-expected_result2)/expected_result2), 0.1 )

    


if __name__ == '__main__':
    gr_unittest.run(qa_probe_pj_cf, "qa_probe_pj_cf.xml")
