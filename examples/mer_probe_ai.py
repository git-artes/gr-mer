#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#
# SPDX-License-Identifier: GPL-3.0
#
# GNU Radio Python Flow Graph
# Title: Not titled yet
# GNU Radio version: 3.9.8.0

from distutils.version import StrictVersion

if __name__ == '__main__':
    import ctypes
    import sys
    if sys.platform.startswith('linux'):
        try:
            x11 = ctypes.cdll.LoadLibrary('libX11.so')
            x11.XInitThreads()
        except:
            print("Warning: failed to XInitThreads()")

from PyQt5 import Qt
from gnuradio import qtgui
from gnuradio.filter import firdes
import sip
from gnuradio import blocks
import numpy
from gnuradio import channels
from gnuradio import dtv
from gnuradio import gr
from gnuradio.fft import window
import sys
import signal
from argparse import ArgumentParser
from gnuradio.eng_arg import eng_float, intx
from gnuradio import eng_notation
from gnuradio.qtgui import Range, RangeWidget
from PyQt5 import QtCore
import mer



from gnuradio import qtgui

class mer_probe_ai(gr.top_block, Qt.QWidget):

    def __init__(self):
        gr.top_block.__init__(self, "Not titled yet", catch_exceptions=True)
        Qt.QWidget.__init__(self)
        self.setWindowTitle("Not titled yet")
        qtgui.util.check_set_qss()
        try:
            self.setWindowIcon(Qt.QIcon.fromTheme('gnuradio-grc'))
        except:
            pass
        self.top_scroll_layout = Qt.QVBoxLayout()
        self.setLayout(self.top_scroll_layout)
        self.top_scroll = Qt.QScrollArea()
        self.top_scroll.setFrameStyle(Qt.QFrame.NoFrame)
        self.top_scroll_layout.addWidget(self.top_scroll)
        self.top_scroll.setWidgetResizable(True)
        self.top_widget = Qt.QWidget()
        self.top_scroll.setWidget(self.top_widget)
        self.top_layout = Qt.QVBoxLayout(self.top_widget)
        self.top_grid_layout = Qt.QGridLayout()
        self.top_layout.addLayout(self.top_grid_layout)

        self.settings = Qt.QSettings("GNU Radio", "mer_probe_ai")

        try:
            if StrictVersion(Qt.qVersion()) < StrictVersion("5.0.0"):
                self.restoreGeometry(self.settings.value("geometry").toByteArray())
            else:
                self.restoreGeometry(self.settings.value("geometry"))
        except:
            pass

        ##################################################
        # Variables
        ##################################################
        self.samp_rate = samp_rate = 32000
        self.qe = qe = 0
        self.pj = pj = -40
        self.noise = noise = 10e-3
        self.cs = cs = 0
        self.const_256QAM = const_256QAM = [(1.1504475+1.1504475j),(1.1504475+0.9970545j),(0.9970545+1.1504475j),(0.9970545+0.9970545j),(1.1504475+0.6902685j),(1.1504475+0.8436615j),(0.9970545+0.6902685j),(0.9970545+0.8436615j),(0.6902685+1.1504475j),(0.6902685+0.9970545j),(0.8436615+1.1504475j),(0.8436615+0.9970545j),(0.6902685+0.6902685j),(0.6902685+0.8436615j),(0.8436615+0.6902685j),(0.8436615+0.8436615j),(1.1504475+0.0766965j),(1.1504475+0.2300895j),(0.9970545+0.0766965j),(0.9970545+0.2300895j),(1.1504475+0.5368755j),(1.1504475+0.38348252j),(0.9970545+0.5368755j),(0.9970545+0.38348252j),(0.6902685+0.0766965j),(0.6902685+0.2300895j),(0.8436615+0.0766965j),(0.8436615+0.2300895j),(0.6902685+0.5368755j),(0.6902685+0.38348252j),(0.8436615+0.5368755j),(0.8436615+0.38348252j),(0.0766965+1.1504475j),(0.0766965+0.9970545j),(0.2300895+1.1504475j),(0.2300895+0.9970545j),(0.0766965+0.6902685j),(0.0766965+0.8436615j),(0.2300895+0.6902685j),(0.2300895+0.8436615j),(0.5368755+1.1504475j),(0.5368755+0.9970545j),(0.38348252+1.1504475j),(0.38348252+0.9970545j),(0.5368755+0.6902685j),(0.5368755+0.8436615j),(0.38348252+0.6902685j),(0.38348252+0.8436615j),(0.0766965+0.0766965j),(0.0766965+0.2300895j),(0.2300895+0.0766965j),(0.2300895+0.2300895j),(0.0766965+0.5368755j),(0.0766965+0.38348252j),(0.2300895+0.5368755j),(0.2300895+0.38348252j),(0.5368755+0.0766965j),(0.5368755+0.2300895j),(0.38348252+0.0766965j),(0.38348252+0.2300895j),(0.5368755+0.5368755j),(0.5368755+0.38348252j),(0.38348252+0.5368755j),(0.38348252+0.38348252j),(1.1504475-1.1504475j),(1.1504475-0.9970545j),(0.9970545-1.1504475j),(0.9970545-0.9970545j),(1.1504475-0.6902685j),(1.1504475-0.8436615j),(0.9970545-0.6902685j),(0.9970545-0.8436615j),(0.6902685-1.1504475j),(0.6902685-0.9970545j),(0.8436615-1.1504475j),(0.8436615-0.9970545j),(0.6902685-0.6902685j),(0.6902685-0.8436615j),(0.8436615-0.6902685j),(0.8436615-0.8436615j),(1.1504475-0.0766965j),(1.1504475-0.2300895j),(0.9970545-0.0766965j),(0.9970545-0.2300895j),(1.1504475-0.5368755j),(1.1504475-0.38348252j),(0.9970545-0.5368755j),(0.9970545-0.38348252j),(0.6902685-0.0766965j),(0.6902685-0.2300895j),(0.8436615-0.0766965j),(0.8436615-0.2300895j),(0.6902685-0.5368755j),(0.6902685-0.38348252j),(0.8436615-0.5368755j),(0.8436615-0.38348252j),(0.0766965-1.1504475j),(0.0766965-0.9970545j),(0.2300895-1.1504475j),(0.2300895-0.9970545j),(0.0766965-0.6902685j),(0.0766965-0.8436615j),(0.2300895-0.6902685j),(0.2300895-0.8436615j),(0.5368755-1.1504475j),(0.5368755-0.9970545j),(0.38348252-1.1504475j),(0.38348252-0.9970545j),(0.5368755-0.6902685j),(0.5368755-0.8436615j),(0.38348252-0.6902685j),(0.38348252-0.8436615j),(0.0766965-0.0766965j),(0.0766965-0.2300895j),(0.2300895-0.0766965j),(0.2300895-0.2300895j),(0.0766965-0.5368755j),(0.0766965-0.38348252j),(0.2300895-0.5368755j),(0.2300895-0.38348252j),(0.5368755-0.0766965j),(0.5368755-0.2300895j),(0.38348252-0.0766965j),(0.38348252-0.2300895j),(0.5368755-0.5368755j),(0.5368755-0.38348252j),(0.38348252-0.5368755j),(0.38348252-0.38348252j),(-1.1504475+1.1504475j),(-1.1504475+0.9970545j),(-0.9970545+1.1504475j),(-0.9970545+0.9970545j),(-1.1504475+0.6902685j),(-1.1504475+0.8436615j),(-0.9970545+0.6902685j),(-0.9970545+0.8436615j),(-0.6902685+1.1504475j),(-0.6902685+0.9970545j),(-0.8436615+1.1504475j),(-0.8436615+0.9970545j),(-0.6902685+0.6902685j),(-0.6902685+0.8436615j),(-0.8436615+0.6902685j),(-0.8436615+0.8436615j),(-1.1504475+0.0766965j),(-1.1504475+0.2300895j),(-0.9970545+0.0766965j),(-0.9970545+0.2300895j),(-1.1504475+0.5368755j),(-1.1504475+0.38348252j),(-0.9970545+0.5368755j),(-0.9970545+0.38348252j),(-0.6902685+0.0766965j),(-0.6902685+0.2300895j),(-0.8436615+0.0766965j),(-0.8436615+0.2300895j),(-0.6902685+0.5368755j),(-0.6902685+0.38348252j),(-0.8436615+0.5368755j),(-0.8436615+0.38348252j),(-0.0766965+1.1504475j),(-0.0766965+0.9970545j),(-0.2300895+1.1504475j),(-0.2300895+0.9970545j),(-0.0766965+0.6902685j),(-0.0766965+0.8436615j),(-0.2300895+0.6902685j),(-0.2300895+0.8436615j),(-0.5368755+1.1504475j),(-0.5368755+0.9970545j),(-0.38348252+1.1504475j),(-0.38348252+0.9970545j),(-0.5368755+0.6902685j),(-0.5368755+0.8436615j),(-0.38348252+0.6902685j),(-0.38348252+0.8436615j),(-0.0766965+0.0766965j),(-0.0766965+0.2300895j),(-0.2300895+0.0766965j),(-0.2300895+0.2300895j),(-0.0766965+0.5368755j),(-0.0766965+0.38348252j),(-0.2300895+0.5368755j),(-0.2300895+0.38348252j),(-0.5368755+0.0766965j),(-0.5368755+0.2300895j),(-0.38348252+0.0766965j),(-0.38348252+0.2300895j),(-0.5368755+0.5368755j),(-0.5368755+0.38348252j),(-0.38348252+0.5368755j),(-0.38348252+0.38348252j),(-1.1504475-1.1504475j),(-1.1504475-0.9970545j),(-0.9970545-1.1504475j),(-0.9970545-0.9970545j),(-1.1504475-0.6902685j),(-1.1504475-0.8436615j),(-0.9970545-0.6902685j),(-0.9970545-0.8436615j),(-0.6902685-1.1504475j),(-0.6902685-0.9970545j),(-0.8436615-1.1504475j),(-0.8436615-0.9970545j),(-0.6902685-0.6902685j),(-0.6902685-0.8436615j),(-0.8436615-0.6902685j),(-0.8436615-0.8436615j),(-1.1504475-0.0766965j),(-1.1504475-0.2300895j),(-0.9970545-0.0766965j),(-0.9970545-0.2300895j),(-1.1504475-0.5368755j),(-1.1504475-0.38348252j),(-0.9970545-0.5368755j),(-0.9970545-0.38348252j),(-0.6902685-0.0766965j),(-0.6902685-0.2300895j),(-0.8436615-0.0766965j),(-0.8436615-0.2300895j),(-0.6902685-0.5368755j),(-0.6902685-0.38348252j),(-0.8436615-0.5368755j),(-0.8436615-0.38348252j),(-0.0766965-1.1504475j),(-0.0766965-0.9970545j),(-0.2300895-1.1504475j),(-0.2300895-0.9970545j),(-0.0766965-0.6902685j),(-0.0766965-0.8436615j),(-0.2300895-0.6902685j),(-0.2300895-0.8436615j),(-0.5368755-1.1504475j),(-0.5368755-0.9970545j),(-0.38348252-1.1504475j),(-0.38348252-0.9970545j),(-0.5368755-0.6902685j),(-0.5368755-0.8436615j),(-0.38348252-0.6902685j),(-0.38348252-0.8436615j),(-0.0766965-0.0766965j),(-0.0766965-0.2300895j),(-0.2300895-0.0766965j),(-0.2300895-0.2300895j),(-0.0766965-0.5368755j),(-0.0766965-0.38348252j),(-0.2300895-0.5368755j),(-0.2300895-0.38348252j),(-0.5368755-0.0766965j),(-0.5368755-0.2300895j),(-0.38348252-0.0766965j),(-0.38348252-0.2300895j),(-0.5368755-0.5368755j),(-0.5368755-0.38348252j),(-0.38348252-0.5368755j),(-0.38348252-0.38348252j)]
        self.ai = ai = 0

        ##################################################
        # Blocks
        ##################################################
        self.qtgui_0 = Qt.QTabWidget()
        self.qtgui_0_widget_0 = Qt.QWidget()
        self.qtgui_0_layout_0 = Qt.QBoxLayout(Qt.QBoxLayout.TopToBottom, self.qtgui_0_widget_0)
        self.qtgui_0_grid_layout_0 = Qt.QGridLayout()
        self.qtgui_0_layout_0.addLayout(self.qtgui_0_grid_layout_0)
        self.qtgui_0.addTab(self.qtgui_0_widget_0, 'Constellation')
        self.qtgui_0_widget_1 = Qt.QWidget()
        self.qtgui_0_layout_1 = Qt.QBoxLayout(Qt.QBoxLayout.TopToBottom, self.qtgui_0_widget_1)
        self.qtgui_0_grid_layout_1 = Qt.QGridLayout()
        self.qtgui_0_layout_1.addLayout(self.qtgui_0_grid_layout_1)
        self.qtgui_0.addTab(self.qtgui_0_widget_1, 'Measures')
        self.qtgui_0_widget_2 = Qt.QWidget()
        self.qtgui_0_layout_2 = Qt.QBoxLayout(Qt.QBoxLayout.TopToBottom, self.qtgui_0_widget_2)
        self.qtgui_0_grid_layout_2 = Qt.QGridLayout()
        self.qtgui_0_layout_2.addLayout(self.qtgui_0_grid_layout_2)
        self.qtgui_0.addTab(self.qtgui_0_widget_2, 'FFT')
        self.top_grid_layout.addWidget(self.qtgui_0, 1, 0, 6, 5)
        for r in range(1, 7):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(0, 5):
            self.top_grid_layout.setColumnStretch(c, 1)
        self._qe_range = Range(0, 5, .001, 0, 200)
        self._qe_win = RangeWidget(self._qe_range, self.set_qe, "qe", "counter_slider", float, QtCore.Qt.Horizontal)
        self.top_grid_layout.addWidget(self._qe_win, 0, 3, 1, 1)
        for r in range(0, 1):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(3, 4):
            self.top_grid_layout.setColumnStretch(c, 1)
        self._pj_range = Range(-40, 0, .001, -40, 200)
        self._pj_win = RangeWidget(self._pj_range, self.set_pj, "pj", "counter_slider", float, QtCore.Qt.Horizontal)
        self.top_grid_layout.addWidget(self._pj_win, 0, 0, 1, 1)
        for r in range(0, 1):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(0, 1):
            self.top_grid_layout.setColumnStretch(c, 1)
        self._noise_range = Range(0, 100e-3, .001, 10e-3, 200)
        self._noise_win = RangeWidget(self._noise_range, self.set_noise, "noise", "counter_slider", float, QtCore.Qt.Horizontal)
        self.top_grid_layout.addWidget(self._noise_win, 0, 4, 1, 1)
        for r in range(0, 1):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(4, 5):
            self.top_grid_layout.setColumnStretch(c, 1)
        self._cs_range = Range(0, .5, .001, 0, 200)
        self._cs_win = RangeWidget(self._cs_range, self.set_cs, "cs", "counter_slider", float, QtCore.Qt.Horizontal)
        self.top_grid_layout.addWidget(self._cs_win, 0, 1, 1, 1)
        for r in range(0, 1):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(1, 2):
            self.top_grid_layout.setColumnStretch(c, 1)
        self._ai_range = Range(0, 5, .001, 0, 200)
        self._ai_win = RangeWidget(self._ai_range, self.set_ai, "ai", "counter_slider", float, QtCore.Qt.Horizontal)
        self.top_grid_layout.addWidget(self._ai_win, 0, 2, 1, 1)
        for r in range(0, 1):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(2, 3):
            self.top_grid_layout.setColumnStretch(c, 1)
        self.qtgui_number_sink_1 = qtgui.number_sink(
            gr.sizeof_float,
            0,
            qtgui.NUM_GRAPH_HORIZ,
            1,
            None # parent
        )
        self.qtgui_number_sink_1.set_update_time(0.10)
        self.qtgui_number_sink_1.set_title("Amplitude Imbalance Vertical")

        labels = [" ", '', '', '', '',
            '', '', '', '', '']
        units = ['V', '', '', '', '',
            '', '', '', '', '']
        colors = [("blue", "red"), ("black", "black"), ("black", "black"), ("black", "black"), ("black", "black"),
            ("black", "black"), ("black", "black"), ("black", "black"), ("black", "black"), ("black", "black")]
        factor = [1, 1, 1, 1, 1,
            1, 1, 1, 1, 1]

        for i in range(1):
            self.qtgui_number_sink_1.set_min(i, 0)
            self.qtgui_number_sink_1.set_max(i, 1)
            self.qtgui_number_sink_1.set_color(i, colors[i][0], colors[i][1])
            if len(labels[i]) == 0:
                self.qtgui_number_sink_1.set_label(i, "Data {0}".format(i))
            else:
                self.qtgui_number_sink_1.set_label(i, labels[i])
            self.qtgui_number_sink_1.set_unit(i, units[i])
            self.qtgui_number_sink_1.set_factor(i, factor[i])

        self.qtgui_number_sink_1.enable_autoscale(False)
        self._qtgui_number_sink_1_win = sip.wrapinstance(self.qtgui_number_sink_1.qwidget(), Qt.QWidget)
        self.qtgui_0_grid_layout_1.addWidget(self._qtgui_number_sink_1_win, 1, 2, 1, 1)
        for r in range(1, 2):
            self.qtgui_0_grid_layout_1.setRowStretch(r, 1)
        for c in range(2, 3):
            self.qtgui_0_grid_layout_1.setColumnStretch(c, 1)
        self.qtgui_number_sink_0_4 = qtgui.number_sink(
            gr.sizeof_float,
            0,
            qtgui.NUM_GRAPH_HORIZ,
            1,
            None # parent
        )
        self.qtgui_number_sink_0_4.set_update_time(0.10)
        self.qtgui_number_sink_0_4.set_title("Phase Jitter Variance")

        labels = [" ", '', '', '', '',
            '', '', '', '', '']
        units = ['', '', '', '', '',
            '', '', '', '', '']
        colors = [("blue", "red"), ("black", "black"), ("black", "black"), ("black", "black"), ("black", "black"),
            ("black", "black"), ("black", "black"), ("black", "black"), ("black", "black"), ("black", "black")]
        factor = [1, 1, 1, 1, 1,
            1, 1, 1, 1, 1]

        for i in range(1):
            self.qtgui_number_sink_0_4.set_min(i, -.1)
            self.qtgui_number_sink_0_4.set_max(i, .1)
            self.qtgui_number_sink_0_4.set_color(i, colors[i][0], colors[i][1])
            if len(labels[i]) == 0:
                self.qtgui_number_sink_0_4.set_label(i, "Data {0}".format(i))
            else:
                self.qtgui_number_sink_0_4.set_label(i, labels[i])
            self.qtgui_number_sink_0_4.set_unit(i, units[i])
            self.qtgui_number_sink_0_4.set_factor(i, factor[i])

        self.qtgui_number_sink_0_4.enable_autoscale(False)
        self._qtgui_number_sink_0_4_win = sip.wrapinstance(self.qtgui_number_sink_0_4.qwidget(), Qt.QWidget)
        self.qtgui_0_grid_layout_1.addWidget(self._qtgui_number_sink_0_4_win, 2, 2, 1, 1)
        for r in range(2, 3):
            self.qtgui_0_grid_layout_1.setRowStretch(r, 1)
        for c in range(2, 3):
            self.qtgui_0_grid_layout_1.setColumnStretch(c, 1)
        self.qtgui_number_sink_0_3 = qtgui.number_sink(
            gr.sizeof_float,
            0,
            qtgui.NUM_GRAPH_HORIZ,
            1,
            None # parent
        )
        self.qtgui_number_sink_0_3.set_update_time(0.10)
        self.qtgui_number_sink_0_3.set_title("Quadrature Horizontal Angle Error ")

        labels = [" ", '', '', '', '',
            '', '', '', '', '']
        units = ['degrees', '', '', '', '',
            '', '', '', '', '']
        colors = [("blue", "red"), ("black", "black"), ("black", "black"), ("black", "black"), ("black", "black"),
            ("black", "black"), ("black", "black"), ("black", "black"), ("black", "black"), ("black", "black")]
        factor = [1, 1, 1, 1, 1,
            1, 1, 1, 1, 1]

        for i in range(1):
            self.qtgui_number_sink_0_3.set_min(i, -10)
            self.qtgui_number_sink_0_3.set_max(i, 10)
            self.qtgui_number_sink_0_3.set_color(i, colors[i][0], colors[i][1])
            if len(labels[i]) == 0:
                self.qtgui_number_sink_0_3.set_label(i, "Data {0}".format(i))
            else:
                self.qtgui_number_sink_0_3.set_label(i, labels[i])
            self.qtgui_number_sink_0_3.set_unit(i, units[i])
            self.qtgui_number_sink_0_3.set_factor(i, factor[i])

        self.qtgui_number_sink_0_3.enable_autoscale(False)
        self._qtgui_number_sink_0_3_win = sip.wrapinstance(self.qtgui_number_sink_0_3.qwidget(), Qt.QWidget)
        self.qtgui_0_grid_layout_1.addWidget(self._qtgui_number_sink_0_3_win, 2, 0, 1, 1)
        for r in range(2, 3):
            self.qtgui_0_grid_layout_1.setRowStretch(r, 1)
        for c in range(0, 1):
            self.qtgui_0_grid_layout_1.setColumnStretch(c, 1)
        self.qtgui_number_sink_0_2 = qtgui.number_sink(
            gr.sizeof_float,
            0,
            qtgui.NUM_GRAPH_HORIZ,
            1,
            None # parent
        )
        self.qtgui_number_sink_0_2.set_update_time(0.10)
        self.qtgui_number_sink_0_2.set_title("Amplitude Imbalance Horizontal")

        labels = [" ", '', '', '', '',
            '', '', '', '', '']
        units = ['V', '', '', '', '',
            '', '', '', '', '']
        colors = [("blue", "red"), ("black", "black"), ("black", "black"), ("black", "black"), ("black", "black"),
            ("black", "black"), ("black", "black"), ("black", "black"), ("black", "black"), ("black", "black")]
        factor = [1, 1, 1, 1, 1,
            1, 1, 1, 1, 1]

        for i in range(1):
            self.qtgui_number_sink_0_2.set_min(i, 0)
            self.qtgui_number_sink_0_2.set_max(i, 1)
            self.qtgui_number_sink_0_2.set_color(i, colors[i][0], colors[i][1])
            if len(labels[i]) == 0:
                self.qtgui_number_sink_0_2.set_label(i, "Data {0}".format(i))
            else:
                self.qtgui_number_sink_0_2.set_label(i, labels[i])
            self.qtgui_number_sink_0_2.set_unit(i, units[i])
            self.qtgui_number_sink_0_2.set_factor(i, factor[i])

        self.qtgui_number_sink_0_2.enable_autoscale(False)
        self._qtgui_number_sink_0_2_win = sip.wrapinstance(self.qtgui_number_sink_0_2.qwidget(), Qt.QWidget)
        self.qtgui_0_grid_layout_1.addWidget(self._qtgui_number_sink_0_2_win, 1, 1, 1, 1)
        for r in range(1, 2):
            self.qtgui_0_grid_layout_1.setRowStretch(r, 1)
        for c in range(1, 2):
            self.qtgui_0_grid_layout_1.setColumnStretch(c, 1)
        self.qtgui_number_sink_0_1 = qtgui.number_sink(
            gr.sizeof_float,
            0,
            qtgui.NUM_GRAPH_HORIZ,
            1,
            None # parent
        )
        self.qtgui_number_sink_0_1.set_update_time(0.10)
        self.qtgui_number_sink_0_1.set_title("Carrier Suppression")

        labels = [" ", '', '', '', '',
            '', '', '', '', '']
        units = ['Power Normalized to Tx Power', '', '', '', '',
            '', '', '', '', '']
        colors = [("blue", "red"), ("black", "black"), ("black", "black"), ("black", "black"), ("black", "black"),
            ("black", "black"), ("black", "black"), ("black", "black"), ("black", "black"), ("black", "black")]
        factor = [1, 1, 1, 1, 1,
            1, 1, 1, 1, 1]

        for i in range(1):
            self.qtgui_number_sink_0_1.set_min(i, 0)
            self.qtgui_number_sink_0_1.set_max(i, 1)
            self.qtgui_number_sink_0_1.set_color(i, colors[i][0], colors[i][1])
            if len(labels[i]) == 0:
                self.qtgui_number_sink_0_1.set_label(i, "Data {0}".format(i))
            else:
                self.qtgui_number_sink_0_1.set_label(i, labels[i])
            self.qtgui_number_sink_0_1.set_unit(i, units[i])
            self.qtgui_number_sink_0_1.set_factor(i, factor[i])

        self.qtgui_number_sink_0_1.enable_autoscale(False)
        self._qtgui_number_sink_0_1_win = sip.wrapinstance(self.qtgui_number_sink_0_1.qwidget(), Qt.QWidget)
        self.qtgui_0_grid_layout_1.addWidget(self._qtgui_number_sink_0_1_win, 1, 0, 1, 1)
        for r in range(1, 2):
            self.qtgui_0_grid_layout_1.setRowStretch(r, 1)
        for c in range(0, 1):
            self.qtgui_0_grid_layout_1.setColumnStretch(c, 1)
        self.qtgui_number_sink_0_0_1 = qtgui.number_sink(
            gr.sizeof_float,
            0,
            qtgui.NUM_GRAPH_HORIZ,
            1,
            None # parent
        )
        self.qtgui_number_sink_0_0_1.set_update_time(0.10)
        self.qtgui_number_sink_0_0_1.set_title("SNR")

        labels = [" ", '', '', '', '',
            '', '', '', '', '']
        units = ['dB', '', '', '', '',
            '', '', '', '', '']
        colors = [("blue", "red"), ("black", "black"), ("black", "black"), ("black", "black"), ("black", "black"),
            ("black", "black"), ("black", "black"), ("black", "black"), ("black", "black"), ("black", "black")]
        factor = [1, 1, 1, 1, 1,
            1, 1, 1, 1, 1]

        for i in range(1):
            self.qtgui_number_sink_0_0_1.set_min(i, 0)
            self.qtgui_number_sink_0_0_1.set_max(i, 100)
            self.qtgui_number_sink_0_0_1.set_color(i, colors[i][0], colors[i][1])
            if len(labels[i]) == 0:
                self.qtgui_number_sink_0_0_1.set_label(i, "Data {0}".format(i))
            else:
                self.qtgui_number_sink_0_0_1.set_label(i, labels[i])
            self.qtgui_number_sink_0_0_1.set_unit(i, units[i])
            self.qtgui_number_sink_0_0_1.set_factor(i, factor[i])

        self.qtgui_number_sink_0_0_1.enable_autoscale(False)
        self._qtgui_number_sink_0_0_1_win = sip.wrapinstance(self.qtgui_number_sink_0_0_1.qwidget(), Qt.QWidget)
        self.qtgui_0_grid_layout_1.addWidget(self._qtgui_number_sink_0_0_1_win, 0, 2, 1, 1)
        for r in range(0, 1):
            self.qtgui_0_grid_layout_1.setRowStretch(r, 1)
        for c in range(2, 3):
            self.qtgui_0_grid_layout_1.setColumnStretch(c, 1)
        self.qtgui_number_sink_0_0_0 = qtgui.number_sink(
            gr.sizeof_float,
            0,
            qtgui.NUM_GRAPH_HORIZ,
            1,
            None # parent
        )
        self.qtgui_number_sink_0_0_0.set_update_time(0.10)
        self.qtgui_number_sink_0_0_0.set_title("Quadrature Vertical Angle Error ")

        labels = [" ", '', '', '', '',
            '', '', '', '', '']
        units = ['degrees', '', '', '', '',
            '', '', '', '', '']
        colors = [("blue", "red"), ("black", "black"), ("black", "black"), ("black", "black"), ("black", "black"),
            ("black", "black"), ("black", "black"), ("black", "black"), ("black", "black"), ("black", "black")]
        factor = [1, 1, 1, 1, 1,
            1, 1, 1, 1, 1]

        for i in range(1):
            self.qtgui_number_sink_0_0_0.set_min(i, -10)
            self.qtgui_number_sink_0_0_0.set_max(i, 10)
            self.qtgui_number_sink_0_0_0.set_color(i, colors[i][0], colors[i][1])
            if len(labels[i]) == 0:
                self.qtgui_number_sink_0_0_0.set_label(i, "Data {0}".format(i))
            else:
                self.qtgui_number_sink_0_0_0.set_label(i, labels[i])
            self.qtgui_number_sink_0_0_0.set_unit(i, units[i])
            self.qtgui_number_sink_0_0_0.set_factor(i, factor[i])

        self.qtgui_number_sink_0_0_0.enable_autoscale(False)
        self._qtgui_number_sink_0_0_0_win = sip.wrapinstance(self.qtgui_number_sink_0_0_0.qwidget(), Qt.QWidget)
        self.qtgui_0_grid_layout_1.addWidget(self._qtgui_number_sink_0_0_0_win, 2, 1, 1, 1)
        for r in range(2, 3):
            self.qtgui_0_grid_layout_1.setRowStretch(r, 1)
        for c in range(1, 2):
            self.qtgui_0_grid_layout_1.setColumnStretch(c, 1)
        self.qtgui_number_sink_0_0 = qtgui.number_sink(
            gr.sizeof_float,
            0,
            qtgui.NUM_GRAPH_HORIZ,
            1,
            None # parent
        )
        self.qtgui_number_sink_0_0.set_update_time(0.10)
        self.qtgui_number_sink_0_0.set_title("STE")

        labels = [" ", '', '', '', '',
            '', '', '', '', '']
        units = ['V', '', '', '', '',
            '', '', '', '', '']
        colors = [("blue", "red"), ("black", "black"), ("black", "black"), ("black", "black"), ("black", "black"),
            ("black", "black"), ("black", "black"), ("black", "black"), ("black", "black"), ("black", "black")]
        factor = [1, 1, 1, 1, 1,
            1, 1, 1, 1, 1]

        for i in range(1):
            self.qtgui_number_sink_0_0.set_min(i, 0)
            self.qtgui_number_sink_0_0.set_max(i, 1)
            self.qtgui_number_sink_0_0.set_color(i, colors[i][0], colors[i][1])
            if len(labels[i]) == 0:
                self.qtgui_number_sink_0_0.set_label(i, "Data {0}".format(i))
            else:
                self.qtgui_number_sink_0_0.set_label(i, labels[i])
            self.qtgui_number_sink_0_0.set_unit(i, units[i])
            self.qtgui_number_sink_0_0.set_factor(i, factor[i])

        self.qtgui_number_sink_0_0.enable_autoscale(False)
        self._qtgui_number_sink_0_0_win = sip.wrapinstance(self.qtgui_number_sink_0_0.qwidget(), Qt.QWidget)
        self.qtgui_0_grid_layout_1.addWidget(self._qtgui_number_sink_0_0_win, 0, 1, 1, 1)
        for r in range(0, 1):
            self.qtgui_0_grid_layout_1.setRowStretch(r, 1)
        for c in range(1, 2):
            self.qtgui_0_grid_layout_1.setColumnStretch(c, 1)
        self.qtgui_number_sink_0 = qtgui.number_sink(
            gr.sizeof_float,
            0,
            qtgui.NUM_GRAPH_HORIZ,
            1,
            None # parent
        )
        self.qtgui_number_sink_0.set_update_time(0.10)
        self.qtgui_number_sink_0.set_title("MER")

        labels = [" ", '', '', '', '',
            '', '', '', '', '']
        units = ['dB', '', '', '', '',
            '', '', '', '', '']
        colors = [("blue", "red"), ("black", "black"), ("black", "black"), ("black", "black"), ("black", "black"),
            ("black", "black"), ("black", "black"), ("black", "black"), ("black", "black"), ("black", "black")]
        factor = [1, 1, 1, 1, 1,
            1, 1, 1, 1, 1]

        for i in range(1):
            self.qtgui_number_sink_0.set_min(i, 0)
            self.qtgui_number_sink_0.set_max(i, 100)
            self.qtgui_number_sink_0.set_color(i, colors[i][0], colors[i][1])
            if len(labels[i]) == 0:
                self.qtgui_number_sink_0.set_label(i, "Data {0}".format(i))
            else:
                self.qtgui_number_sink_0.set_label(i, labels[i])
            self.qtgui_number_sink_0.set_unit(i, units[i])
            self.qtgui_number_sink_0.set_factor(i, factor[i])

        self.qtgui_number_sink_0.enable_autoscale(False)
        self._qtgui_number_sink_0_win = sip.wrapinstance(self.qtgui_number_sink_0.qwidget(), Qt.QWidget)
        self.qtgui_0_grid_layout_1.addWidget(self._qtgui_number_sink_0_win, 0, 0, 1, 1)
        for r in range(0, 1):
            self.qtgui_0_grid_layout_1.setRowStretch(r, 1)
        for c in range(0, 1):
            self.qtgui_0_grid_layout_1.setColumnStretch(c, 1)
        self.qtgui_freq_sink_x_0 = qtgui.freq_sink_c(
            2048, #size
            window.WIN_BLACKMAN_hARRIS, #wintype
            0, #fc
            samp_rate, #bw
            "", #name
            1,
            None # parent
        )
        self.qtgui_freq_sink_x_0.set_update_time(0.10)
        self.qtgui_freq_sink_x_0.set_y_axis(-140, 10)
        self.qtgui_freq_sink_x_0.set_y_label('Relative Gain', 'dB')
        self.qtgui_freq_sink_x_0.set_trigger_mode(qtgui.TRIG_MODE_FREE, 0.0, 0, "")
        self.qtgui_freq_sink_x_0.enable_autoscale(False)
        self.qtgui_freq_sink_x_0.enable_grid(False)
        self.qtgui_freq_sink_x_0.set_fft_average(1.0)
        self.qtgui_freq_sink_x_0.enable_axis_labels(True)
        self.qtgui_freq_sink_x_0.enable_control_panel(False)
        self.qtgui_freq_sink_x_0.set_fft_window_normalized(False)



        labels = ['', '', '', '', '',
            '', '', '', '', '']
        widths = [1, 1, 1, 1, 1,
            1, 1, 1, 1, 1]
        colors = ["blue", "red", "green", "black", "cyan",
            "magenta", "yellow", "dark red", "dark green", "dark blue"]
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0, 1.0]

        for i in range(1):
            if len(labels[i]) == 0:
                self.qtgui_freq_sink_x_0.set_line_label(i, "Data {0}".format(i))
            else:
                self.qtgui_freq_sink_x_0.set_line_label(i, labels[i])
            self.qtgui_freq_sink_x_0.set_line_width(i, widths[i])
            self.qtgui_freq_sink_x_0.set_line_color(i, colors[i])
            self.qtgui_freq_sink_x_0.set_line_alpha(i, alphas[i])

        self._qtgui_freq_sink_x_0_win = sip.wrapinstance(self.qtgui_freq_sink_x_0.qwidget(), Qt.QWidget)
        self.qtgui_0_grid_layout_2.addWidget(self._qtgui_freq_sink_x_0_win, 0, 0, 1, 1)
        for r in range(0, 1):
            self.qtgui_0_grid_layout_2.setRowStretch(r, 1)
        for c in range(0, 1):
            self.qtgui_0_grid_layout_2.setColumnStretch(c, 1)
        self.qtgui_const_sink_x_0_0 = qtgui.const_sink_c(
            1024*10, #size
            "Rotated Constellation", #name
            1, #number of inputs
            None # parent
        )
        self.qtgui_const_sink_x_0_0.set_update_time(0.10)
        self.qtgui_const_sink_x_0_0.set_y_axis(-2, 2)
        self.qtgui_const_sink_x_0_0.set_x_axis(-2, 2)
        self.qtgui_const_sink_x_0_0.set_trigger_mode(qtgui.TRIG_MODE_FREE, qtgui.TRIG_SLOPE_POS, 0.0, 0, "")
        self.qtgui_const_sink_x_0_0.enable_autoscale(False)
        self.qtgui_const_sink_x_0_0.enable_grid(False)
        self.qtgui_const_sink_x_0_0.enable_axis_labels(True)


        labels = ['', '', '', '', '',
            '', '', '', '', '']
        widths = [1, 1, 1, 1, 1,
            1, 1, 1, 1, 1]
        colors = ["blue", "red", "red", "red", "red",
            "red", "red", "red", "red", "red"]
        styles = [0, 0, 0, 0, 0,
            0, 0, 0, 0, 0]
        markers = [0, 0, 0, 0, 0,
            0, 0, 0, 0, 0]
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0, 1.0]

        for i in range(1):
            if len(labels[i]) == 0:
                self.qtgui_const_sink_x_0_0.set_line_label(i, "Data {0}".format(i))
            else:
                self.qtgui_const_sink_x_0_0.set_line_label(i, labels[i])
            self.qtgui_const_sink_x_0_0.set_line_width(i, widths[i])
            self.qtgui_const_sink_x_0_0.set_line_color(i, colors[i])
            self.qtgui_const_sink_x_0_0.set_line_style(i, styles[i])
            self.qtgui_const_sink_x_0_0.set_line_marker(i, markers[i])
            self.qtgui_const_sink_x_0_0.set_line_alpha(i, alphas[i])

        self._qtgui_const_sink_x_0_0_win = sip.wrapinstance(self.qtgui_const_sink_x_0_0.qwidget(), Qt.QWidget)
        self.top_layout.addWidget(self._qtgui_const_sink_x_0_0_win)
        self.qtgui_const_sink_x_0 = qtgui.const_sink_c(
            1024*10, #size
            "", #name
            1, #number of inputs
            None # parent
        )
        self.qtgui_const_sink_x_0.set_update_time(0.10)
        self.qtgui_const_sink_x_0.set_y_axis(-2, 2)
        self.qtgui_const_sink_x_0.set_x_axis(-2, 2)
        self.qtgui_const_sink_x_0.set_trigger_mode(qtgui.TRIG_MODE_FREE, qtgui.TRIG_SLOPE_POS, 0.0, 0, "")
        self.qtgui_const_sink_x_0.enable_autoscale(False)
        self.qtgui_const_sink_x_0.enable_grid(False)
        self.qtgui_const_sink_x_0.enable_axis_labels(True)


        labels = ['', '', '', '', '',
            '', '', '', '', '']
        widths = [1, 1, 1, 1, 1,
            1, 1, 1, 1, 1]
        colors = ["blue", "red", "red", "red", "red",
            "red", "red", "red", "red", "red"]
        styles = [0, 0, 0, 0, 0,
            0, 0, 0, 0, 0]
        markers = [0, 0, 0, 0, 0,
            0, 0, 0, 0, 0]
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0, 1.0]

        for i in range(1):
            if len(labels[i]) == 0:
                self.qtgui_const_sink_x_0.set_line_label(i, "Data {0}".format(i))
            else:
                self.qtgui_const_sink_x_0.set_line_label(i, labels[i])
            self.qtgui_const_sink_x_0.set_line_width(i, widths[i])
            self.qtgui_const_sink_x_0.set_line_color(i, colors[i])
            self.qtgui_const_sink_x_0.set_line_style(i, styles[i])
            self.qtgui_const_sink_x_0.set_line_marker(i, markers[i])
            self.qtgui_const_sink_x_0.set_line_alpha(i, alphas[i])

        self._qtgui_const_sink_x_0_win = sip.wrapinstance(self.qtgui_const_sink_x_0.qwidget(), Qt.QWidget)
        self.qtgui_0_grid_layout_0.addWidget(self._qtgui_const_sink_x_0_win, 0, 0, 1, 1)
        for r in range(0, 1):
            self.qtgui_0_grid_layout_0.setRowStretch(r, 1)
        for c in range(0, 1):
            self.qtgui_0_grid_layout_0.setColumnStretch(c, 1)
        self.mer_qam_desrotator_cf_0 = mer.qam_desrotator_cf(256,8100)
        self.mer_probe_all_meassurements_cf_0 = mer.probe_all_meassurements_cf(const_256QAM, 0.005)
        self.dtv_dvbt2_modulator_bc_0 = dtv.dvbt2_modulator_bc(dtv.FECFRAME_NORMAL, dtv.MOD_256QAM, dtv.ROTATION_ON)
        self.channels_impairments_0 = channels.impairments(pj, ai, qe, cs, 0, 0, 0, 0)
        self.channels_channel_model_0 = channels.channel_model(
            noise_voltage=noise,
            frequency_offset=0.0,
            epsilon=1.0,
            taps=[1.0],
            noise_seed=0,
            block_tags=False)
        self.analog_random_source_x_0 = blocks.vector_source_b(list(map(int, numpy.random.randint(0, 256, 100000))), True)


        ##################################################
        # Connections
        ##################################################
        self.connect((self.analog_random_source_x_0, 0), (self.dtv_dvbt2_modulator_bc_0, 0))
        self.connect((self.channels_channel_model_0, 0), (self.mer_qam_desrotator_cf_0, 0))
        self.connect((self.channels_channel_model_0, 0), (self.qtgui_const_sink_x_0_0, 0))
        self.connect((self.channels_impairments_0, 0), (self.channels_channel_model_0, 0))
        self.connect((self.dtv_dvbt2_modulator_bc_0, 0), (self.channels_impairments_0, 0))
        self.connect((self.mer_probe_all_meassurements_cf_0, 0), (self.qtgui_number_sink_0, 0))
        self.connect((self.mer_probe_all_meassurements_cf_0, 1), (self.qtgui_number_sink_0_0, 0))
        self.connect((self.mer_probe_all_meassurements_cf_0, 6), (self.qtgui_number_sink_0_0_0, 0))
        self.connect((self.mer_probe_all_meassurements_cf_0, 8), (self.qtgui_number_sink_0_0_1, 0))
        self.connect((self.mer_probe_all_meassurements_cf_0, 2), (self.qtgui_number_sink_0_1, 0))
        self.connect((self.mer_probe_all_meassurements_cf_0, 3), (self.qtgui_number_sink_0_2, 0))
        self.connect((self.mer_probe_all_meassurements_cf_0, 5), (self.qtgui_number_sink_0_3, 0))
        self.connect((self.mer_probe_all_meassurements_cf_0, 7), (self.qtgui_number_sink_0_4, 0))
        self.connect((self.mer_probe_all_meassurements_cf_0, 4), (self.qtgui_number_sink_1, 0))
        self.connect((self.mer_qam_desrotator_cf_0, 0), (self.mer_probe_all_meassurements_cf_0, 0))
        self.connect((self.mer_qam_desrotator_cf_0, 0), (self.qtgui_const_sink_x_0, 0))
        self.connect((self.mer_qam_desrotator_cf_0, 0), (self.qtgui_freq_sink_x_0, 0))


    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "mer_probe_ai")
        self.settings.setValue("geometry", self.saveGeometry())
        self.stop()
        self.wait()

        event.accept()

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.qtgui_freq_sink_x_0.set_frequency_range(0, self.samp_rate)

    def get_qe(self):
        return self.qe

    def set_qe(self, qe):
        self.qe = qe
        self.channels_impairments_0.set_phasebal(self.qe)

    def get_pj(self):
        return self.pj

    def set_pj(self, pj):
        self.pj = pj
        self.channels_impairments_0.set_phase_noise_mag(self.pj)

    def get_noise(self):
        return self.noise

    def set_noise(self, noise):
        self.noise = noise
        self.channels_channel_model_0.set_noise_voltage(self.noise)

    def get_cs(self):
        return self.cs

    def set_cs(self, cs):
        self.cs = cs
        self.channels_impairments_0.set_q_ofs(self.cs)

    def get_const_256QAM(self):
        return self.const_256QAM

    def set_const_256QAM(self, const_256QAM):
        self.const_256QAM = const_256QAM

    def get_ai(self):
        return self.ai

    def set_ai(self, ai):
        self.ai = ai
        self.channels_impairments_0.set_magbal(self.ai)




def main(top_block_cls=mer_probe_ai, options=None):

    if StrictVersion("4.5.0") <= StrictVersion(Qt.qVersion()) < StrictVersion("5.0.0"):
        style = gr.prefs().get_string('qtgui', 'style', 'raster')
        Qt.QApplication.setGraphicsSystem(style)
    qapp = Qt.QApplication(sys.argv)

    tb = top_block_cls()

    tb.start()

    tb.show()

    def sig_handler(sig=None, frame=None):
        tb.stop()
        tb.wait()

        Qt.QApplication.quit()

    signal.signal(signal.SIGINT, sig_handler)
    signal.signal(signal.SIGTERM, sig_handler)

    timer = Qt.QTimer()
    timer.start(500)
    timer.timeout.connect(lambda: None)

    qapp.exec_()

if __name__ == '__main__':
    main()
