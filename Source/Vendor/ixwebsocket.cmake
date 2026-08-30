set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(USE_TLS TRUE CACHE BOOL "" FORCE)
set(IXWEBSOCKET_INSTALL FALSE CACHE BOOL "" FORCE)
set(USE_MBED_TLS TRUE CACHE BOOL "" FORCE)

include(ixwebsocket-zlib.cmake)
include(ixwebsocket-mbedtls.cmake)

add_subdirectory(IXWebSocket-12.0.1)
