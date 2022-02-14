/* -*- c++ -*- */
/*
 * Copyright 2020 dl1ksv.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_FUNCUBE_FCDPP_IMPL_H
#define INCLUDED_FUNCUBE_FCDPP_IMPL_H

#include <gnuradio/audio/source.h>
#include <gnuradio/logger.h>
#include <gnuradio/prefs.h>
#include <funcube/fcdpp.h>
#include <funcube/fcdpp_control.h>


namespace gr {
namespace funcube {

class fcdpp_impl : public fcdpp
{
private:
    gr::audio::source::sptr fcd;           /*!< The audio input source */
    fcdpp_control::sptr fcd_control_block; /*!< The fcd control block */
    double d_freq_req;               /*!< The latest requested frequency in Hz */
    double d_freq_corr;
    int d_unit;
    gr::logger_ptr d_logger;

public:
    fcdpp_impl(const std::string device_name, int unit);
    ~fcdpp_impl();
    /* Public API functions documented in include/funcube/fcdproplus.h */
    void set_freq(double freq) override;
    void set_lna(int gain) override;
    void set_mixer_gain(int gain) override;
    void set_freq_corr(double ppm) override;
    void set_if_gain(int gain) override;
};

} // namespace funcube
} // namespace gr

#endif /* INCLUDED_FUNCUBE_FCDPP_IMPL_H */
