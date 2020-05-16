#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#
# SPDX-License-Identifier: GPL-3.0
#
# GNU Radio Python Flow Graph
# Title: FM radio to test FCDPROplus
# Author: dl1ksv
# GNU Radio version: 3.9.0.0-git

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
from PyQt5.QtCore import QObject, pyqtSlot
from gnuradio import qtgui
from gnuradio.filter import firdes
import sip
from gnuradio import analog
from gnuradio import audio
from gnuradio import filter
from gnuradio import gr
import sys
import signal
from argparse import ArgumentParser
from gnuradio.eng_arg import eng_float, intx
from gnuradio import eng_notation
from gnuradio.qtgui import Range, RangeWidget
import funcube

from gnuradio import qtgui

class FMRadio(gr.top_block, Qt.QWidget):

    def __init__(self):
        gr.top_block.__init__(self, "FM radio to test FCDPROplus", catch_exceptions=True)
        Qt.QWidget.__init__(self)
        self.setWindowTitle("FM radio to test FCDPROplus")
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

        self.settings = Qt.QSettings("GNU Radio", "FMRadio")

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
        self.samp_rate = samp_rate = 192000
        self.RxFrequency = RxFrequency = 94300
        self.Mixergain = Mixergain = 1
        self.Lna = Lna = 1
        self.Ifgain = Ifgain = 10

        ##################################################
        # Blocks
        ##################################################
        self._RxFrequency_range = Range(80000, 146000, 1, 94300, 200)
        self._RxFrequency_win = RangeWidget(self._RxFrequency_range, self.set_RxFrequency, 'Set Frequency ', "counter", float)
        self.top_grid_layout.addWidget(self._RxFrequency_win, 0, 0, 1, 1)
        for r in range(0, 1):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(0, 1):
            self.top_grid_layout.setColumnStretch(c, 1)
        # Create the options list
        self._Mixergain_options = (1, 0, )
        # Create the labels list
        self._Mixergain_labels = ('On', 'Off', )
        # Create the combo box
        self._Mixergain_tool_bar = Qt.QToolBar(self)
        self._Mixergain_tool_bar.addWidget(Qt.QLabel('Mixergain' + ": "))
        self._Mixergain_combo_box = Qt.QComboBox()
        self._Mixergain_tool_bar.addWidget(self._Mixergain_combo_box)
        for _label in self._Mixergain_labels: self._Mixergain_combo_box.addItem(_label)
        self._Mixergain_callback = lambda i: Qt.QMetaObject.invokeMethod(self._Mixergain_combo_box, "setCurrentIndex", Qt.Q_ARG("int", self._Mixergain_options.index(i)))
        self._Mixergain_callback(self.Mixergain)
        self._Mixergain_combo_box.currentIndexChanged.connect(
            lambda i: self.set_Mixergain(self._Mixergain_options[i]))
        # Create the radio buttons
        self.top_grid_layout.addWidget(self._Mixergain_tool_bar, 0, 2, 1, 1)
        for r in range(0, 1):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(2, 3):
            self.top_grid_layout.setColumnStretch(c, 1)
        # Create the options list
        self._Lna_options = (1, 0, )
        # Create the labels list
        self._Lna_labels = ('On', 'Off', )
        # Create the combo box
        self._Lna_tool_bar = Qt.QToolBar(self)
        self._Lna_tool_bar.addWidget(Qt.QLabel('LNA Enable/Disable' + ": "))
        self._Lna_combo_box = Qt.QComboBox()
        self._Lna_tool_bar.addWidget(self._Lna_combo_box)
        for _label in self._Lna_labels: self._Lna_combo_box.addItem(_label)
        self._Lna_callback = lambda i: Qt.QMetaObject.invokeMethod(self._Lna_combo_box, "setCurrentIndex", Qt.Q_ARG("int", self._Lna_options.index(i)))
        self._Lna_callback(self.Lna)
        self._Lna_combo_box.currentIndexChanged.connect(
            lambda i: self.set_Lna(self._Lna_options[i]))
        # Create the radio buttons
        self.top_grid_layout.addWidget(self._Lna_tool_bar, 0, 1, 1, 1)
        for r in range(0, 1):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(1, 2):
            self.top_grid_layout.setColumnStretch(c, 1)
        self._Ifgain_range = Range(0, 59, 1, 10, 45)
        self._Ifgain_win = RangeWidget(self._Ifgain_range, self.set_Ifgain, 'IFGain', "counter", int)
        self.top_grid_layout.addWidget(self._Ifgain_win, 0, 3, 1, 1)
        for r in range(0, 1):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(3, 4):
            self.top_grid_layout.setColumnStretch(c, 1)
        self.qtgui_sink_x_0 = qtgui.sink_c(
            1024, #fftsize
            firdes.WIN_BLACKMAN_hARRIS, #wintype
            RxFrequency*1000, #fc
            samp_rate, #bw
            'QT GUI Plot', #name
            True, #plotfreq
            True, #plotwaterfall
            False, #plottime
            False #plotconst
        )
        self.qtgui_sink_x_0.set_update_time(1.0/10)
        self._qtgui_sink_x_0_win = sip.wrapinstance(self.qtgui_sink_x_0.pyqwidget(), Qt.QWidget)

        self.qtgui_sink_x_0.enable_rf_freq(True)

        self.top_grid_layout.addWidget(self._qtgui_sink_x_0_win, 1, 0, 1, 7)
        for r in range(1, 2):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(0, 7):
            self.top_grid_layout.setColumnStretch(c, 1)
        self.low_pass_filter_0 = filter.fir_filter_ccf(
            1,
            firdes.low_pass(
                5,
                samp_rate,
                60000,
                500,
                firdes.WIN_HAMMING,
                6.76))
        self.funcube_fcdpp_0 = funcube.fcdpp( "", 1000)

        self.funcube_fcdpp_0.set_lna(Lna)
        self.funcube_fcdpp_0.set_mixer_gain(Mixergain)
        self.funcube_fcdpp_0.set_if_gain(Ifgain)
        self.funcube_fcdpp_0.set_freq_corr(0)
        self.funcube_fcdpp_0.set_freq(RxFrequency)
        self.audio_sink_0 = audio.sink(48000, 'default', True)
        self.analog_fm_demod_cf_0 = analog.fm_demod_cf(
        	channel_rate=samp_rate,
        	audio_decim=4,
        	deviation=75000,
        	audio_pass=15000,
        	audio_stop=16000,
        	gain=1.0,
        	tau=75e-6,
        )
        self.analog_fm_deemph_0 = analog.fm_deemph(fs=48000, tau=75e-6)



        ##################################################
        # Connections
        ##################################################
        self.msg_connect((self.qtgui_sink_x_0, 'freq'), (self.funcube_fcdpp_0, 'freq'))
        self.msg_connect((self.qtgui_sink_x_0, 'freq'), (self.qtgui_sink_x_0, 'freq'))
        self.connect((self.analog_fm_deemph_0, 0), (self.audio_sink_0, 1))
        self.connect((self.analog_fm_deemph_0, 0), (self.audio_sink_0, 0))
        self.connect((self.analog_fm_demod_cf_0, 0), (self.analog_fm_deemph_0, 0))
        self.connect((self.funcube_fcdpp_0, 0), (self.low_pass_filter_0, 0))
        self.connect((self.funcube_fcdpp_0, 0), (self.qtgui_sink_x_0, 0))
        self.connect((self.low_pass_filter_0, 0), (self.analog_fm_demod_cf_0, 0))


    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "FMRadio")
        self.settings.setValue("geometry", self.saveGeometry())
        event.accept()

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.low_pass_filter_0.set_taps(firdes.low_pass(5, self.samp_rate, 60000, 500, firdes.WIN_HAMMING, 6.76))
        self.qtgui_sink_x_0.set_frequency_range(self.RxFrequency*1000, self.samp_rate)

    def get_RxFrequency(self):
        return self.RxFrequency

    def set_RxFrequency(self, RxFrequency):
        self.RxFrequency = RxFrequency
        self.funcube_fcdpp_0.set_freq(self.RxFrequency)
        self.qtgui_sink_x_0.set_frequency_range(self.RxFrequency*1000, self.samp_rate)

    def get_Mixergain(self):
        return self.Mixergain

    def set_Mixergain(self, Mixergain):
        self.Mixergain = Mixergain
        self._Mixergain_callback(self.Mixergain)
        self.funcube_fcdpp_0.set_mixer_gain(self.Mixergain)

    def get_Lna(self):
        return self.Lna

    def set_Lna(self, Lna):
        self.Lna = Lna
        self._Lna_callback(self.Lna)
        self.funcube_fcdpp_0.set_lna(self.Lna)

    def get_Ifgain(self):
        return self.Ifgain

    def set_Ifgain(self, Ifgain):
        self.Ifgain = Ifgain
        self.funcube_fcdpp_0.set_if_gain(self.Ifgain)





def main(top_block_cls=FMRadio, options=None):

    if StrictVersion("4.5.0") <= StrictVersion(Qt.qVersion()) < StrictVersion("5.0.0"):
        style = gr.prefs().get_string('qtgui', 'style', 'raster')
        Qt.QApplication.setGraphicsSystem(style)
    qapp = Qt.QApplication(sys.argv)

    tb = top_block_cls()

    tb.start()

    tb.show()

    def sig_handler(sig=None, frame=None):
        Qt.QApplication.quit()

    signal.signal(signal.SIGINT, sig_handler)
    signal.signal(signal.SIGTERM, sig_handler)

    timer = Qt.QTimer()
    timer.start(500)
    timer.timeout.connect(lambda: None)

    def quitting():
        tb.stop()
        tb.wait()

    qapp.aboutToQuit.connect(quitting)
    qapp.exec_()

if __name__ == '__main__':
    main()
