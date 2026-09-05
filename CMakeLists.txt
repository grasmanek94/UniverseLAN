cmake_minimum_required(VERSION 3.16)

######################################################################################

project( universelan )

set(CMAKE_CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_REQUIRED True)

enable_language( CXX )
enable_language( C )


if(NOT EXPERIMENTAL_FAST_BUILD)
  set(EXPERIMENTAL_FAST_BUILD "" CACHE STRING "[Experimental] [Needs manual file adjustment] Will try to perform an unity build (all .cxx files included in one .cxx file per project)")
endif()

if(EXPERIMENTAL_FAST_BUILD)
  set(CMAKE_UNITY_BUILD ON)
  set(CMAKE_UNITY_BUILD_BATCH_SIZE 100)
  add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/bigobj>)
endif()

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
else() # if (MSVC)
  set(CMAKE_POSITION_INDEPENDENT_CODE ON)
  set(UNIVERSELAN_EXTRA_BIN_FOLDER "${CMAKE_BUILD_TYPE}/")

  if(NOT GALAXY_ARCH)
    set(GALAXY_ARCH "" CACHE STRING "Architecture which is being compiled for (x86 or x64)")
  endif()

  message("Selected GALAXY_ARCH: '${GALAXY_ARCH}'")
  if(NOT "--${GALAXY_ARCH}--" STREQUAL "--x86--")
    if(NOT "--${GALAXY_ARCH}--" STREQUAL "--x64--")   
      message(FATAL_ERROR "Unknown GALAXY_ARCH, please define GALAXY_ARCH manually (x86 or x64)")
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
    add_compile_options(-m32)
    add_link_options(-m32)

    # here is the target environment located
    if(NOT DEFINED CMAKE_FIND_ROOT_PATH OR CMAKE_FIND_ROOT_PATH STREQUAL "")
      set(CMAKE_FIND_ROOT_PATH   /usr/i486-linux-gnu )
    endif()
  else()
    add_compile_options(-m64)
    add_link_options(-m64)
  endif()
endif()

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${UNIVERSELAN_EXTRA_BIN_FOLDER}")
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${UNIVERSELAN_EXTRA_BIN_FOLDER}")

SET(LIMIT_VERSIONS_SPECIFIED 0)
if(NOT LIMIT_VERSIONS)
  set(LIMIT_VERSIONS "" CACHE STRING "Comma separated list of versions to generate compilation units for. If not specified, projects for all supported versions will be generated")
else()
  STRING(REPLACE "," ";" LIMIT_VERSIONS "${LIMIT_VERSIONS}")
  SET(LIMIT_VERSIONS_SPECIFIED 1)
endif()

add_subdirectory(Source)
