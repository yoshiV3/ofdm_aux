INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_OFDMAUX ofdmAux)

FIND_PATH(
    OFDMAUX_INCLUDE_DIRS
    NAMES ofdmAux/api.h
    HINTS $ENV{OFDMAUX_DIR}/include
        ${PC_OFDMAUX_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    OFDMAUX_LIBRARIES
    NAMES gnuradio-ofdmAux
    HINTS $ENV{OFDMAUX_DIR}/lib
        ${PC_OFDMAUX_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(OFDMAUX DEFAULT_MSG OFDMAUX_LIBRARIES OFDMAUX_INCLUDE_DIRS)
MARK_AS_ADVANCED(OFDMAUX_LIBRARIES OFDMAUX_INCLUDE_DIRS)

