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

#include "hidapi/hidapi.h"
#include <gnuradio/funcube/fcdpp_control.h>

namespace gr {
namespace funcube {

class fcdpp_control_cpu : public virtual fcdpp_control
{
public:
    fcdpp_control_cpu(block_args args);
    work_return_t work(work_io& wio) override;
    //    void handle_msg_freq(pmtf::pmt msg) override;

    void set_freq(double freq);
    void set_lna(int gain);
    void set_mixer_gain(int gain);
    void set_if_gain(int gain);

private:
    // private variables here
    hid_device* d_control_handle; /*!< handle to control the device, set frequency, etc */
    unsigned char aucBuf[65]; /*!< Buffers to read/write control messages to the dongle */
};

} // namespace funcube
} // namespace gr
