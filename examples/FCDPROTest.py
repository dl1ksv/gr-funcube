#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#
# SPDX-License-Identifier: GPL-3.0
#
# GNU Radio Python Flow Graph
# Title: Fcdprotest
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

import os
import sys
sys.path.append(os.environ.get('GRC_HIER_PATH', os.path.expanduser('~/.grc_gnuradio')))

from PyQt5 import Qt
from PyQt5.QtCore import QObject, pyqtSlot
from gnuradio import qtgui
from gnuradio.filter import firdes
import sip
import display
from decodeApt import decodeApt  # grc-generated hier_block
from gnuradio import analog
from gnuradio import blocks
from gnuradio import filter
from gnuradio import gr
import signal
from argparse import ArgumentParser
from gnuradio.eng_arg import eng_float, intx
from gnuradio import eng_notation
from gnuradio.qtgui import Range, RangeWidget
import funcube

from gnuradio import qtgui

class FCDPROTest(gr.top_block, Qt.QWidget):

    def __init__(self):
        gr.top_block.__init__(self, "Fcdprotest", catch_exceptions=True)
        Qt.QWidget.__init__(self)
        self.setWindowTitle("Fcdprotest")
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

        self.settings = Qt.QSettings("GNU Radio", "FCDPROTest")

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
        self.sat = sat = 137100
        self.samp_rate = samp_rate = 192000
        self.StartRecord = StartRecord = 0
        self.RxFrequency = RxFrequency = -8000
        self.Mixergain = Mixergain = 1
        self.Lna = Lna = 1
        self.Ifgain = Ifgain = 15
        self.Force = Force = 0

        ##################################################
        # Blocks
        ##################################################
        self.Rx = Qt.QTabWidget()
        self.Rx_widget_0 = Qt.QWidget()
        self.Rx_layout_0 = Qt.QBoxLayout(Qt.QBoxLayout.TopToBottom, self.Rx_widget_0)
        self.Rx_grid_layout_0 = Qt.QGridLayout()
        self.Rx_layout_0.addLayout(self.Rx_grid_layout_0)
        self.Rx.addTab(self.Rx_widget_0, 'Spectrum and Control')
        self.Rx_widget_1 = Qt.QWidget()
        self.Rx_layout_1 = Qt.QBoxLayout(Qt.QBoxLayout.TopToBottom, self.Rx_widget_1)
        self.Rx_grid_layout_1 = Qt.QGridLayout()
        self.Rx_layout_1.addLayout(self.Rx_grid_layout_1)
        self.Rx.addTab(self.Rx_widget_1, 'Image')
        self.top_grid_layout.addWidget(self.Rx, 1, 0, 5, 6)
        for r in range(1, 6):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(0, 6):
            self.top_grid_layout.setColumnStretch(c, 1)
        # Create the options list
        self._sat_options = (0, 137500, 137912, 137100, )
        # Create the labels list
        self._sat_labels = ('Noaa15', 'Noaa17', 'Noaa18', 'Noaa19', )
        # Create the combo box
        self._sat_tool_bar = Qt.QToolBar(self)
        self._sat_tool_bar.addWidget(Qt.QLabel('sat' + ": "))
        self._sat_combo_box = Qt.QComboBox()
        self._sat_tool_bar.addWidget(self._sat_combo_box)
        for _label in self._sat_labels: self._sat_combo_box.addItem(_label)
        self._sat_callback = lambda i: Qt.QMetaObject.invokeMethod(self._sat_combo_box, "setCurrentIndex", Qt.Q_ARG("int", self._sat_options.index(i)))
        self._sat_callback(self.sat)
        self._sat_combo_box.currentIndexChanged.connect(
            lambda i: self.set_sat(self._sat_options[i]))
        # Create the radio buttons
        self.Rx_grid_layout_0.addWidget(self._sat_tool_bar, 0, 0, 1, 1)
        for r in range(0, 1):
            self.Rx_grid_layout_0.setRowStretch(r, 1)
        for c in range(0, 1):
            self.Rx_grid_layout_0.setColumnStretch(c, 1)
        self._RxFrequency_range = Range(-50000, 0, 1000, -8000, 130)
        self._RxFrequency_win = RangeWidget(self._RxFrequency_range, self.set_RxFrequency, 'Set Frequency Offset', "counter", float)
        self.Rx_grid_layout_0.addWidget(self._RxFrequency_win, 0, 1, 1, 1)
        for r in range(0, 1):
            self.Rx_grid_layout_0.setRowStretch(r, 1)
        for c in range(1, 2):
            self.Rx_grid_layout_0.setColumnStretch(c, 1)
        # Create the options list
        self._Mixergain_options = (0, 1, )
        # Create the labels list
        self._Mixergain_labels = ('Off', 'On', )
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
        self.Rx_grid_layout_0.addWidget(self._Mixergain_tool_bar, 0, 4, 1, 1)
        for r in range(0, 1):
            self.Rx_grid_layout_0.setRowStretch(r, 1)
        for c in range(4, 5):
            self.Rx_grid_layout_0.setColumnStretch(c, 1)
        # Create the options list
        self._Lna_options = (0, 1, )
        # Create the labels list
        self._Lna_labels = ('Off', 'On', )
        # Create the combo box
        self._Lna_tool_bar = Qt.QToolBar(self)
        self._Lna_tool_bar.addWidget(Qt.QLabel('Lna' + ": "))
        self._Lna_combo_box = Qt.QComboBox()
        self._Lna_tool_bar.addWidget(self._Lna_combo_box)
        for _label in self._Lna_labels: self._Lna_combo_box.addItem(_label)
        self._Lna_callback = lambda i: Qt.QMetaObject.invokeMethod(self._Lna_combo_box, "setCurrentIndex", Qt.Q_ARG("int", self._Lna_options.index(i)))
        self._Lna_callback(self.Lna)
        self._Lna_combo_box.currentIndexChanged.connect(
            lambda i: self.set_Lna(self._Lna_options[i]))
        # Create the radio buttons
        self.Rx_grid_layout_0.addWidget(self._Lna_tool_bar, 0, 3, 1, 1)
        for r in range(0, 1):
            self.Rx_grid_layout_0.setRowStretch(r, 1)
        for c in range(3, 4):
            self.Rx_grid_layout_0.setColumnStretch(c, 1)
        self._Ifgain_range = Range(0, 59, 1, 15, 80)
        self._Ifgain_win = RangeWidget(self._Ifgain_range, self.set_Ifgain, 'Ifgain', "counter", int)
        self.Rx_grid_layout_0.addWidget(self._Ifgain_win, 0, 2, 1, 1)
        for r in range(0, 1):
            self.Rx_grid_layout_0.setRowStretch(r, 1)
        for c in range(2, 3):
            self.Rx_grid_layout_0.setColumnStretch(c, 1)
        self.show_image_0 = display.show_image( 2080, 1400  )
        self.show_image_0.displayBottomUp(True)
        self._show_image_0_win = sip.wrapinstance(self.show_image_0.pyqwidget(), Qt.QWidget)
        self.Rx_layout_1.addWidget(self._show_image_0_win)
        self.qtgui_waterfall_sink_x_0 = qtgui.waterfall_sink_c(
            1024, #size
            firdes.WIN_BLACKMAN_hARRIS, #wintype
            (sat-20)*1000, #fc
            samp_rate, #bw
            "", #name
            1 #number of inputs
        )
        self.qtgui_waterfall_sink_x_0.set_update_time(0.10)
        self.qtgui_waterfall_sink_x_0.enable_grid(False)
        self.qtgui_waterfall_sink_x_0.enable_axis_labels(True)



        labels = ['', '', '', '', '',
                  '', '', '', '', '']
        colors = [0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0]
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
                  1.0, 1.0, 1.0, 1.0, 1.0]

        for i in range(1):
            if len(labels[i]) == 0:
                self.qtgui_waterfall_sink_x_0.set_line_label(i, "Data {0}".format(i))
            else:
                self.qtgui_waterfall_sink_x_0.set_line_label(i, labels[i])
            self.qtgui_waterfall_sink_x_0.set_color_map(i, colors[i])
            self.qtgui_waterfall_sink_x_0.set_line_alpha(i, alphas[i])

        self.qtgui_waterfall_sink_x_0.set_intensity_range(-140, 10)

        self._qtgui_waterfall_sink_x_0_win = sip.wrapinstance(self.qtgui_waterfall_sink_x_0.pyqwidget(), Qt.QWidget)
        self.Rx_layout_0.addWidget(self._qtgui_waterfall_sink_x_0_win)
        self.qtgui_time_sink_x_0 = qtgui.time_sink_f(
            2080, #size
            samp_rate/10, #samp_rate
            'QT GUI Plot', #name
            3 #number of inputs
        )
        self.qtgui_time_sink_x_0.set_update_time(0.10)
        self.qtgui_time_sink_x_0.set_y_axis(-2, 2)

        self.qtgui_time_sink_x_0.set_y_label('Amplitude', "")

        self.qtgui_time_sink_x_0.enable_tags(True)
        self.qtgui_time_sink_x_0.set_trigger_mode(qtgui.TRIG_MODE_FREE, qtgui.TRIG_SLOPE_POS, 0.0, 0, 0, "")
        self.qtgui_time_sink_x_0.enable_autoscale(False)
        self.qtgui_time_sink_x_0.enable_grid(True)
        self.qtgui_time_sink_x_0.enable_axis_labels(True)
        self.qtgui_time_sink_x_0.enable_control_panel(False)
        self.qtgui_time_sink_x_0.enable_stem_plot(False)


        labels = ['', '', '', '', '',
            '', '', '', '', '']
        widths = [1, 1, 1, 1, 1,
            1, 1, 1, 1, 1]
        colors = ['blue', 'red', 'green', 'black', 'cyan',
            'magenta', 'yellow', 'dark red', 'dark green', 'dark blue']
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0, 1.0]
        styles = [1, 1, 1, 1, 1,
            1, 1, 1, 1, 1]
        markers = [-1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1]


        for i in range(3):
            if len(labels[i]) == 0:
                self.qtgui_time_sink_x_0.set_line_label(i, "Data {0}".format(i))
            else:
                self.qtgui_time_sink_x_0.set_line_label(i, labels[i])
            self.qtgui_time_sink_x_0.set_line_width(i, widths[i])
            self.qtgui_time_sink_x_0.set_line_color(i, colors[i])
            self.qtgui_time_sink_x_0.set_line_style(i, styles[i])
            self.qtgui_time_sink_x_0.set_line_marker(i, markers[i])
            self.qtgui_time_sink_x_0.set_line_alpha(i, alphas[i])

        self._qtgui_time_sink_x_0_win = sip.wrapinstance(self.qtgui_time_sink_x_0.pyqwidget(), Qt.QWidget)
        self.Rx_layout_0.addWidget(self._qtgui_time_sink_x_0_win)
        self.funcube_fcdpp_0 = funcube.fcdpp( "", 1000)

        self.funcube_fcdpp_0.set_lna(Lna)
        self.funcube_fcdpp_0.set_mixer_gain(Mixergain)
        self.funcube_fcdpp_0.set_if_gain(Ifgain)
        self.funcube_fcdpp_0.set_freq_corr(0)
        self.funcube_fcdpp_0.set_freq(sat-20)
        self.fir_filter_xxx_0_2 = filter.fir_filter_fff(1, (-14,-14,-14,-14,-14,-14,-14,-14,18,18,-14,-14,18,18,-14,-14,18,18,-14,-14,18,18,-14,-14,18,18,-14,-14,18,18,-14,-14,18,18,-14,-14,-14))
        self.fir_filter_xxx_0_2.declare_sample_delay(0)
        self.decodeApt_0 = decodeApt(
            gain=128,
            samp_rate_in=samp_rate,
        )
        self.blocks_threshold_ff_1_0 = blocks.threshold_ff(-1, 0.9, 0)
        self.blocks_multiply_xx_0 = blocks.multiply_vcc(1)
        self.blocks_multiply_const_vxx_0 = blocks.multiply_const_ff(1)
        self.blocks_float_to_char_0 = blocks.float_to_char(1, 1)
        self.blocks_delay_0 = blocks.delay(gr.sizeof_char*1, 30)
        self.blocks_add_const_vxx_0 = blocks.add_const_ff(40)
        self.analog_sig_source_x_0 = analog.sig_source_c(samp_rate, analog.GR_COS_WAVE, RxFrequency, 1, 0, 0)
        # Create the options list
        self._StartRecord_options = (0, 1, )
        # Create the labels list
        self._StartRecord_labels = ('Stop', 'Start', )
        # Create the combo box
        self._StartRecord_tool_bar = Qt.QToolBar(self)
        self._StartRecord_tool_bar.addWidget(Qt.QLabel('Start Recording' + ": "))
        self._StartRecord_combo_box = Qt.QComboBox()
        self._StartRecord_tool_bar.addWidget(self._StartRecord_combo_box)
        for _label in self._StartRecord_labels: self._StartRecord_combo_box.addItem(_label)
        self._StartRecord_callback = lambda i: Qt.QMetaObject.invokeMethod(self._StartRecord_combo_box, "setCurrentIndex", Qt.Q_ARG("int", self._StartRecord_options.index(i)))
        self._StartRecord_callback(self.StartRecord)
        self._StartRecord_combo_box.currentIndexChanged.connect(
            lambda i: self.set_StartRecord(self._StartRecord_options[i]))
        # Create the radio buttons
        self.top_grid_layout.addWidget(self._StartRecord_tool_bar, 0, 0, 1, 1)
        for r in range(0, 1):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(0, 1):
            self.top_grid_layout.setColumnStretch(c, 1)
        # Create the options list
        self._Force_options = (0, 1, )
        # Create the labels list
        self._Force_labels = ('Automatic start', 'Force start', )
        # Create the combo box
        # Create the radio buttons
        self._Force_group_box = Qt.QGroupBox('Force Display' + ": ")
        self._Force_box = Qt.QVBoxLayout()
        class variable_chooser_button_group(Qt.QButtonGroup):
            def __init__(self, parent=None):
                Qt.QButtonGroup.__init__(self, parent)
            @pyqtSlot(int)
            def updateButtonChecked(self, button_id):
                self.button(button_id).setChecked(True)
        self._Force_button_group = variable_chooser_button_group()
        self._Force_group_box.setLayout(self._Force_box)
        for i, _label in enumerate(self._Force_labels):
            radio_button = Qt.QRadioButton(_label)
            self._Force_box.addWidget(radio_button)
            self._Force_button_group.addButton(radio_button, i)
        self._Force_callback = lambda i: Qt.QMetaObject.invokeMethod(self._Force_button_group, "updateButtonChecked", Qt.Q_ARG("int", self._Force_options.index(i)))
        self._Force_callback(self.Force)
        self._Force_button_group.buttonClicked[int].connect(
            lambda i: self.set_Force(self._Force_options[i]))
        self.top_grid_layout.addWidget(self._Force_group_box, 0, 1, 1, 1)
        for r in range(0, 1):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(1, 2):
            self.top_grid_layout.setColumnStretch(c, 1)



        ##################################################
        # Connections
        ##################################################
        self.connect((self.analog_sig_source_x_0, 0), (self.blocks_multiply_xx_0, 1))
        self.connect((self.blocks_add_const_vxx_0, 0), (self.blocks_threshold_ff_1_0, 0))
        self.connect((self.blocks_delay_0, 0), (self.show_image_0, 0))
        self.connect((self.blocks_float_to_char_0, 0), (self.show_image_0, 1))
        self.connect((self.blocks_multiply_const_vxx_0, 0), (self.qtgui_time_sink_x_0, 0))
        self.connect((self.blocks_multiply_xx_0, 0), (self.decodeApt_0, 0))
        self.connect((self.blocks_multiply_xx_0, 0), (self.qtgui_waterfall_sink_x_0, 0))
        self.connect((self.blocks_threshold_ff_1_0, 0), (self.blocks_float_to_char_0, 0))
        self.connect((self.blocks_threshold_ff_1_0, 0), (self.qtgui_time_sink_x_0, 1))
        self.connect((self.decodeApt_0, 0), (self.blocks_delay_0, 0))
        self.connect((self.decodeApt_0, 1), (self.fir_filter_xxx_0_2, 0))
        self.connect((self.decodeApt_0, 1), (self.qtgui_time_sink_x_0, 2))
        self.connect((self.fir_filter_xxx_0_2, 0), (self.blocks_add_const_vxx_0, 0))
        self.connect((self.fir_filter_xxx_0_2, 0), (self.blocks_multiply_const_vxx_0, 0))
        self.connect((self.funcube_fcdpp_0, 0), (self.blocks_multiply_xx_0, 0))


    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "FCDPROTest")
        self.settings.setValue("geometry", self.saveGeometry())
        event.accept()

    def setStyleSheetFromFile(self, filename):
        try:
            if not os.path.exists(filename):
                filename = os.path.join(
                    gr.prefix(), "share", "gnuradio", "themes", filename)
            with open(filename) as ss:
                self.setStyleSheet(ss.read())
        except Exception as e:
            print(e, file=sys.stderr)

    def get_sat(self):
        return self.sat

    def set_sat(self, sat):
        self.sat = sat
        self._sat_callback(self.sat)
        self.funcube_fcdpp_0.set_freq(self.sat-20)
        self.qtgui_waterfall_sink_x_0.set_frequency_range((self.sat-20)*1000, self.samp_rate)

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.analog_sig_source_x_0.set_sampling_freq(self.samp_rate)
        self.decodeApt_0.set_samp_rate_in(self.samp_rate)
        self.qtgui_time_sink_x_0.set_samp_rate(self.samp_rate/10)
        self.qtgui_waterfall_sink_x_0.set_frequency_range((self.sat-20)*1000, self.samp_rate)

    def get_StartRecord(self):
        return self.StartRecord

    def set_StartRecord(self, StartRecord):
        self.StartRecord = StartRecord
        self._StartRecord_callback(self.StartRecord)

    def get_RxFrequency(self):
        return self.RxFrequency

    def set_RxFrequency(self, RxFrequency):
        self.RxFrequency = RxFrequency
        self.analog_sig_source_x_0.set_frequency(self.RxFrequency)

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

    def get_Force(self):
        return self.Force

    def set_Force(self, Force):
        self.Force = Force
        self._Force_callback(self.Force)





def main(top_block_cls=FCDPROTest, options=None):

    if StrictVersion("4.5.0") <= StrictVersion(Qt.qVersion()) < StrictVersion("5.0.0"):
        style = gr.prefs().get_string('qtgui', 'style', 'raster')
        Qt.QApplication.setGraphicsSystem(style)
    qapp = Qt.QApplication(sys.argv)

    tb = top_block_cls()

    tb.start()

    tb.setStyleSheetFromFile("/home/schroer/gnuradiocomponents/gnuradio/gr-qtgui/themes/plain.qss")
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
