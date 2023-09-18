cmake_minimum_required(VERSION 3.13)

######################################################################################

project( universelan )

set(CMAKE_CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_REQUIRED True)

enable_language( CXX )
enable_language( C )

if(MSVC)
  add_definitions(/MP)
  set(UNIVERSELAN_EXTRA_BIN_FOLDER "")

  if("${MSVC_C_ARCHITECTURE_ID}" STREQUAL "X86")
    set(GALAXY_ARCH "x86")
  elseif("${MSVC_C_ARCHITECTURE_ID}" STREQUAL "x64")
    set(GALAXY_ARCH "x64")
  endif()

  # Enable EHa 
  #string(REGEX REPLACE "/EHsc" "/EHa" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
else()
  set(CMAKE_POSITION_INDEPENDENT_CODE ON)
  set(UNIVERSELAN_EXTRA_BIN_FOLDER "${CMAKE_BUILD_TYPE}/")

  if(NOT GALAXY_ARCH)
    set(GALAXY_ARCH "" CACHE STRING "Architecture which is being compiled for (x86 or x64)")
  endif()

  if(NOT "--${GALAXY_ARCH}--" STREQUAL "--x86--")
    if(NOT "--${GALAXY_ARCH}--" STREQUAL "--x64--")   
      message("Unknown GALAXY_ARCH, please define GALAXY_ARCH manually (x86 or x64)")
      return()
    endif()
  endif()

  # adjust the default behaviour of the FIND_XXX() commands:
  # search headers and libraries in the target environment, search
  # programs in the host environment
  set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
  set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
  set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

  if("--${GALAXY_ARCH}--" STREQUAL "--x86--")
    set(CMAKE_C_FLAGS -m32)
    set(CMAKE_CXX_FLAGS -m32)

    # here is the target environment located
    set(CMAKE_FIND_ROOT_PATH   /usr/i486-linux-gnu )
  else()
    set(CMAKE_C_FLAGS -m64)
    set(CMAKE_CXX_FLAGS -m64)
  endif()
endif()

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${UNIVERSELAN_EXTRA_BIN_FOLDER}")
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${UNIVERSELAN_EXTRA_BIN_FOLDER}")

add_subdirectory(Source)
