/* -*- c++ -*- */
/*
 * Copyright 2020 dl1ksv.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_FUNCUBE_FCDPP_CONTROL_H
#define INCLUDED_FUNCUBE_FCDPP_CONTROL_H

#include <gnuradio/block.h>
#include <funcube/api.h>

namespace gr {
namespace funcube {

/*!
 * \brief <+description of block+>
 * \ingroup funcube
 *
 */
class FUNCUBE_API fcdpp_control : virtual public gr::block
{
public:
    typedef std::shared_ptr<fcdpp_control> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of funcube::fcdpp_control.
     *
     * To avoid accidental use of raw pointers, funcube::fcdpp_control's
     * constructor is in a private implementation
     * class. funcube::fcdpp_control::make is the public interface for
     * creating new instances.
     */
    static sptr make();
    /*! \brief Sets the frequency .
     *  \param freq The frequency in unit Hz
     *
     * Sets the frequency of the Funcube Dongle with Hz resolution
     *
     */
    virtual void set_freq(float freq) = 0;

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

    /*! \brief Set If gain.
     *  \param gain The If gain value between 0 and 59 db
     *
     */
    virtual void set_if_gain(int gain) = 0;
};

} // namespace funcube
} // namespace gr

#endif /* INCLUDED_FUNCUBE_FCDPP_CONTROL_H */
