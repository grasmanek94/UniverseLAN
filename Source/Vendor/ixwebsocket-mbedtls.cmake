include_guard(GLOBAL)

set(GEN_FILES OFF CACHE BOOL "" FORCE)
set(ENABLE_PROGRAMS OFF CACHE BOOL "" FORCE)
set(MBEDTLS_AS_SUBPROJECT ON CACHE BOOL "" FORCE)
set(ENABLE_TESTING OFF CACHE BOOL "" FORCE)
set(USE_STATIC_MBEDTLS_LIBRARY ON CACHE BOOL "" FORCE)
set(USE_SHARED_MBEDTLS_LIBRARY OFF CACHE BOOL "" FORCE)

set(_saved_disable_find_python3
    "${CMAKE_DISABLE_FIND_PACKAGE_Python3}"
)

set(CMAKE_DISABLE_FIND_PACKAGE_Python3 TRUE)

add_subdirectory(mbedtls-4.2.0)

if(DEFINED _saved_disable_find_python3 AND
   NOT _saved_disable_find_python3 STREQUAL "")
    set(
        CMAKE_DISABLE_FIND_PACKAGE_Python3
        "${_saved_disable_find_python3}"
    )
else()
    unset(CMAKE_DISABLE_FIND_PACKAGE_Python3)
endif()

unset(_saved_disable_find_python3)

# This helper must be included after:
#
#   add_subdirectory(mbedtls-4.2.0)
#
# and before:
#
#   add_subdirectory(IXWebSocket-12.0.1)

if(TARGET mbedtls)
    set(_ix_mbedtls_target mbedtls)
elseif(TARGET MbedTLS::mbedtls)
    set(_ix_mbedtls_target MbedTLS::mbedtls)
else()
    message(FATAL_ERROR
        "ixwebsocket-mbedtls.cmake: Cannot find the mbedtls target. "
        "Call add_subdirectory(mbedtls-4.2.0) first."
    )
endif()

if(TARGET mbedx509)
    set(_ix_mbedx509_target mbedx509)
elseif(TARGET MbedTLS::mbedx509)
    set(_ix_mbedx509_target MbedTLS::mbedx509)
else()
    message(FATAL_ERROR
        "ixwebsocket-mbedtls.cmake: Cannot find the mbedx509 target."
    )
endif()

# Mbed TLS 4.x replaced mbedcrypto with TF-PSA-Crypto.
if(TARGET tfpsacrypto)
    set(_ix_mbedcrypto_target tfpsacrypto)
elseif(TARGET TFPSACrypto::tfpsacrypto)
    set(_ix_mbedcrypto_target TFPSACrypto::tfpsacrypto)
elseif(TARGET mbedcrypto)
    set(_ix_mbedcrypto_target mbedcrypto)
elseif(TARGET MbedTLS::mbedcrypto)
    set(_ix_mbedcrypto_target MbedTLS::mbedcrypto)
else()
    message(FATAL_ERROR
        "ixwebsocket-mbedtls.cmake: Cannot find tfpsacrypto "
        "or mbedcrypto."
    )
endif()

get_target_property(
    _ix_mbedtls_interface_includes
    ${_ix_mbedtls_target}
    INTERFACE_INCLUDE_DIRECTORIES
)

if(NOT _ix_mbedtls_interface_includes OR
   _ix_mbedtls_interface_includes STREQUAL
       "_ix_mbedtls_interface_includes-NOTFOUND")
    message(FATAL_ERROR
        "ixwebsocket-mbedtls.cmake: The mbedtls target has no "
        "INTERFACE_INCLUDE_DIRECTORIES."
    )
endif()

# IXWebSocket wraps MBEDTLS_INCLUDE_DIRS inside BUILD_INTERFACE itself.
# Therefore, remove Mbed TLS's existing BUILD_INTERFACE wrappers and
# discard INSTALL_INTERFACE entries.
set(_ix_mbedtls_plain_include_dirs "")

foreach(_ix_include IN LISTS _ix_mbedtls_interface_includes)
    if(_ix_include MATCHES "^\\$<BUILD_INTERFACE:(.*)>$")
        list(APPEND
            _ix_mbedtls_plain_include_dirs
            "${CMAKE_MATCH_1}"
        )
    elseif(_ix_include MATCHES "^\\$<INSTALL_INTERFACE:.*>$")
        # Not relevant while consuming Mbed TLS from the build tree.
    elseif(NOT _ix_include MATCHES "^\\$<")
        list(APPEND
            _ix_mbedtls_plain_include_dirs
            "${_ix_include}"
        )
    endif()
endforeach()

list(REMOVE_DUPLICATES _ix_mbedtls_plain_include_dirs)

if(NOT _ix_mbedtls_plain_include_dirs)
    message(FATAL_ERROR
        "ixwebsocket-mbedtls.cmake: No usable build-tree include "
        "directories could be extracted from the mbedtls target."
    )
endif()

# Legacy variables expected by IXWebSocket 12.0.1.
set(MBEDTLS_FOUND TRUE)
set(MbedTLS_FOUND TRUE)

set(
    MBEDTLS_INCLUDE_DIRS
    ${_ix_mbedtls_plain_include_dirs}
)

set(
    MBEDTLS_LIBRARIES
    ${_ix_mbedtls_target}
    ${_ix_mbedx509_target}
    ${_ix_mbedcrypto_target}
)

set(MBEDTLS_VERSION "4.2.0")
set(MBEDTLS_VERSION_GREATER_THAN_3 TRUE)

# IXWebSocket only adds this definition inside its find_package branch.
# Since MBEDTLS_FOUND is already true, that branch is skipped.
#
# Directory compile definitions are inherited by the IXWebSocket
# subdirectory added afterward.
add_compile_definitions(
    IXWEBSOCKET_USE_MBED_TLS_MIN_VERSION_3
)

message(STATUS
    "IXWebSocket: using in-tree Mbed TLS targets: "
    "${_ix_mbedtls_target};"
    "${_ix_mbedx509_target};"
    "${_ix_mbedcrypto_target}"
)

message(STATUS
    "IXWebSocket: Mbed TLS includes: "
    "${MBEDTLS_INCLUDE_DIRS}"
)

unset(_ix_mbedtls_target)
unset(_ix_mbedx509_target)
unset(_ix_mbedcrypto_target)
unset(_ix_mbedtls_interface_includes)
unset(_ix_mbedtls_plain_include_dirs)
unset(_ix_include)
