cmake_minimum_required(VERSION 3.12)

set(UNIVERSELAN_DLL_CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

include(determine_galaxy_version_feature_definitions.cmake)
 
function(add_version_definitions_to TARGET)
  string(REPLACE "." "" GALAXY_VERSION_DEF ${GALAXY_VERSION})
  string(REPLACE "x64-" "" GALAXY_VERSION_DEF ${GALAXY_VERSION_DEF})
  string(REPLACE "x86-" "" GALAXY_VERSION_DEF ${GALAXY_VERSION_DEF})

  string(REPLACE "-" " " GALAXY_VERSION_DEF_LIST ${GALAXY_VERSION})
  string(REPLACE "x" ""  GALAXY_VERSION_DEF_LIST ${GALAXY_VERSION_DEF_LIST})
  string(REPLACE "." " " GALAXY_VERSION_DEF_LIST ${GALAXY_VERSION_DEF_LIST})

  separate_arguments(GALAXY_VERSION_DEF_LIST)
  list (GET GALAXY_VERSION_DEF_LIST 0 GALAXY_VERSION_PLATFORM)
  list (GET GALAXY_VERSION_DEF_LIST 1 GALAXY_VERSION_MAJOR)
  list (GET GALAXY_VERSION_DEF_LIST 2 GALAXY_VERSION_MINOR)
  list (GET GALAXY_VERSION_DEF_LIST 3 GALAXY_VERSION_PATCH)

  if("${GALAXY_VERSION_MAJOR}" STREQUAL "0")
    string(SUBSTRING "${GALAXY_VERSION_DEF}" 1 -1 GALAXY_VERSION_DEF)
  endif()

  target_compile_definitions(${TARGET} PUBLIC 
    "GALAXY_VERSION_PLATFORM=${GALAXY_VERSION_PLATFORM}"
    "GALAXY_VERSION_MAJOR=${GALAXY_VERSION_MAJOR}"
    "GALAXY_VERSION_MINOR=${GALAXY_VERSION_MINOR}"
    "GALAXY_VERSION_PATCH=${GALAXY_VERSION_PATCH}"
    "GALAXY_VERSION=${GALAXY_VERSION_DEF}"
# Bug in MSVC, causes warnings
#    "IS_GALAXY_VERSION_GE(MAJOR,MINOR,PATCH)=(((GALAXY_VERSION_MAJOR)>(MAJOR))||(((GALAXY_VERSION_MAJOR)==(MAJOR))&&((GALAXY_VERSION_MINOR)>(MINOR)))||(((GALAXY_VERSION_MAJOR)==(MAJOR))&&((GALAXY_VERSION_MINOR)==(MINOR))&&((GALAXY_VERSION_PATCH)>=(PATCH))))"
  )

  add_feature_definitions_to_target(${TARGET} ${GALAXY_VERSION_MAJOR} ${GALAXY_VERSION_MINOR} ${GALAXY_VERSION_PATCH})
endfunction()

function(prep_version_rc PROJECT_TARGET UVLAN_COMPONENT UVLAN_OriginalFilename RC_FILENAME)
  SET(OUT_VERSION_RC_FILE ${UNIVERSELAN_DLL_CMAKE_CURRENT_SOURCE_DIR}/${GALAXY_VERSION_NUMBER}/${GALAXY_ARCH}/${RC_FILENAME}_versioninfo.rc)
  configure_file(${IN_VERSION_RC_FILE} ${OUT_VERSION_RC_FILE} @ONLY)
  target_sources(${PROJECT_TARGET} PRIVATE ${OUT_VERSION_RC_FILE})
endfunction()

function(add_version_rc)
  string(REPLACE "." "" GALAXY_VERSION_DEF ${GALAXY_VERSION})
  string(REPLACE "x64-" "" GALAXY_VERSION_DEF ${GALAXY_VERSION_DEF})
  string(REPLACE "x86-" "" GALAXY_VERSION_DEF ${GALAXY_VERSION_DEF})

  string(REPLACE "-" " " GALAXY_VERSION_DEF_LIST ${GALAXY_VERSION})
  string(REPLACE "x" ""  GALAXY_VERSION_DEF_LIST ${GALAXY_VERSION_DEF_LIST})
  string(REPLACE "." " " GALAXY_VERSION_DEF_LIST ${GALAXY_VERSION_DEF_LIST})

  separate_arguments(GALAXY_VERSION_DEF_LIST)
  list (GET GALAXY_VERSION_DEF_LIST 0 GALAXY_VERSION_PLATFORM)
  list (GET GALAXY_VERSION_DEF_LIST 1 GALAXY_VERSION_MAJOR)
  list (GET GALAXY_VERSION_DEF_LIST 2 GALAXY_VERSION_MINOR)
  list (GET GALAXY_VERSION_DEF_LIST 3 GALAXY_VERSION_PATCH)

  if("${GALAXY_VERSION_MAJOR}" STREQUAL "0")
    string(SUBSTRING "${GALAXY_VERSION_DEF}" 1 -1 GALAXY_VERSION_DEF)
  endif()

  string(TIMESTAMP PROJECT_CURRENT_YEAR "%Y")

  SET(IN_VERSION_RC_FILE ${UNIVERSELAN_DLL_CMAKE_CURRENT_SOURCE_DIR}/versioninfo.rc.cmake.in)

  prep_version_rc(universelan-client-${GALAXY_VERSION} "Client" "Galaxy-${GALAXY_VERSION}.dll" "client")
  prep_version_rc(universelan-server-${GALAXY_VERSION} "Server" "UniverseLANServer-${GALAXY_VERSION}.exe" "server")
  if(BUILD_INTERCEPTOR)
    prep_version_rc(universelan-interceptor-${GALAXY_VERSION} "Galaxy SDK Call Logger" "Galaxy-${GALAXY_VERSION}-interceptor.dll" "interceptor")
  endif()

endfunction()

function(define_projects_for_version)
  message("-- Adding Version: ${GALAXY_VERSION}")

  define_galaxy(${GALAXY_VERSION} ${UNIVERSELAN_SDK_INCL_DIR})
  define_shared(${GALAXY_VERSION})
  define_client(${GALAXY_VERSION})
  if(BUILD_INTERCEPTOR)
    define_interception_logger(${GALAXY_VERSION})
  endif()

  define_server(${GALAXY_VERSION} ${GALAXY_VERSION_NUMBER} "${ARCH_ADDITION}")
  
  if(BUILD_TEST_CASES)
    define_unet_library(${GALAXY_VERSION} ${GALAXY_VERSION_NUMBER} "${ARCH_ADDITION}")
  endif()
endfunction()

function(add_universelan_executables GALAXY_VERSION_NUMBER)
  set(GALAXY_VERSION "${GALAXY_ARCH}-${GALAXY_VERSION_NUMBER}")
  set(MODULE_DEFINITION_FILE ${UNIVERSELAN_DLL_CMAKE_CURRENT_SOURCE_DIR}/${GALAXY_VERSION_NUMBER}/${GALAXY_ARCH}/UniverseLAN.def)
  set(DLL_FILE ${UNIVERSELAN_DLL_CMAKE_CURRENT_SOURCE_DIR}/${GALAXY_VERSION_NUMBER}/Dll.cxx)
  set(FACTORY_FILE ${UNIVERSELAN_DLL_CMAKE_CURRENT_SOURCE_DIR}/${GALAXY_VERSION_NUMBER}/Factory.cxx)

  set(UNIVERSELAN_OUT_TYPE "DLL")
  set(UNIVERSELAN_SOURCE_CLIENT "${DLL_FILE}")

  set(UNIVERSELAN_SDK_INCL_DIR "${UNIVERSELAN_DLL_CMAKE_CURRENT_SOURCE_DIR}/${GALAXY_VERSION_NUMBER}/")

  if(NOT EXISTS "${DLL_FILE}")
    # Switch to FACTORY type if this is not a DLL type
    set(UNIVERSELAN_OUT_TYPE "FACTORY")
    set(UNIVERSELAN_SOURCE_CLIENT "${FACTORY_FILE}")
  endif()

  if(NOT EXISTS "${MODULE_DEFINITION_FILE}")
    return()
  endif()

  set(ARCH_ADDITION ${GALAXY_ARCH})
  string(REPLACE "x64" "64" ARCH_ADDITION ${ARCH_ADDITION})
  string(REPLACE "x86" "" ARCH_ADDITION ${ARCH_ADDITION})

  define_projects_for_version()

  # some SDK versions use REDGalaxy instead of Galaxy for lib name
  get_property(GALAXY_BUILD_FEATURE_HAS_RED_PREFIX GLOBAL PROPERTY "GALAXY_${GALAXY_VERSION_NUMBER}_BUILD_FEATURE_HAS_RED_PREFIX")
  if(GALAXY_BUILD_FEATURE_HAS_RED_PREFIX)
    set(MAYBE_RED_GALAXY_PREFIX "RED")
  else()
    set(MAYBE_RED_GALAXY_PREFIX "")
  endif()

  # Create the .DLL / Shared library
  add_library(universelan-client-${GALAXY_VERSION} SHARED "${UNIVERSELAN_SOURCE_CLIENT}" "${MODULE_DEFINITION_FILE}" )
  target_include_directories(universelan-client-${GALAXY_VERSION} PUBLIC "${UNIVERSELAN_SDK_INCL_DIR}")
  target_compile_definitions(universelan-client-${GALAXY_VERSION} PUBLIC "CLIENT_${UNIVERSELAN_OUT_TYPE}")
  target_link_libraries(universelan-client-${GALAXY_VERSION} PUBLIC universelan-lib-${GALAXY_VERSION})
  set_target_properties(universelan-client-${GALAXY_VERSION} PROPERTIES 
    OUTPUT_NAME "${MAYBE_RED_GALAXY_PREFIX}Galaxy${ARCH_ADDITION}"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${GALAXY_VERSION_NUMBER}/${UNIVERSELAN_EXTRA_BIN_FOLDER}"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${GALAXY_VERSION_NUMBER}/${UNIVERSELAN_EXTRA_BIN_FOLDER}"
  )

  if(BUILD_INTERCEPTOR)
    # Create SDK call interceptor / logger .DLL / Shared library
    add_library(universelan-interceptor-${GALAXY_VERSION} SHARED "${UNIVERSELAN_SOURCE_CLIENT}" "${MODULE_DEFINITION_FILE}")
    target_include_directories(universelan-interceptor-${GALAXY_VERSION} PUBLIC "${UNIVERSELAN_SDK_INCL_DIR}")
    target_compile_definitions(universelan-interceptor-${GALAXY_VERSION} PUBLIC "INTERCEPTOR_${UNIVERSELAN_OUT_TYPE}")
    target_link_libraries(universelan-interceptor-${GALAXY_VERSION} PUBLIC universelan-interception-logger-lib-${GALAXY_VERSION} )
    set_target_properties(universelan-interceptor-${GALAXY_VERSION} PROPERTIES 
      OUTPUT_NAME "${MAYBE_RED_GALAXY_PREFIX}GalaxyInterceptor${ARCH_ADDITION}"
      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${GALAXY_VERSION_NUMBER}/${UNIVERSELAN_EXTRA_BIN_FOLDER}"
      LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${GALAXY_VERSION_NUMBER}/${UNIVERSELAN_EXTRA_BIN_FOLDER}"
    )
    if(NOT MSVC)
      target_link_options(universelan-interceptor-${GALAXY_VERSION} PRIVATE -static-libgcc -static-libstdc++)
    endif()
  endif()

  if(NOT MSVC)
    target_link_options(universelan-client-${GALAXY_VERSION} PRIVATE -static-libgcc -static-libstdc++)
  endif()

  # add version.rc
  add_version_rc()

  file(COPY "${CMAKE_SOURCE_DIR}/Config/" DESTINATION "${CMAKE_SOURCE_DIR}/bin/${GALAXY_VERSION_NUMBER}/Debug/")
  file(COPY "${CMAKE_SOURCE_DIR}/Config/" DESTINATION "${CMAKE_SOURCE_DIR}/bin/${GALAXY_VERSION_NUMBER}/Release/")

endfunction()

MACRO(SUBDIRLIST result curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
      LIST(APPEND dirlist ${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()

SUBDIRLIST(SUBDIRS ${UNIVERSELAN_DLL_CMAKE_CURRENT_SOURCE_DIR})

SET(PROJECT_GALAXY_VERSION_NUMBER_LIST "") # variable which holds succesfully added versions

FOREACH(GALAXY_VERSION_NUMBER ${SUBDIRS})
  set(TOTAL_PATH "${UNIVERSELAN_DLL_CMAKE_CURRENT_SOURCE_DIR}/${GALAXY_VERSION_NUMBER}/${GALAXY_ARCH}")
  file(RELATIVE_PATH TOTAL_PATH_REL "${PROJECT_SOURCE_DIR}" "${TOTAL_PATH}/CMakeLists.txt")
  if(EXISTS "${TOTAL_PATH}/CMakeLists.txt")
    if(NOT LIMIT_VERSIONS_SPECIFIED OR "${GALAXY_VERSION_NUMBER}" IN_LIST LIMIT_VERSIONS)
      list(APPEND PROJECT_GALAXY_VERSION_NUMBER_LIST "${GALAXY_VERSION_NUMBER}")
      add_subdirectory(${TOTAL_PATH})
    else()
      message("-- Warning: Version '${GALAXY_ARCH}-${GALAXY_VERSION_NUMBER}' is not on inclusion list")
    endif()
  else()
    message("-- Warning: Version '${GALAXY_ARCH}-${GALAXY_VERSION_NUMBER}' not added because '${TOTAL_PATH_REL}' does not exist. Ignore if deliberate choice.")
  endif()
ENDFOREACH()

set_property(GLOBAL PROPERTY PROJECT_GALAXY_VERSION_NUMBER_LIST "${PROJECT_GALAXY_VERSION_NUMBER_LIST}")
