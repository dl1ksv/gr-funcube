/* -*- c++ -*- */
/*
 * Copyright 2020 dl1ksv.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_FUNCUBE_FCD_H
#define INCLUDED_FUNCUBE_FCD_H

#include <funcube/api.h>
#include <gnuradio/hier_block2.h>

namespace gr {
  namespace funcube {

    /*!
     * \brief <+description of block+>
     * \ingroup funcube
     *
     */
    class FUNCUBE_API fcd : virtual public gr::hier_block2
    {
     public:
      typedef boost::shared_ptr<fcd> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of funcube::fcd.
       *
       * To avoid accidental use of raw pointers, funcube::fcd's
       * constructor is in a private implementation
       * class. funcube::fcd::make is the public interface for
       * creating new instances.
       */
      static sptr make(const std::string device_name = "");
    };

  } // namespace funcube
} // namespace gr

#endif /* INCLUDED_FUNCUBE_FCD_H */

