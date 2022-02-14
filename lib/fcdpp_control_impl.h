/* -*- c++ -*- */
/*
 * Copyright 2020 dl1ksv.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_FUNCUBE_FCDPP_CONTROL_IMPL_H
#define INCLUDED_FUNCUBE_FCDPP_CONTROL_IMPL_H

#include "hidapi/hidapi.h"
#include <funcube/fcdpp_control.h>

namespace gr {
namespace funcube {

class fcdpp_control_impl : public fcdpp_control
{
private:
    hid_device* d_control_handle; /*!< handle to control the device, set frequency, etc */
    unsigned char aucBuf[65]; /*!< Buffers to read/write control messages to the dongle */

public:
    fcdpp_control_impl();
    ~fcdpp_control_impl();

    /* Public API functions documented in include/funcube/fcdpp_control.h */
    void set_freq(double freq) override;
    void set_lna(int gain) override;
    void set_mixer_gain(int gain) override;
    void set_if_gain(int gain);
    void set_frequency_msg(pmt::pmt_t msg);
};

} // namespace funcube
} // namespace gr

#endif /* INCLUDED_FUNCUBE_FCDPP_CONTROL_IMPL_H */
