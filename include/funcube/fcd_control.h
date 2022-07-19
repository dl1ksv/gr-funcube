/* -*- c++ -*- */
/*
 * Copyright 2020 dl1ksv.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_FUNCUBE_FCD_CONTROL_H
#define INCLUDED_FUNCUBE_FCD_CONTROL_H

#include <gnuradio/block.h>
#include <funcube/api.h>

namespace gr {
namespace funcube {

/*!
 * \brief <+description of block+>
 * \ingroup funcube
 *
 */
class FUNCUBE_API fcd_control : virtual public gr::block
{
public:
    typedef std::shared_ptr<fcd_control> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of funcube::fcd_control.
     *
     * To avoid accidental use of raw pointers, funcube::fcd_control's
     * constructor is in a private implementation
     * class. funcube::fcd_control::make is the public interface for
     * creating new instances.
     */
    static sptr make();
    /*! \brief Set frequency with Hz resolution.
     *  \param freq The frequency in Hz
     *
     * This is a convenience function that uses float parameter in
     * order to allow using engineering notation in GRC.
     *
     */
    virtual void set_freq(double freq) = 0;

    /*! \brief Set LNA gain.
     *  \param gain The new gain in dB.
     *
     * Set the LNA gain in the FCD. Valid range is -5 to
     * 30. Although the LNA gain in the FCD takes enumerated values
     * corresponding to 2.5 dB steps, you can can call this method
     * with any float value and it will be rounded to the nearest
     * valid value.
     *
     * By default the LNA gain is set to 20 dB and this is a good value for
     * most cases. In noisy areas you may try to reduce the gain.
     */
    virtual void set_lna_gain(float gain) = 0;

    /*! \brief Set mixer gain.
     *  \param gain The new gain in dB.
     *
     * Set the mixer gain in the FCD. Valid values are +4 and +12 dB.
     *
     * By default the mixer gain is set to +12 dB and this is a good
     * value for most cases. In noisy areas you may try to reduce
     * the gain.
     */
    virtual void set_mixer_gain(float gain) = 0;

    /*! \brief Set DC offset correction.
     *  \param _dci DC correction for I component (-1.0 to 1.0)
     *  \param _dcq DC correction for Q component (-1.0 to 1.0)
     *
     * Set DC offset correction in the device. Default is 0.0.
     */
    virtual void set_dc_corr(double _dci, double _dcq) = 0;

    /*! \brief Set IQ phase and gain balance.
     *  \param _gain The gain correction (-1.0 to 1.0)
     *  \param _phase The phase correction (-1.0 to 1.0)
     *
     * Set IQ phase and gain balance in the device. The default values
     * are 0.0 for phase and 1.0 for gain.
     */
    virtual void set_iq_corr(double _gain, double _phase) = 0;
};

} // namespace funcube
} // namespace gr

#endif /* INCLUDED_FUNCUBE_FCD_CONTROL_H */
