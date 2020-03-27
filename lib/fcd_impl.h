/* -*- c++ -*- */
/*
 * Copyright 2020 dl1ksv.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_FUNCUBE_FCD_IMPL_H
#define INCLUDED_FUNCUBE_FCD_IMPL_H

#include <funcube/fcd.h>

namespace gr {
  namespace funcube {

    class fcd_impl : public fcd
    {
     private:
      // Nothing to declare in this block.

     public:
      fcd_impl(const std::string device_name);
      ~fcd_impl();

      // Where all the action really happens
    };

  } // namespace funcube
} // namespace gr

#endif /* INCLUDED_FUNCUBE_FCD_IMPL_H */

