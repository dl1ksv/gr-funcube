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

#include "fcdpp_impl.h"

#include <exception>
#include <fstream>
#include <iostream>
namespace gr {
namespace funcube {

fcdpp::sptr fcdpp::make(const std::string device_name, int unit)
{
    return gnuradio::get_initial_sptr(new fcdpp_impl(device_name, unit));
}

/*
 * The private constructor
 */
fcdpp_impl::fcdpp_impl(const std::string user_device_name, int unit)
    : gr::hier_block2("fcdpp",
                      gr::io_signature::make(0, 0, 0),
                      gr::io_signature::make(1, 1, sizeof(gr_complex)))
{

    bool found=gr::configure_default_loggers(this->d_logger, this->d_debug_logger, "Funcube Pro+");
    if( !found)
        throw std::runtime_error("logger not found.");

    std::string device_name;
    bool success;
    gr::blocks::float_to_complex::sptr f2c;

    success = false;
    d_freq_req = 0;
    d_corr = 0;
    d_unit = unit;

    this->d_logger->info("Start init fcdpp");
    if (!user_device_name.empty()) {
        try {
            /* Audio source; sample rate fixed at 192kHz */
            fcd = gr::audio::source::make(192000, user_device_name, true);
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

                if (line.find("USB-Audio - FUNcube Dongle V2.0") != std::string::npos) {
                    int id;
                    std::istringstream(line) >> id;

                    std::ostringstream hw_id;
                    hw_id << "hw:" << id << ",0"; // build alsa identifier
                    device_name = hw_id.str();
                }
            }
            cards.close();
            if (device_name.empty()) {
                throw std::runtime_error("No FunCube Dongle  V2.0 found.");
            }
        } else {
            throw std::runtime_error("Alsa not found.");
        }
        /* Audio source; sample rate fixed at 192kHz */
        fcd = gr::audio::source::make(192000, device_name, true);
    }
    if (success) {
        this->d_logger->info("Audio device {:s} opened", device_name);
    } else {
        this->d_logger->info("Funcube Dongle Pro+ found as: {:s}",device_name);
    }

    /* block to convert stereo audio to a complex stream */
    f2c = gr::blocks::float_to_complex::make(1);

    connect(fcd, 0, f2c, 0);
    connect(fcd, 1, f2c, 1);
    connect(f2c, 0, self(), 0);

    fcd_control_block = fcdpp_control::make();

    message_port_register_hier_in(pmt::mp("freq"));
    msg_connect(self(), pmt::mp("freq"), fcd_control_block, pmt::mp("freq"));
}

/*
 * Our virtual destructor.
 */
fcdpp_impl::~fcdpp_impl() {}

void fcdpp_impl::set_freq(float freq)
{
    float setfreq;
    if (d_freq_req == (unsigned int)freq)
        return; // Frequency did not change
    d_freq_req = (int)freq;
    if (d_corr == 0) {
        setfreq = freq * d_unit;
    } else {
        setfreq = ((float)d_unit + ((float)d_corr) / (1000000. / d_unit)) * freq;
    }
    fcd_control_block->set_freq(setfreq);
}

void fcdpp_impl::set_lna(int gain) { fcd_control_block->set_lna(gain); }

void fcdpp_impl::set_mixer_gain(int gain) { fcd_control_block->set_mixer_gain(gain); }

void fcdpp_impl::set_freq_corr(int ppm)
{
    float freq;
    if (d_corr == ppm)
        return;
    d_corr = ppm;
    this->d_logger->info("Set frequency correction to: {:i} ppm ", ppm);
    freq = d_freq_req;
    d_freq_req = 0;
    set_freq(freq);
}

void fcdpp_impl::set_if_gain(int gain)
{
    if ((gain < 0) || gain > 59) {
        this->d_logger->warn("Invalid If gain value: {:i}", gain);
        return;
    }
    fcd_control_block->set_if_gain(gain);
}

} /* namespace funcube */
} /* namespace gr */
