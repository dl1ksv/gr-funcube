/* -*- c++ -*- */
/*
 * Copyright 2020 dl1ksv.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_FUNCUBE_FCD_CONTROL_IMPL_H
#define INCLUDED_FUNCUBE_FCD_CONTROL_IMPL_H

#include <funcube/fcd_control.h>

#include "hidapi/hidapi.h"

namespace gr {
namespace funcube {

class fcd_control_impl : public fcd_control
{
public:
    fcd_control_impl();
    ~fcd_control_impl();

    /* Public API functions documented in include/funcube/fcd_control.h */
    void set_freq(float freq);
    void set_lna_gain(float gain);
    void set_mixer_gain(float gain);
    void set_freq_corr(int ppm);
    void set_dc_corr(double _dci, double _dcq);
    void set_iq_corr(double _gain, double _phase);
    void set_frequency_msg(pmt::pmt_t msg);

private:
    int d_freq_corr;              /*!< The frequency correction in ppm */
    hid_device* d_control_handle; /*!< handle to control the device, set frequency, etc */
    unsigned char aucBuf[65]; /*!< Buffers to read/write control messages to the dongle */
};

} // namespace funcube
} // namespace gr

#endif /* INCLUDED_FUNCUBE_FCD_CONTROL_IMPL_H */
