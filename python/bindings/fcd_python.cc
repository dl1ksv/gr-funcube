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
/* BINDTOOL_HEADER_FILE(fcd.h)                                        */
/* BINDTOOL_HEADER_FILE_HASH(07066cb146612ba061c886f3eb8defc9)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <funcube/fcd.h>
// pydoc.h is automatically generated in the build directory
#include <fcd_pydoc.h>

void bind_fcd(py::module& m)
{

    using fcd    = ::gr::funcube::fcd;


    py::class_<fcd, gr::hier_block2,
        std::shared_ptr<fcd>>(m, "fcd", D(fcd))

        .def(py::init(&fcd::make),
           py::arg("device_name") = "",
           D(fcd,make)
        )
        




        .def("set_freq",&fcd::set_freq,
            py::arg("freq"),
            D(fcd,set_freq)
        )


        .def("set_lna_gain",&fcd::set_lna_gain,
            py::arg("gain"),
            D(fcd,set_lna_gain)
        )


        .def("set_mixer_gain",&fcd::set_mixer_gain,
            py::arg("gain"),
            D(fcd,set_mixer_gain)
        )


        .def("set_freq_corr",&fcd::set_freq_corr,
            py::arg("ppm"),
            D(fcd,set_freq_corr)
        )


        .def("set_dc_corr",&fcd::set_dc_corr,
            py::arg("_dci"),
            py::arg("_dcq"),
            D(fcd,set_dc_corr)
        )


        .def("set_iq_corr",&fcd::set_iq_corr,
            py::arg("_gain"),
            py::arg("_phase"),
            D(fcd,set_iq_corr)
        )

        ;




}







