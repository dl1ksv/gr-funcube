/* -*- c++ -*- */
/*
 * Copyright 2020 dl1ksv.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_FUNCUBE_FCD_IMPL_H
#define INCLUDED_FUNCUBE_FCD_IMPL_H

#include <gnuradio/audio/source.h>
#include <gnuradio/logger.h>
#include <gnuradio/prefs.h>
#include <funcube/fcd.h>
#include <funcube/fcd_control.h>
namespace gr {
namespace funcube {

class fcd_impl : public fcd
{
private:
    // Nothing to declare in this block.

public:
    fcd_impl(const std::string device_name = "");
    ~fcd_impl();
    /* Public API functions documented in include/fcdproplus/fcd.h */
    void set_freq(double freq) override;
    void set_lna_gain(float gain) override;
    void set_mixer_gain(float gain) override;
    void set_freq_corr(double ppm) override;
    void set_dc_corr(double _dci, double _dcq) override;
    void set_iq_corr(double _gain, double _phase) override;

private:
    gr::audio::source::sptr fcd_audio;   /*!< The audio input source */
    double d_freq_corr;                     /*!< The frequency correction in ppm */
    double d_freq_req;                      /*!< The latest requested frequency in Hz */
    fcd_control::sptr fcd_control_block; /*!< The fcd control block */
    gr::logger_ptr d_logger;
};

} // namespace funcube
} // namespace gr

#endif /* INCLUDED_FUNCUBE_FCD_IMPL_H */
