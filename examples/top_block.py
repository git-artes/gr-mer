#!/usr/bin/env python
##################################################
# Gnuradio Python Flow Graph
# Title: Top Block
# Generated: Mon May 11 16:53:30 2015
##################################################

from gnuradio import blocks
from gnuradio import channels
from gnuradio import digital
from gnuradio import eng_notation
from gnuradio import gr
from gnuradio import wxgui
from gnuradio.eng_option import eng_option
from gnuradio.fft import window
from gnuradio.filter import firdes
from gnuradio.wxgui import fftsink2
from gnuradio.wxgui import forms
from gnuradio.wxgui import numbersink2
from gnuradio.wxgui import scopesink2
from grc_gnuradio import wxgui as grc_wxgui
from optparse import OptionParser
import mer
import numpy
import wx

class top_block(grc_wxgui.top_block_gui):

    def __init__(self):
        grc_wxgui.top_block_gui.__init__(self, title="Top Block")
        _icon_path = "/usr/share/icons/hicolor/32x32/apps/gnuradio-grc.png"
        self.SetIcon(wx.Icon(_icon_path, wx.BITMAP_TYPE_ANY))

        ##################################################
        # Variables
        ##################################################
        self.sym_rate = sym_rate = 32e3 
        self.samp_rate = samp_rate = 32000
        self.qe = qe = 0
        self.pj = pj = -40
        self.noise = noise = 0.01
        self.cs = cs = 0
        self.ai = ai = 0

        ##################################################
        # Blocks
        ##################################################
        _qe_sizer = wx.BoxSizer(wx.VERTICAL)
        self._qe_text_box = forms.text_box(
        	parent=self.GetWin(),
        	sizer=_qe_sizer,
        	value=self.qe,
        	callback=self.set_qe,
        	label='qe',
        	converter=forms.float_converter(),
        	proportion=0,
        )
        self._qe_slider = forms.slider(
        	parent=self.GetWin(),
        	sizer=_qe_sizer,
        	value=self.qe,
        	callback=self.set_qe,
        	minimum=0,
        	maximum=5,
        	num_steps=100,
        	style=wx.SL_HORIZONTAL,
        	cast=float,
        	proportion=1,
        )
        self.GridAdd(_qe_sizer, 1, 3, 1, 1)
        _pj_sizer = wx.BoxSizer(wx.VERTICAL)
        self._pj_text_box = forms.text_box(
        	parent=self.GetWin(),
        	sizer=_pj_sizer,
        	value=self.pj,
        	callback=self.set_pj,
        	label='pj',
        	converter=forms.float_converter(),
        	proportion=0,
        )
        self._pj_slider = forms.slider(
        	parent=self.GetWin(),
        	sizer=_pj_sizer,
        	value=self.pj,
        	callback=self.set_pj,
        	minimum=-40,
        	maximum=0,
        	num_steps=100,
        	style=wx.SL_HORIZONTAL,
        	cast=float,
        	proportion=1,
        )
        self.GridAdd(_pj_sizer, 1, 0, 1, 1)
        _noise_sizer = wx.BoxSizer(wx.VERTICAL)
        self._noise_text_box = forms.text_box(
        	parent=self.GetWin(),
        	sizer=_noise_sizer,
        	value=self.noise,
        	callback=self.set_noise,
        	label='noise',
        	converter=forms.float_converter(),
        	proportion=0,
        )
        self._noise_slider = forms.slider(
        	parent=self.GetWin(),
        	sizer=_noise_sizer,
        	value=self.noise,
        	callback=self.set_noise,
        	minimum=0,
        	maximum=0.1,
        	num_steps=100,
        	style=wx.SL_HORIZONTAL,
        	cast=float,
        	proportion=1,
        )
        self.GridAdd(_noise_sizer, 1, 4, 1, 1)
        self.n_0 = self.n_0 = wx.Notebook(self.GetWin(), style=wx.NB_TOP)
        self.n_0.AddPage(grc_wxgui.Panel(self.n_0), "Constellation")
        self.n_0.AddPage(grc_wxgui.Panel(self.n_0), "Meassures")
        self.n_0.AddPage(grc_wxgui.Panel(self.n_0), "FFT")
        self.Add(self.n_0)
        _cs_sizer = wx.BoxSizer(wx.VERTICAL)
        self._cs_text_box = forms.text_box(
        	parent=self.GetWin(),
        	sizer=_cs_sizer,
        	value=self.cs,
        	callback=self.set_cs,
        	label='cs',
        	converter=forms.float_converter(),
        	proportion=0,
        )
        self._cs_slider = forms.slider(
        	parent=self.GetWin(),
        	sizer=_cs_sizer,
        	value=self.cs,
        	callback=self.set_cs,
        	minimum=0,
        	maximum=0.5,
        	num_steps=100,
        	style=wx.SL_HORIZONTAL,
        	cast=float,
        	proportion=1,
        )
        self.GridAdd(_cs_sizer, 1, 1, 1, 1)
        _ai_sizer = wx.BoxSizer(wx.VERTICAL)
        self._ai_text_box = forms.text_box(
        	parent=self.GetWin(),
        	sizer=_ai_sizer,
        	value=self.ai,
        	callback=self.set_ai,
        	label='ai',
        	converter=forms.float_converter(),
        	proportion=0,
        )
        self._ai_slider = forms.slider(
        	parent=self.GetWin(),
        	sizer=_ai_sizer,
        	value=self.ai,
        	callback=self.set_ai,
        	minimum=0,
        	maximum=5,
        	num_steps=100,
        	style=wx.SL_HORIZONTAL,
        	cast=float,
        	proportion=1,
        )
        self.GridAdd(_ai_sizer, 1, 2, 1, 1)
        self.wxgui_scopesink2_0_0 = scopesink2.scope_sink_c(
        	self.n_0.GetPage(0).GetWin(),
        	title="Constellation",
        	sample_rate=sym_rate,
        	v_scale=0.5,
        	v_offset=0,
        	t_scale=0,
        	ac_couple=False,
        	xy_mode=True,
        	num_inputs=1,
        	trig_mode=wxgui.TRIG_MODE_AUTO,
        	y_axis_label="Counts",
        )
        self.n_0.GetPage(0).GridAdd(self.wxgui_scopesink2_0_0.win, 0, 0, 1, 1)
        self.wxgui_numbersink2_1_1_1 = numbersink2.number_sink_f(
        	self.n_0.GetPage(1).GetWin(),
        	unit="",
        	minval=0,
        	maxval=1,
        	factor=1.0,
        	decimal_places=1,
        	ref_level=0,
        	sample_rate=samp_rate,
        	number_rate=15,
        	average=False,
        	avg_alpha=0.03,
        	label="Amplitude Imbalance horizontal",
        	peak_hold=False,
        	show_gauge=True,
        )
        self.n_0.GetPage(1).GridAdd(self.wxgui_numbersink2_1_1_1.win, 1, 1, 1, 1)
        self.wxgui_numbersink2_1_1_0_1_0_0 = numbersink2.number_sink_f(
        	self.n_0.GetPage(1).GetWin(),
        	unit="",
        	minval=0,
        	maxval=100,
        	factor=1.0,
        	decimal_places=1,
        	ref_level=0,
        	sample_rate=samp_rate,
        	number_rate=15,
        	average=False,
        	avg_alpha=0.03,
        	label="SNR",
        	peak_hold=False,
        	show_gauge=True,
        )
        self.n_0.GetPage(1).GridAdd(self.wxgui_numbersink2_1_1_0_1_0_0.win, 3, 1, 1, 1)
        self.wxgui_numbersink2_1_1_0_1_0 = numbersink2.number_sink_f(
        	self.n_0.GetPage(1).GetWin(),
        	unit="",
        	minval=0,
        	maxval=0.1,
        	factor=1.0,
        	decimal_places=5,
        	ref_level=0,
        	sample_rate=samp_rate,
        	number_rate=15,
        	average=False,
        	avg_alpha=0.03,
        	label="Phase Jitter Variance",
        	peak_hold=False,
        	show_gauge=True,
        )
        self.n_0.GetPage(1).GridAdd(self.wxgui_numbersink2_1_1_0_1_0.win, 3, 0, 1, 1)
        self.wxgui_numbersink2_1_1_0_1 = numbersink2.number_sink_f(
        	self.n_0.GetPage(1).GetWin(),
        	unit="degrees",
        	minval=-10,
        	maxval=10,
        	factor=1.0,
        	decimal_places=1,
        	ref_level=0,
        	sample_rate=samp_rate,
        	number_rate=15,
        	average=False,
        	avg_alpha=0.03,
        	label="Quadrature Horizontal Angle Error ",
        	peak_hold=False,
        	show_gauge=True,
        )
        self.n_0.GetPage(1).GridAdd(self.wxgui_numbersink2_1_1_0_1.win, 2, 0, 1, 1)
        self.wxgui_numbersink2_1_1_0_0 = numbersink2.number_sink_f(
        	self.n_0.GetPage(1).GetWin(),
        	unit="degrees",
        	minval=-10,
        	maxval=10,
        	factor=1.0,
        	decimal_places=1,
        	ref_level=0,
        	sample_rate=samp_rate,
        	number_rate=15,
        	average=False,
        	avg_alpha=0.03,
        	label="Quadrature Vertical Angle Error",
        	peak_hold=False,
        	show_gauge=True,
        )
        self.n_0.GetPage(1).GridAdd(self.wxgui_numbersink2_1_1_0_0.win, 2, 1, 1, 1)
        self.wxgui_numbersink2_1_1_0 = numbersink2.number_sink_f(
        	self.n_0.GetPage(1).GetWin(),
        	unit="volts",
        	minval=0,
        	maxval=1,
        	factor=1.0,
        	decimal_places=1,
        	ref_level=0,
        	sample_rate=samp_rate,
        	number_rate=15,
        	average=False,
        	avg_alpha=0.03,
        	label="Amplitude Imbalance Vertical",
        	peak_hold=False,
        	show_gauge=True,
        )
        self.n_0.GetPage(1).GridAdd(self.wxgui_numbersink2_1_1_0.win, 1, 2, 1, 1)
        self.wxgui_numbersink2_1_1 = numbersink2.number_sink_f(
        	self.n_0.GetPage(1).GetWin(),
        	unit="power normalized to tx power",
        	minval=0,
        	maxval=0.1,
        	factor=1.0,
        	decimal_places=4,
        	ref_level=0,
        	sample_rate=samp_rate,
        	number_rate=15,
        	average=False,
        	avg_alpha=0.03,
        	label="Carrier Suppression ",
        	peak_hold=False,
        	show_gauge=True,
        )
        self.n_0.GetPage(1).GridAdd(self.wxgui_numbersink2_1_1.win, 1, 0, 1, 1)
        self.wxgui_numbersink2_1_0 = numbersink2.number_sink_f(
        	self.n_0.GetPage(1).GetWin(),
        	unit="voltage",
        	minval=0,
        	maxval=1,
        	factor=1.0,
        	decimal_places=3,
        	ref_level=0,
        	sample_rate=samp_rate,
        	number_rate=15,
        	average=True,
        	avg_alpha=0.03,
        	label="STE",
        	peak_hold=True,
        	show_gauge=True,
        )
        self.n_0.GetPage(1).GridAdd(self.wxgui_numbersink2_1_0.win, 0, 1, 1, 1)
        self.wxgui_numbersink2_1 = numbersink2.number_sink_f(
        	self.n_0.GetPage(1).GetWin(),
        	unit="db",
        	minval=0,
        	maxval=100,
        	factor=1.0,
        	decimal_places=1,
        	ref_level=0,
        	sample_rate=samp_rate,
        	number_rate=15,
        	average=True,
        	avg_alpha=0.03,
        	label="MER",
        	peak_hold=False,
        	show_gauge=True,
        )
        self.n_0.GetPage(1).GridAdd(self.wxgui_numbersink2_1.win, 0, 0, 1, 1)
        self.wxgui_fftsink2_0 = fftsink2.fft_sink_c(
        	self.n_0.GetPage(2).GetWin(),
        	baseband_freq=0,
        	y_per_div=10,
        	y_divs=10,
        	ref_level=0,
        	ref_scale=2.0,
        	sample_rate=samp_rate,
        	fft_size=2048,
        	fft_rate=15,
        	average=True,
        	avg_alpha=0.01,
        	title="FFT Plot",
        	peak_hold=False,
        )
        self.n_0.GetPage(2).GridAdd(self.wxgui_fftsink2_0.win, 0, 1, 1, 1)
        self.mer_probe_all_meassurements_cf_0 = mer.probe_all_meassurements_cf((0.9487+0.9487j,0.9487+0.3162j, 0.3162+0.9487j, 0.3162 +0.3162j,0.9487-0.9487j,0.9487- 0.3162j, 0.3162-0.9487j, 0.3162- 0.3162j,-0.9487+0.9487j,-0.9487+ 0.3162j,- 0.3162+0.9487j,- 0.3162+ 0.3162j,-0.9487-0.9487j,-0.9487- 0.3162j,-0.3162-0.9487j,-0.3162- 0.3162j), 0.05)
        self.digital_chunks_to_symbols_xx_0 = digital.chunks_to_symbols_bc((0.9487+0.9487j,0.9487+0.3162j, 0.3162+0.9487j, 0.3162 +0.3162j,0.9487-0.9487j,0.9487- 0.3162j, 0.3162-0.9487j, 0.3162- 0.3162j,-0.9487+0.9487j,-0.9487+ 0.3162j,- 0.3162+0.9487j,- 0.3162+ 0.3162j,-0.9487-0.9487j,-0.9487- 0.3162j,-0.3162-0.9487j,-0.3162- 0.3162j), 1)
        self.channels_impairments_0 = channels.impairments(pj, ai, qe, cs, 0, 0, 0, 0)
        self.channels_channel_model_0 = channels.channel_model(
        	noise_voltage=noise,
        	frequency_offset=0.0,
        	epsilon=1.0,
        	taps=(1, ),
        	noise_seed=0,
        	block_tags=False
        )
        self.blocks_throttle_0 = blocks.throttle(gr.sizeof_char*1, sym_rate,True)
        self.analog_random_source_x_0 = blocks.vector_source_b(map(int, numpy.random.randint(0, 16, 1000)), True)

        ##################################################
        # Connections
        ##################################################
        self.connect((self.analog_random_source_x_0, 0), (self.blocks_throttle_0, 0))    
        self.connect((self.blocks_throttle_0, 0), (self.digital_chunks_to_symbols_xx_0, 0))    
        self.connect((self.channels_channel_model_0, 0), (self.mer_probe_all_meassurements_cf_0, 0))    
        self.connect((self.channels_channel_model_0, 0), (self.wxgui_fftsink2_0, 0))    
        self.connect((self.channels_channel_model_0, 0), (self.wxgui_scopesink2_0_0, 0))    
        self.connect((self.channels_impairments_0, 0), (self.channels_channel_model_0, 0))    
        self.connect((self.digital_chunks_to_symbols_xx_0, 0), (self.channels_impairments_0, 0))    
        self.connect((self.mer_probe_all_meassurements_cf_0, 0), (self.wxgui_numbersink2_1, 0))    
        self.connect((self.mer_probe_all_meassurements_cf_0, 1), (self.wxgui_numbersink2_1_0, 0))    
        self.connect((self.mer_probe_all_meassurements_cf_0, 2), (self.wxgui_numbersink2_1_1, 0))    
        self.connect((self.mer_probe_all_meassurements_cf_0, 3), (self.wxgui_numbersink2_1_1_0, 0))    
        self.connect((self.mer_probe_all_meassurements_cf_0, 6), (self.wxgui_numbersink2_1_1_0_0, 0))    
        self.connect((self.mer_probe_all_meassurements_cf_0, 5), (self.wxgui_numbersink2_1_1_0_1, 0))    
        self.connect((self.mer_probe_all_meassurements_cf_0, 7), (self.wxgui_numbersink2_1_1_0_1_0, 0))    
        self.connect((self.mer_probe_all_meassurements_cf_0, 8), (self.wxgui_numbersink2_1_1_0_1_0_0, 0))    
        self.connect((self.mer_probe_all_meassurements_cf_0, 4), (self.wxgui_numbersink2_1_1_1, 0))    


    def get_sym_rate(self):
        return self.sym_rate

    def set_sym_rate(self, sym_rate):
        self.sym_rate = sym_rate
        self.blocks_throttle_0.set_sample_rate(self.sym_rate)
        self.wxgui_scopesink2_0_0.set_sample_rate(self.sym_rate)

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.wxgui_fftsink2_0.set_sample_rate(self.samp_rate)

    def get_qe(self):
        return self.qe

    def set_qe(self, qe):
        self.qe = qe
        self._qe_slider.set_value(self.qe)
        self._qe_text_box.set_value(self.qe)
        self.channels_impairments_0.set_phasebal(self.qe)

    def get_pj(self):
        return self.pj

    def set_pj(self, pj):
        self.pj = pj
        self._pj_slider.set_value(self.pj)
        self._pj_text_box.set_value(self.pj)
        self.channels_impairments_0.set_phase_noise_mag(self.pj)

    def get_noise(self):
        return self.noise

    def set_noise(self, noise):
        self.noise = noise
        self._noise_slider.set_value(self.noise)
        self._noise_text_box.set_value(self.noise)
        self.channels_channel_model_0.set_noise_voltage(self.noise)

    def get_cs(self):
        return self.cs

    def set_cs(self, cs):
        self.cs = cs
        self._cs_slider.set_value(self.cs)
        self._cs_text_box.set_value(self.cs)
        self.channels_impairments_0.set_q_ofs(self.cs)

    def get_ai(self):
        return self.ai

    def set_ai(self, ai):
        self.ai = ai
        self._ai_slider.set_value(self.ai)
        self._ai_text_box.set_value(self.ai)
        self.channels_impairments_0.set_magbal(self.ai)

if __name__ == '__main__':
    import ctypes
    import sys
    if sys.platform.startswith('linux'):
        try:
            x11 = ctypes.cdll.LoadLibrary('libX11.so')
            x11.XInitThreads()
        except:
            print "Warning: failed to XInitThreads()"
    parser = OptionParser(option_class=eng_option, usage="%prog: [options]")
    (options, args) = parser.parse_args()
    tb = top_block()
    tb.Start(True)
    tb.Wait()
