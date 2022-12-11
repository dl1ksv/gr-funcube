/* -*- c++ -*- */
/*
 * Copyright 2022 [Volker Schroer, dl1ksv]
 *
 * This file is part of GNU Radio
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include "fcdpp_cpu.h"
#include "fcdpp_cpu_gen.h"

#include <exception>
#include <fstream>
#include <iostream>

namespace gr {
namespace funcube {

fcdpp_cpu::fcdpp_cpu(block_args args)
    : INHERITED_CONSTRUCTORS, d_device_name(args.device_name), d_unit(args.unit)
{
    bool success;
    gr::blocks::float_to_complex::sptr f2c;
    gr::blocks::float_to_complex::block_args f2c_args;

    success = false;
    d_freq_req = 0;
    d_freq_corr = 0;
    fcd_settings.num_outputs = 2;
    fcd_settings.sampling_rate = 192000;
    this->d_logger->info("Start init fcdpp");

    if (!d_device_name.empty()) {
        try {
            /* Audio source; sample rate fixed at 192kHz */
            fcd_settings.device_name = d_device_name;
            fcd = gr::audio::alsa_source::make(fcd_settings);
            success = true;
        } catch (std::exception const&) {
            this->d_logger->info("Could not open device: {:s}", d_device_name);
            success = false;
        }
    }
    if (!success) {
        d_device_name.clear();
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
                    d_device_name = hw_id.str();
                }
            }
            cards.close();
            if (d_device_name.empty()) {
                throw std::runtime_error("No FunCube Dongle  V2.0 found.");
            }
        } else {
            throw std::runtime_error("Alsa not found.");
        }
        /* Audio source; sample rate fixed at 192kHz */
        fcd_settings.device_name = d_device_name;
        fcd = gr::audio::alsa_source::make(fcd_settings);
    }
    if (success) {
        this->d_logger->info("Audio device {:s} opened", d_device_name);
    } else {
        this->d_logger->info("Funcube Dongle Pro+ found as: {:s}", d_device_name);
    }

    /* block to convert stereo audio to a complex stream */
    f2c = gr::blocks::float_to_complex::make(f2c_args);

    connect(fcd, 0, f2c, 0);
    connect(fcd, 1, f2c, 1);
    connect(f2c, 0, self(), 0);
    set_freq_corr(args.ppm);
    d_fcd_control_block_settings.lnaswitch = args.lnaswitch;
    d_fcd_control_block_settings.mixergainswitch = args.mixergainswitch;
    d_fcd_control_block_settings.if_gain = args.if_gain;
    //    d_fcd_control_block_settings.freq = args.freq;
    d_fcd_control_block = fcdpp_control::make(d_fcd_control_block_settings);
    set_freq(args.freq);
}

work_return_t fcdpp_cpu::work(work_io& wio)
{
    // Do <+signal processing+>
    // Block specific code goes here
    return work_return_t::OK;
}
void fcdpp_cpu::set_freq(double freq)
{
    double setfreq;
    if (d_freq_req == freq)
        return; // Frequency did not change
    d_freq_req = freq;
    if (d_freq_corr == 0.) {
        setfreq = freq * d_unit;
    } else {
        setfreq = (d_unit + d_freq_corr * d_unit / 1000000.) * freq;
    }
    d_fcd_control_block->set_freq(setfreq);
}
void fcdpp_cpu::set_lna(int gain) { d_fcd_control_block->set_lna(gain); }
void fcdpp_cpu::set_mixer_gain(int gain) { d_fcd_control_block->set_mixer_gain(gain); }
void fcdpp_cpu::set_freq_corr(double ppm)
{
    if (d_freq_corr == ppm)
        return;
    d_freq_corr = ppm;
    this->d_logger->info("Set frequency correction to: {} ppm ", ppm);
    //    double freq = d_freq_req;
    //    d_freq_req = 0;
    //    set_freq(freq);
}
void fcdpp_cpu::set_if_gain(int gain)
{
    if ((gain < 0) || gain > 59) {
        this->d_logger->warn("Invalid If gain value: {:d}", gain);
        return;
    }
    d_fcd_control_block->set_if_gain(gain);
}

} // namespace funcube
} // namespace gr
