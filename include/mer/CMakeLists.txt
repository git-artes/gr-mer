# Copyright 2011,2012 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.

########################################################################
# Install public header files
########################################################################
install(FILES
    api.h
    probe_mer_c.h
    demapper.h
    mer.h
    probe_ste_cf.h
    ste.h
    probe_cs_cf.h
    carrier_suppression.h
    probe_ai_cf.h
    amplitude_imbalance.h
    probe_qe_cf.h
    quadrature_error.h
    probe_pj_cf.h
    phase_jitter.h
    probe_all_meassurements_cf.h DESTINATION include/mer
)
