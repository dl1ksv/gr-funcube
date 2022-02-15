/* -*- c++ -*- */
/*
 * Copyright 2020 dl1ksv.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "fcd_control_impl.h"
#include "fcdcmd.h"
#include <gnuradio/io_signature.h>
#include <gnuradio/logger.h>

#define FCD_VENDOR_ID 0x04D8  /*!< USB vendor ID. */
#define FCD_PRODUCT_ID 0xFB56 /*!< USB product ID. */

namespace gr {
namespace funcube {

/*
 * Create a new instance of gr::fcd::fcd_control_impl and return an
 * upcasted boost shared_ptr. This is effectively the public
 * constructor.
 */
fcd_control::sptr fcd_control::make()
{
    return gnuradio::get_initial_sptr(new fcd_control_impl());
}

/*
 * The private constructor
 */
fcd_control_impl::fcd_control_impl()
    : gr::block("fcd_control",
                gr::io_signature::make(0, 0, 0),
                gr::io_signature::make(0, 0, 0)),
      d_freq_corr(-120)
{
    /* setup the control part */
    d_control_handle = NULL;
    hid_init();
    d_control_handle = hid_open(FCD_VENDOR_ID, FCD_PRODUCT_ID, NULL);
    if (d_control_handle == NULL) {
        d_logger->error("FunCube Dongle  V1.0 not found.");
        throw std::runtime_error("FunCube Dongle  V1.0 not found.");
    } else {
        d_logger->info("FunCube Dongle  V1.0 initialized.");
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
    d_logger->info("Dongle: {:s}", &aucBuf[2]);
    /*
     * Initialize message handling
     *
     * Replace boost::function with std::function
     *
     */

    message_port_register_in(pmt::mp("freq"));
    /*
     * set_msg_handler(pmt::mp("freq"),
     *               boost::bind(&fcd_control_impl::set_frequency_msg, this, _1));
     */
    set_msg_handler(pmt::mp("freq"), [this](pmt::pmt_t msg) {
        this->fcd_control_impl::set_frequency_msg(msg);
    });
}

fcd_control_impl::~fcd_control_impl()
{
    if (d_control_handle != NULL) {
        hid_close(d_control_handle);
    }
    hid_exit();
}

// Set frequency with Hz resolution (type float)
void fcd_control_impl::set_freq(float freq)
{
    /* valid range 50 MHz - 2.0 GHz */
    if ((freq < 50.0e6) || (freq > 2.0e9))
        return;

    unsigned int nfreq = (double)freq * (1.0 + d_freq_corr / 1000000.0);
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

// Set LNA gain
void fcd_control_impl::set_lna_gain(float gain)
{
    unsigned char g;

    /* convert to nearest discrete value */
    if (gain > 27.5) {
        g = 14; // 30.0 dB
    } else if (gain > 22.5) {
        g = 13; // 25.0 dB
    } else if (gain > 18.75) {
        g = 12; // 20.0 dB
    } else if (gain > 16.25) {
        g = 11; // 17.5 dB
    } else if (gain > 13.75) {
        g = 10; // 15.0 dB
    } else if (gain > 11.25) {
        g = 9; // 12.5 dB
    } else if (gain > 8.75) {
        g = 8; // 10.0 dB
    } else if (gain > 6.25) {
        g = 7; // 7.5 dB
    } else if (gain > 3.75) {
        g = 6; // 5.0 dB
    } else if (gain > 1.25) {
        g = 5; // 2.5 dB
    } else if (gain > -1.25) {
        g = 4; // 0.0 dB
    } else if (gain > -3.75) {
        g = 1; // -2.5 dB
    } else {
        g = 0; // -5.0 dB
    }
    aucBuf[0] = 0; // Report ID. Ignored by HID Class firmware as only config'd
                   // for one report
    aucBuf[1] = FCD_HID_CMD_SET_LNA_GAIN;
    aucBuf[2] = g;
    hid_write(d_control_handle, aucBuf, 65);
    hid_read(d_control_handle, aucBuf, 65);
    if (aucBuf[0] == FCD_HID_CMD_SET_LNA_GAIN) {
        d_logger->info("LNA gain set to: {:g}", gain);
    } else {
        d_logger->error("Failed to modify LNA gain. Result of transaction: {:d},{:d}",
                        aucBuf[0],
                        aucBuf[1]);
    }
}

// Set mixer gain
void fcd_control_impl::set_mixer_gain(float gain)
{
    unsigned char g;

    if (gain > 4.0) {
        g = TMGE_P12_0DB;
    } else {
        g = TMGE_P4_0DB;
    }

    aucBuf[0] = 0; // Report ID. Ignored by HID Class firmware as only config'd
                   // for one report
    aucBuf[1] = FCD_HID_CMD_SET_MIXER_GAIN;
    aucBuf[2] = g;
    hid_write(d_control_handle, aucBuf, 65);
    hid_read(d_control_handle, aucBuf, 65);
    if (aucBuf[0] == FCD_HID_CMD_SET_MIXER_GAIN) {
        d_logger->info("Mixer gain set to: {:g}", gain);
    }

    else {
        d_logger->error("Failed to modify Mixer gain. Result of transaction: {:d},{:d}",
                        aucBuf[0],
                        aucBuf[1]);
    }
}

// Set new frequency correction
void fcd_control_impl::set_freq_corr(int ppm)
{
    d_freq_corr = ppm;
    // re-tune with new correction value
    // set_freq(d_freq_req);
}

// Set DC offset correction.
void fcd_control_impl::set_dc_corr(double _dci, double _dcq)
{
    union {
        unsigned char auc[4];
        struct {
            signed short dci; // equivalent of qint16 which should be 16 bit everywhere
            signed short dcq;
        };
    } dcinfo;

    if ((_dci < -1.0) || (_dci > 1.0) || (_dcq < -1.0) || (_dcq > 1.0))
        return;

    dcinfo.dci = static_cast<signed short>(_dci * 32768.0);
    dcinfo.dcq = static_cast<signed short>(_dcq * 32768.0);
    aucBuf[0] = 0; // Report ID. Ignored by HID Class firmware as only config'd
                   // for one report
    aucBuf[1] = FCD_CMD_APP_SET_DC_CORR;
    for (int i = 0; i < 4; i++)
        aucBuf[2 + i] = dcinfo.auc[i];

    hid_write(d_control_handle, aucBuf, 65);
    hid_read(d_control_handle, aucBuf, 65);
    if (aucBuf[0] == FCD_CMD_APP_SET_DC_CORR) {
        d_logger->info("DC offset correction set");
    }

    else {
        d_logger->error(
            "Failed to set DC offset correction. Result of transaction: {:d},{:d}",
            aucBuf[0],
            aucBuf[1]);
    }
}

// Set IQ phase and gain balance.
void fcd_control_impl::set_iq_corr(double _gain, double _phase)
{
    union {
        unsigned char auc[4];
        struct {
            signed short phase;
            signed short gain;
        };
    } iqinfo;

    if ((_gain < -1.0) || (_gain > 1.0) || (_phase < -1.0) || (_phase > 1.0))
        return;

    iqinfo.phase = static_cast<signed short>(_phase * 32768.0);
    iqinfo.gain = static_cast<signed short>(_gain * 32768.0);
    aucBuf[0] = 0; // Report ID. Ignored by HID Class firmware as only config'd
                   // for one report
    aucBuf[1] = FCD_CMD_APP_SET_IQ_CORR;
    for (int i = 0; i < 4; i++)
        aucBuf[2 + i] = iqinfo.auc[i];

    hid_write(d_control_handle, aucBuf, 65);
    hid_read(d_control_handle, aucBuf, 65);
    if (aucBuf[0] == FCD_CMD_APP_SET_IQ_CORR) {
        d_logger->info("IQ phase and gain balance set");
    }

    else {
        d_logger->error(
            "Failed to set IQ phase and gain balance. Result of transaction: {:d},{:d}",
            aucBuf[0],
            aucBuf[1]);
    }
}

void fcd_control_impl::set_frequency_msg(pmt::pmt_t msg)
{
    // Accepts either a number that is assumed to be the new
    // frequency or a key:value pair message where the key must be
    // "freq" and the value is the new frequency.
    d_logger->debug("Funcube Control frequency message arrived");
    if (pmt::is_number(msg)) {
        set_freq(pmt::to_double(msg));
    } else if (pmt::is_pair(msg)) {
        pmt::pmt_t key = pmt::car(msg);
        pmt::pmt_t val = pmt::cdr(msg);
        if (pmt::eq(key, pmt::intern("freq"))) {
            if (pmt::is_number(val)) {
                set_freq(pmt::to_double(val));
            }
        } else {
            d_logger->warn(
                "Set Frequency Message must have the key = 'freq'; got '{:s}'.",
                pmt::write_string(key));
        }
    } else {
        d_logger->warn("Set Frequency Message must be either a number or a "
                       "key:value pair where the key is 'freq'.");
    }
}

} /* namespace funcube */
} /* namespace gr */
