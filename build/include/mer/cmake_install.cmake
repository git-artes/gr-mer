# Install script for directory: /home/belza/Dropbox/software/gr-mer/include/mer

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Release")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mer" TYPE FILE FILES
    "/home/belza/Dropbox/software/gr-mer/include/mer/api.h"
    "/home/belza/Dropbox/software/gr-mer/include/mer/probe_mer_c.h"
    "/home/belza/Dropbox/software/gr-mer/include/mer/demapper.h"
    "/home/belza/Dropbox/software/gr-mer/include/mer/mer.h"
    "/home/belza/Dropbox/software/gr-mer/include/mer/probe_ste_cf.h"
    "/home/belza/Dropbox/software/gr-mer/include/mer/ste.h"
    "/home/belza/Dropbox/software/gr-mer/include/mer/probe_cs_cf.h"
    "/home/belza/Dropbox/software/gr-mer/include/mer/carrier_suppression.h"
    "/home/belza/Dropbox/software/gr-mer/include/mer/probe_ai_cf.h"
    "/home/belza/Dropbox/software/gr-mer/include/mer/amplitude_imbalance.h"
    "/home/belza/Dropbox/software/gr-mer/include/mer/probe_qe_cf.h"
    "/home/belza/Dropbox/software/gr-mer/include/mer/quadrature_error.h"
    "/home/belza/Dropbox/software/gr-mer/include/mer/probe_pj_cf.h"
    "/home/belza/Dropbox/software/gr-mer/include/mer/phase_jitter.h"
    "/home/belza/Dropbox/software/gr-mer/include/mer/probe_all_meassurements_cf.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

