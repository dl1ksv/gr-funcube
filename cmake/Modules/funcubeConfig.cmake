INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_FUNCUBE funcube)

FIND_PATH(
    FUNCUBE_INCLUDE_DIRS
    NAMES funcube/api.h
    HINTS $ENV{FUNCUBE_DIR}/include
        ${PC_FUNCUBE_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    FUNCUBE_LIBRARIES
    NAMES gnuradio-funcube
    HINTS $ENV{FUNCUBE_DIR}/lib
        ${PC_FUNCUBE_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/funcubeTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(FUNCUBE DEFAULT_MSG FUNCUBE_LIBRARIES FUNCUBE_INCLUDE_DIRS)
MARK_AS_ADVANCED(FUNCUBE_LIBRARIES FUNCUBE_INCLUDE_DIRS)
