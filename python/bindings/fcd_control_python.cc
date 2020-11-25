/*
 * Copyright 2020 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

/***********************************************************************************/
/* This file is automatically generated using bindtool and can be manually edited  */
/* The following lines can be configured to regenerate this file during cmake      */
/* If manual edits are made, the following tags should be modified accordingly.    */
/* BINDTOOL_GEN_AUTOMATIC(0)                                                       */
/* BINDTOOL_USE_PYGCCXML(0)                                                        */
/* BINDTOOL_HEADER_FILE(fcd_control.h)                                        */
/* BINDTOOL_HEADER_FILE_HASH(0f61ad1312dc063b7ec2da730408797e)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <funcube/fcd_control.h>
// pydoc.h is automatically generated in the build directory
#include <fcd_control_pydoc.h>

void bind_fcd_control(py::module& m)
{

    using fcd_control    = ::gr::funcube::fcd_control;


    py::class_<fcd_control, gr::block, gr::basic_block,
        std::shared_ptr<fcd_control>>(m, "fcd_control", D(fcd_control))

        .def(py::init(&fcd_control::make),
           D(fcd_control,make)
        )
        




        .def("set_freq",&fcd_control::set_freq,
            py::arg("freq"),
            D(fcd_control,set_freq)
        )


        .def("set_lna_gain",&fcd_control::set_lna_gain,
            py::arg("gain"),
            D(fcd_control,set_lna_gain)
        )


        .def("set_mixer_gain",&fcd_control::set_mixer_gain,
            py::arg("gain"),
            D(fcd_control,set_mixer_gain)
        )


        .def("set_freq_corr",&fcd_control::set_freq_corr,
            py::arg("ppm"),
            D(fcd_control,set_freq_corr)
        )


        .def("set_dc_corr",&fcd_control::set_dc_corr,
            py::arg("_dci"),
            py::arg("_dcq"),
            D(fcd_control,set_dc_corr)
        )


        .def("set_iq_corr",&fcd_control::set_iq_corr,
            py::arg("_gain"),
            py::arg("_phase"),
            D(fcd_control,set_iq_corr)
        )

        ;




}






