cmake_minimum_required(VERSION 3.12)

# INCLUSIVE MIN_VERSION and INCLUSIVE MAX_VERSION
function(afvd FEATURE_NAME FEATURE_MIN_VERSION)
  set(RESULT 0)

  if(${UVV} VERSION_GREATER_EQUAL ${FEATURE_MIN_VERSION})
    set(RESULT 1)
  endif()

  if(ARGN)
    list (GET ARGN 0 FEATURE_MAX_VERSION)
    if(NOT "${FEATURE_MAX_VERSION}" STREQUAL "")
      if(${UVV} VERSION_GREATER ${FEATURE_MAX_VERSION})
        message("A ${FEATURE_MAX_VERSION}")
        set(RESULT 0)
      else()
        message("B ${FEATURE_MAX_VERSION}")
      endif()
    endif()
  endif()

  target_compile_definitions(${TARGET} PUBLIC 
    "GALAXY_BUILD_FEATURE_${FEATURE_NAME}=${RESULT}"
  )
endfunction()

include(../galaxy_sdk_features.cmake)