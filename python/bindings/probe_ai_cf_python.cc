/*
 * Copyright 2023 Free Software Foundation, Inc.
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
/* BINDTOOL_HEADER_FILE(probe_ai_cf.h)                                        */
/* BINDTOOL_HEADER_FILE_HASH(2f539f5f0c83411bcd28a5e9e2fcb27c)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <mer/probe_ai_cf.h>
// pydoc.h is automatically generated in the build directory
#include <probe_ai_cf_pydoc.h>

void bind_probe_ai_cf(py::module& m)
{

    using probe_ai_cf    = gr::mer::probe_ai_cf;


    py::class_<probe_ai_cf, gr::sync_block, gr::block, gr::basic_block,
        std::shared_ptr<probe_ai_cf>>(m, "probe_ai_cf", D(probe_ai_cf))

        .def(py::init(&probe_ai_cf::make),
           D(probe_ai_cf,make)
        )
        



        ;




}








