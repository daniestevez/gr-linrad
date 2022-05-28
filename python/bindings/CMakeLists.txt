# Copyright 2020 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

########################################################################
# Check if there is C++ code at all
########################################################################
if(NOT linrad_sources)
    MESSAGE(STATUS "No C++ sources... skipping python bindings")
    return()
endif(NOT linrad_sources)

########################################################################
# Check for pygccxml
########################################################################
GR_PYTHON_CHECK_MODULE_RAW(
    "pygccxml"
    "import pygccxml"
    PYGCCXML_FOUND
    )

include(GrPybind)

########################################################################
# Python Bindings
########################################################################

list(APPEND linrad_python_files
    python_bindings.cc
    send_raw16_python.cc
    send_raw24_python.cc)

GR_PYBIND_MAKE_OOT(linrad
   ../..
   gr::linrad
   "${linrad_python_files}")

install(TARGETS linrad_python DESTINATION ${GR_PYTHON_DIR}/linrad COMPONENT pythonapi)
