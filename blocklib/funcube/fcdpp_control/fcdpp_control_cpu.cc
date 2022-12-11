/* -*- c++ -*- */
/*
 * Copyright 2022 [Volker Schroer, dl1ksv]
 *
 * This file is part of GNU Radio
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include "fcdpp_control_cpu.h"
#include "fcdpp_control_cpu_gen.h"
#include "pmtf/wrap.hpp"

#include "fcdcmd.h"


#define FCDPROPLUS_VENDOR_ID 0x04d8
#define FCDPROPLUS_PRODUCT_ID 0xfb31

#define TIMEOUT 5000

namespace gr {
namespace funcube {

fcdpp_control_cpu::fcdpp_control_cpu(block_args args) : INHERITED_CONSTRUCTORS
{
    /* setup the control part */
    d_control_handle = NULL;
    hid_init();
    d_control_handle = hid_open(FCDPROPLUS_VENDOR_ID, FCDPROPLUS_PRODUCT_ID, NULL);
    if (d_control_handle == NULL) {
        d_logger->error("FunCube Dongle  V2.0 not found.");
        throw std::runtime_error("FunCube Dongle  V2.0 not found.");
    } else {
        d_logger->info("FunCube Dongle  V2.0 initialized.");
    }

    /*
     * Check mode, so
     * Send a BL Query Command
     */
    aucBuf[0] = 0; // Report ID. Ignored by HID Class firmware as only config'd
                   // for one report
    aucBuf[1] = FCD_HID_CMD_QUERY;
    hid_write(d_control_handle, aucBuf, 65);
    hid_read(d_control_handle, aucBuf, 65);
    aucBuf[15] = 0;
    d_logger->info("Dongle: {:s}", reinterpret_cast<const char*>(&aucBuf[2]));
    /*
     * Set initial values for the dongle
     */

    set_freq(args.freq);
    set_lna(args.lnaswitch);
    set_mixer_gain(args.mixergainswitch);
    set_if_gain(args.if_gain);
    /*
     * Initialize message handling
     *
     */
}

work_return_t fcdpp_control_cpu::work(work_io& wio)
{
    // Do <+signal processing+>
    // Block specific code goes here
    return work_return_t::OK;
}

void fcdpp_control_cpu::set_freq(double freq)
{
    unsigned int nfreq = freq;
    aucBuf[0] = 0;
    aucBuf[1] = FCD_HID_CMD_SET_FREQUENCY_HZ;
    aucBuf[2] = (unsigned char)nfreq;
    aucBuf[3] = (unsigned char)(nfreq >> 8);
    aucBuf[4] = (unsigned char)(nfreq >> 16);
    aucBuf[5] = (unsigned char)(nfreq >> 24);
    hid_write(d_control_handle, aucBuf, 65);
    aucBuf[1] = 0;
    hid_read(d_control_handle, aucBuf, 65);
    if (aucBuf[0] == FCD_HID_CMD_SET_FREQUENCY_HZ && aucBuf[1] == 1) {
        nfreq = 0;
        nfreq = (unsigned int)aucBuf[2];
        nfreq += (unsigned int)(aucBuf[3] << 8);
        nfreq += (unsigned int)(aucBuf[4] << 16);
        nfreq += (unsigned int)(aucBuf[5] << 24);
        d_logger->info("Set Frequency to: {:d} Hz", nfreq);

    } else {
        d_logger->error("Set Frequency to {:d} Hz failed", nfreq);
    }
}
void fcdpp_control_cpu::set_lna(int gain)
{
    aucBuf[0] = 0; // Report ID. Ignored by HID Class firmware as only config'd
                   // for one report
    aucBuf[1] = FCD_HID_CMD_SET_LNA_GAIN;
    if (gain != 0) {
        aucBuf[2] = 1;
    } else {
        aucBuf[2] = 0;
    }
    hid_write(d_control_handle, aucBuf, 65);
    hid_read(d_control_handle, aucBuf, 65);
    if (aucBuf[0] == FCD_HID_CMD_SET_LNA_GAIN) {
        if (gain != 0) {
            d_logger->info("LNA gain enabled");
        } else {
            d_logger->info("LNA gain disabled");
        }
    } else {
        d_logger->error("Failed to modify LNA gain. Result of transaction: {:d},{:d}",
                        aucBuf[0],
                        aucBuf[1]);
    }
}
void fcdpp_control_cpu::set_mixer_gain(int gain)
{
    aucBuf[0] = 0; // Report ID. Ignored by HID Class firmware as only config'd
                   // for one report
    aucBuf[1] = FCD_HID_CMD_SET_MIXER_GAIN;
    if (gain != 0) {
        aucBuf[2] = 1;
    } else {
        aucBuf[2] = 0;
    }
    hid_write(d_control_handle, aucBuf, 65);
    hid_read(d_control_handle, aucBuf, 65);
    if (aucBuf[0] == FCD_HID_CMD_SET_MIXER_GAIN) {
        if (gain != 0) {
            d_logger->info("Mixer gain enabled");
        } else {
            d_logger->info("Mixer gain disabled");
        }
    } else {
        d_logger->error("Failed to modify Mixer gain. Result of transaction: {:d},{:d}",
                        aucBuf[0],
                        aucBuf[1]);
    }
}
void fcdpp_control_cpu::set_if_gain(int gain)
{
    if ((gain < 0) || gain > 59) {
        d_logger->error("Invalid IF gain value: {:d}", gain);
        return;
    }
    aucBuf[0] = 0; // Report ID. Ignored by HID Class firmware as only config'd
                   // for one report
    aucBuf[1] = FCD_HID_CMD_SET_IF_GAIN;
    aucBuf[2] = (unsigned char)gain;
    hid_write(d_control_handle, aucBuf, 65);
    hid_read(d_control_handle, aucBuf, 65);
    if (aucBuf[0] == FCD_HID_CMD_SET_IF_GAIN) {
        d_logger->info("IF gain set to: {:d}", gain);
    } else {
        d_logger->error("Could not set IF gain");
    }
}
} // namespace funcube
} // namespace gr
