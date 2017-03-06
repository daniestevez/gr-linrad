INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_LINRAD linrad)

FIND_PATH(
    LINRAD_INCLUDE_DIRS
    NAMES linrad/api.h
    HINTS $ENV{LINRAD_DIR}/include
        ${PC_LINRAD_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    LINRAD_LIBRARIES
    NAMES gnuradio-linrad
    HINTS $ENV{LINRAD_DIR}/lib
        ${PC_LINRAD_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(LINRAD DEFAULT_MSG LINRAD_LIBRARIES LINRAD_INCLUDE_DIRS)
MARK_AS_ADVANCED(LINRAD_LIBRARIES LINRAD_INCLUDE_DIRS)

