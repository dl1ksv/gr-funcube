# Copyright 2020 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

GR_PYTHON_CHECK_MODULE_RAW(
    "pygccxml"
    "import pygccxml"
    PYGCCXML_FOUND
    )

include(GrPybind)

########################################################################
# Python Bindings
########################################################################

list(APPEND funcube_python_files
    fcd_control_python.cc
    fcd_python.cc
    fcdpp_control_python.cc
    fcdpp_python.cc python_bindings.cc)

GR_PYBIND_MAKE_OOT(funcube 
   ../..
   gr::funcube
   "${funcube_python_files}")

install(TARGETS funcube_python DESTINATION ${GR_PYTHON_DIR}/funcube COMPONENT pythonapi)
