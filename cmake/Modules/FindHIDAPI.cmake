if(NOT LIBHIDAPI_FOUND)
  find_path(LIBHIDAPI_INCLUDE_DIR NAMES hidapi.h
    PATHS
    ${LIBHIDAPI_PKG_INCLUDE_DIRS}
    /usr/include/hidapi
    /usr/include
    /usr/local/include
  )

  find_library(LIBHIDAPI_LIBRARIES NAMES libhidapi-libusb hidapi-libusb
    PATHS
    ${LIBHIDAPI_PKG_LIBRARY_DIRS}
    /usr/lib
    /usr/local/lib
  )

if(LIBHIDAPI_INCLUDE_DIR AND LIBHIDAPI_LIBRARIES)
  set(LIBHIDAPI_FOUND TRUE CACHE INTERNAL "libhidapi found")
  message(STATUS "Found hidapi lib: ${LIBHIDAPI_INCLUDE_DIR}, ${LIBHIDAPI_LIBRARIES}")
else(LIBHIDAPI_INCLUDE_DIR AND LIBHIDAPI_LIBRARIES)
  set(LIBHIDAPI_FOUND FALSE CACHE INTERNAL "libhidapi found")
  message(STATUS "hidapi lib not found.")
endif(LIBHIDAPI_INCLUDE_DIR AND LIBHIDAPI_LIBRARIES)

mark_as_advanced(LIBHIDAPI_INCLUDE_DIR LIBHIDAPI_LIBRARIES)

endif(NOT LIBHIDAPI_FOUND)
