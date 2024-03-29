# Copyright 2011 Free Software Foundation, Inc.
#
# This file was generated by gr_modtool, a tool from the GNU Radio framework
# This file is a part of gr-mer
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

########################################################################
# Include python install macros
########################################################################
include(GrPython)
if(NOT PYTHONINTERP_FOUND)
    return()
endif()

add_subdirectory(bindings)

########################################################################
# Install python sources
########################################################################
GR_PYTHON_INSTALL(
    FILES
    __init__.py
    DESTINATION ${GR_PYTHON_DIR}/mer
)

########################################################################
# Handle the unit tests
########################################################################
include(GrTest)

set(GR_TEST_TARGET_DEPS gnuradio-mer)

# Create a package directory that tests can import. It includes everything
# from `python/`.
add_custom_target(
  copy_module_for_tests ALL
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}
          ${CMAKE_BINARY_DIR}/test_modules/mer/
)
GR_ADD_TEST(qa_probe_ai_cf ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/qa_probe_ai_cf.py)
GR_ADD_TEST(qa_probe_cs_cf ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/qa_probe_cs_cf.py)
GR_ADD_TEST(qa_probe_pj_cf ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/qa_probe_pj_cf.py)
GR_ADD_TEST(qa_probe_qe_cf ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/qa_probe_qe_cf.py)
GR_ADD_TEST(qa_probe_ste_cf ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/qa_probe_ste_cf.py)
GR_ADD_TEST(qa_probe_mer_c ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/qa_probe_mer_c.py)
GR_ADD_TEST(qa_probe_all_meassurements_cf ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/qa_probe_all_meassurements_cf.py)
