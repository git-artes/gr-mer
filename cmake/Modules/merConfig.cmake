INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_MER mer)

FIND_PATH(
    MER_INCLUDE_DIRS
    NAMES mer/api.h
    HINTS $ENV{MER_DIR}/include
        ${PC_MER_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    MER_LIBRARIES
    NAMES gnuradio-mer
    HINTS $ENV{MER_DIR}/lib
        ${PC_MER_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(MER DEFAULT_MSG MER_LIBRARIES MER_INCLUDE_DIRS)
MARK_AS_ADVANCED(MER_LIBRARIES MER_INCLUDE_DIRS)

