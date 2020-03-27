/* -*- c++ -*- */
/*
 * Copyright 2020 dl1ksv.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "fcd_impl.h"

namespace gr {
  namespace funcube {

    fcd::sptr
    fcd::make(const std::string device_name)
    {
      return gnuradio::get_initial_sptr
        (new fcd_impl(device_name));
    }


    /*
     * The private constructor
     */
    fcd_impl::fcd_impl(const std::string device_name)
      : gr::hier_block2("fcd",
              gr::io_signature::make(<+MIN_IN+>, <+MAX_IN+>, sizeof(<+ITYPE+>)),
              gr::io_signature::make(<+MIN_OUT+>, <+MAX_OUT+>, sizeof(<+OTYPE+>)))
    {
      connect(self(), 0, d_firstblock, 0);
      // connect other blocks
      connect(d_lastblock, 0, self(), 0);
    }

    /*
     * Our virtual destructor.
     */
    fcd_impl::~fcd_impl()
    {
    }


  } /* namespace funcube */
} /* namespace gr */

