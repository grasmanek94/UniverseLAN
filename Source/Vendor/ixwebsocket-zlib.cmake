include_guard(GLOBAL)

set(ZLIB_BUILD_SHARED OFF CACHE BOOL "" FORCE)
set(ZLIB_BUILD_STATIC ON CACHE BOOL "" FORCE)
set(ZLIB_BUILD_TESTING OFF CACHE BOOL "" FORCE)
set(ZLIB_BUILD_MINIZIP OFF CACHE BOOL "" FORCE)
set(ZLIB_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(zlib-1.3.2)

if(NOT TARGET zlibstatic)
    message(FATAL_ERROR
        "ixwebsocket-zlib.cmake: zlibstatic target was not created."
    )
endif()

# IXWebSocket links specifically against ZLIB::ZLIB.
if(NOT TARGET ZLIB::ZLIB)
    add_library(ZLIB::ZLIB ALIAS zlibstatic)
endif()

# FindZLIB still requires these legacy variables even though IXWebSocket
# ultimately links against the ZLIB::ZLIB target.
set(
    ZLIB_INCLUDE_DIR
    "${CMAKE_CURRENT_SOURCE_DIR}/zlib-1.3.2"
    CACHE PATH
    "In-tree zlib include directory"
    FORCE
)

set(
    ZLIB_INCLUDE_DIRS
    "${CMAKE_CURRENT_SOURCE_DIR}/zlib-1.3.2;${CMAKE_CURRENT_BINARY_DIR}/zlib-1.3.2"
    CACHE STRING
    "In-tree zlib include directories"
    FORCE
)

# This only needs to satisfy FindZLIB's legacy result validation.
# IXWebSocket does not link this variable. It links ZLIB::ZLIB.
set(
    ZLIB_LIBRARY
    "zlibstatic"
    CACHE STRING
    "In-tree zlib target"
    FORCE
)

set(
    ZLIB_LIBRARIES
    "zlibstatic"
    CACHE STRING
    "In-tree zlib target"
    FORCE
)

set(
    ZLIB_VERSION_STRING
    "1.3.2"
    CACHE STRING
    "In-tree zlib version"
    FORCE
)

set(ZLIB_FOUND TRUE CACHE BOOL "" FORCE)

message(STATUS "IXWebSocket: using in-tree zlib target zlibstatic")
