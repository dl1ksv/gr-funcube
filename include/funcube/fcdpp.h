/* -*- c++ -*- */
/*
 * Copyright 2020 dl1ksv.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_FUNCUBE_FCDPP_H
#define INCLUDED_FUNCUBE_FCDPP_H

#include <gnuradio/hier_block2.h>
#include <funcube/api.h>

namespace gr {
namespace funcube {

/*!
 * \brief Funcube Pro+ Dongle source block.
 *
 * This class provides a source block for the Funcube Pro+ Dongle by wrapping the
 * alsa audio interface and the USB control interface of the Funcube Dongle
 * into one convenient source block.
 * The hadware audio device is autodetected by the card name. If more than one Pro+ are
 * connected it takes the first card.
 * The block was tested with  firmware version 20.3
 *
 * \ingroup funcube
 *
 */
class FUNCUBE_API fcdpp : virtual public gr::hier_block2
{
public:
    typedef std::shared_ptr<fcdpp> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of funcube::fcdpp.
     *
     * To avoid accidental use of raw pointers, funcube::fcdpp's
     * constructor is in a private implementation
     * class. funcube::fcdpp::make is the public interface for
     * creating new instances.
     */
    static sptr make(const std::string device_name = "", int unit = 1);

    /*! \brief Set frequency with resolution defined by unit.
     *  \param freq The frequency in unit Hz
     *
     * Sets the frequency of the Funcube Dongle with Hz or Khz resolution
     * depending on the unit parameter ( 1: Hz , 1000 Khz )
     * applying the frequency correction set by set_freq_corr().
     *
     */
    virtual void set_freq(double freq) = 0;

    /*! \brief Switches the LNA on/off.
     *  \param gain  lna on/off.
     *
     */
    virtual void set_lna(int gain) = 0;

    /*! \brief Switches mixer gain onf/off.
     *  \param gain true means on.
     *
     */
    virtual void set_mixer_gain(int gain) = 0;

    /*! \brief Set new frequency correction.
     *  \param ppm The new frequency correction in parts per million
     *
     * Funcube recommends 0 for the Pro+.
     *
     * Ref: http://www.funcubedongle.com/MyImages/FCD2ManualV4.pdf
     */
    virtual void set_freq_corr(double ppm) = 0;

    /*! \brief Set If gain.
     *  \param gain The If gain value between 0 and 59 db
     *
     */
    virtual void set_if_gain(int gain) = 0;
};

} // namespace funcube
} // namespace gr

#endif /* INCLUDED_FUNCUBE_FCDPP_H */
