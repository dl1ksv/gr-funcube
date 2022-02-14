/* -*- c++ -*- */
/*
 * Copyright 2020 dl1ksv.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/blocks/float_to_complex.h>
#include <gnuradio/io_signature.h>

#include "fcd_impl.h"

#include <exception>
#include <fstream>
#include <iostream>
namespace gr {
namespace funcube {

fcd::sptr fcd::make(const std::string device_name)
{
    return gnuradio::get_initial_sptr(new fcd_impl(device_name));
}

/*
 * The private constructor
 */
fcd_impl::fcd_impl(const std::string user_device_name)
    : gr::hier_block2("fcd",
                      gr::io_signature::make(0, 0, 0),
                      gr::io_signature::make(1, 1, sizeof(gr_complex))),
      d_freq_corr(-120.)
{

    bool found=gr::configure_default_loggers(this->d_logger, this->d_debug_logger, "Funcube Pro");
    if( !found)
        throw std::runtime_error("logger not found.");

    std::string device_name;
    bool success;
    gr::blocks::float_to_complex::sptr f2c;

    success = false;
    d_freq_req = 0;

    this->d_logger->info("Start init fcd");
    if (!user_device_name.empty()) {
        try {
            /* Audio source; sample rate fixed at 96kHz */
            fcd_audio = gr::audio::source::make(96000, user_device_name, true);
            success = true;
        } catch (std::exception const&) {
            this->d_logger->info("Could not open device: {:s}",user_device_name);
            success = false;
        }
    }
    if (success) {
        device_name = user_device_name;
    } else {

        device_name.clear();
        std::string line;
        std::ifstream cards("/proc/asound/cards");
        if (cards.is_open()) {
            while (cards.good()) {
                getline(cards, line);

                if (line.find("USB-Audio - FUNcube Dongle V1.0") != std::string::npos) {
                    int id;
                    std::istringstream(line) >> id;

                    std::ostringstream hw_id;
                    hw_id << "hw:" << id << ",0"; // build alsa identifier
                    device_name = hw_id.str();
                }
            }
            cards.close();
            if (device_name.empty()) {
                throw std::runtime_error("No FunCube Dongle  V1.0 found.");
            }
        } else {
            throw std::runtime_error("Alsa not found.");
        }
        /* Audio source; sample rate fixed at 96kHz */
        fcd_audio = gr::audio::source::make(96000, device_name, true);
    }
    if (success) {
        this->d_logger->info("Audio device {:s} opened", device_name);
    } else {
        this->d_logger->info("Funcube Dongle found as: {:s}", device_name);
    }

    /* block to convert stereo audio to a complex stream */
    f2c = gr::blocks::float_to_complex::make(1);

    connect(fcd_audio, 0, f2c, 0);
    connect(fcd_audio, 1, f2c, 1);
    connect(f2c, 0, self(), 0);

    fcd_control_block = fcd_control::make();

    message_port_register_hier_in(pmt::mp("freq"));
    msg_connect(self(), pmt::mp("freq"), fcd_control_block, pmt::mp("freq"));
}

/*
 * Our virtual destructor.
 */
fcd_impl::~fcd_impl() {}

// Set frequency with Hz resolution (type float)
void fcd_impl::set_freq(double freq)
{
    double setfreq;
    if (d_freq_req == freq)
        return; // Frequency did not change
    d_freq_req = freq;
    if (d_freq_corr != 0.)
        setfreq = (1. + d_freq_corr / 1000000.) * freq;
    else
        setfreq = freq;
    fcd_control_block->set_freq(setfreq);
}

// Set LNA gain
void fcd_impl::set_lna_gain(float gain) { fcd_control_block->set_lna_gain(gain); }

// Set mixer gain
void fcd_impl::set_mixer_gain(float gain) { fcd_control_block->set_mixer_gain(gain); }

// Set new frequency correction
void fcd_impl::set_freq_corr(double ppm)
{
    double freq;
    if (d_freq_corr == ppm)
        return;
    d_freq_corr = ppm;
    // re-tune with new correction value
    this->d_logger->info("Set frequency correction to: {} ppm ", ppm);
    freq = d_freq_req;
    d_freq_req = 0;
    set_freq(freq);
}

// Set DC offset correction.
void fcd_impl::set_dc_corr(double _dci, double _dcq)
{
    fcd_control_block->set_dc_corr(_dci, _dcq);
}

// Set IQ phase and gain balance.
void fcd_impl::set_iq_corr(double _gain, double _phase)
{
    fcd_control_block->set_iq_corr(_gain, _phase);
}

} /* namespace funcube */
} /* namespace gr */
