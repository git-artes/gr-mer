# Copyright 2020 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

########################################################################
# Check if there is C++ code at all
########################################################################
if(NOT mer_sources)
    MESSAGE(STATUS "No C++ sources... skipping python bindings")
    return()
endif(NOT mer_sources)

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
list(APPEND mer_python_files
    probe_ai_cf_python.cc
    probe_cs_cf_python.cc
    probe_pj_cf_python.cc
    probe_qe_cf_python.cc
    probe_ste_cf_python.cc
    probe_mer_c_python.cc
    probe_all_meassurements_cf_python.cc
    qam_desrotator_cf_python.cc python_bindings.cc)

GR_PYBIND_MAKE_OOT(mer
   ../..
   gr::mer
   "${mer_python_files}")

# copy bindings extension for use in QA test module
add_custom_command(TARGET mer_python POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:mer_python>
    ${CMAKE_BINARY_DIR}/test_modules/mer/
)

install(TARGETS mer_python DESTINATION ${GR_PYTHON_DIR}/mer COMPONENT pythonapi)
