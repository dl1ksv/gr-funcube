/* -*- c++ -*- */
/*
 * Copyright 2022 [Volker Schroer, dl1ksv]
 *
 * This file is part of GNU Radio
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#pragma once

#include <gnuradio/audio/alsa_source.h>
#include <gnuradio/blocks/float_to_complex.h>
#include <gnuradio/funcube/fcdpp.h>
#include <gnuradio/funcube/fcdpp_control.h>

namespace gr {
namespace funcube {

class fcdpp_cpu : public virtual fcdpp
{
public:
    fcdpp_cpu(fcdpp::block_args args);
    work_return_t work(work_io& wio) override;

    void set_freq(double freq);
    void set_lna(int gain);
    void set_mixer_gain(int gain);
    void set_freq_corr(double ppm);
    void set_if_gain(int gain);

private:
    // private variables here

    std::string d_device_name;
    int d_unit;
    double d_freq_req; /*!< The latest requested frequency in Hz */
    double d_freq_corr;

    fcdpp_control::block_args d_fcd_control_block_settings;
    fcdpp_control::sptr d_fcd_control_block;
    audio::alsa_source::sptr fcd;
    audio::alsa_source::block_args fcd_settings;
};

} // namespace funcube
} // namespace gr
