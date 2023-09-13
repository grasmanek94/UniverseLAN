cmake_minimum_required(VERSION 3.12)

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
  list (GET GALAXY_VERSION_DEF_LIST 3 GALAXY_VERSION_PATCH_MAJOR)
  list (GET GALAXY_VERSION_DEF_LIST 4 GALAXY_VERSION_PATCH_MINOR)

  if("${GALAXY_VERSION_MAJOR}" STREQUAL "0")
    string(SUBSTRING "${GALAXY_VERSION_DEF}" 1 -1 GALAXY_VERSION_DEF)
  endif()

  target_compile_definitions(${TARGET} PUBLIC 
    "GALAXY_VERSION_PLATFORM=${GALAXY_VERSION_PLATFORM}"
    "GALAXY_VERSION_MAJOR=${GALAXY_VERSION_MAJOR}"
    "GALAXY_VERSION_MINOR=${GALAXY_VERSION_MINOR}"
    "GALAXY_VERSION_PATCH_MAJOR=${GALAXY_VERSION_PATCH_MAJOR}"
    "GALAXY_VERSION_PATCH_MINOR=${GALAXY_VERSION_PATCH_MINOR}"
    "GALAXY_VERSION=${GALAXY_VERSION_DEF}"
# Bug in MSVC, causes warnings
#    "IS_GALAXY_VERSION_GE(MAJOR,MINOR,PATCH)=(((GALAXY_VERSION_MAJOR)>(MAJOR))||(((GALAXY_VERSION_MAJOR)==(MAJOR))&&((GALAXY_VERSION_MINOR)>(MINOR)))||(((GALAXY_VERSION_MAJOR)==(MAJOR))&&((GALAXY_VERSION_MINOR)==(MINOR))&&((GALAXY_VERSION_PATCH_MAJOR)>=(PATCH))))"
  )

  add_feature_definitions_to_target(${TARGET} ${GALAXY_VERSION_MAJOR} ${GALAXY_VERSION_MINOR} ${GALAXY_VERSION_PATCH_MAJOR})

  string(TIMESTAMP PROJECT_CURRENT_YEAR "%Y")

  # ${CMAKE_CURRENT_SOURCE_DIR} is location of folder below (so version specific one)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../versioninfo.rc.cmake.in ${CMAKE_CURRENT_SOURCE_DIR}/versioninfo.rc @ONLY)
  target_sources(${TARGET} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/versioninfo.rc)
endfunction()

function(define_projects_for_version GALAXY_VERSION)
  message("-- Adding Version: ${GALAXY_VERSION}")

  define_galaxy(${GALAXY_VERSION})
  define_shared(${GALAXY_VERSION})
  define_client(${GALAXY_VERSION})
  define_server(${GALAXY_VERSION})
endfunction()

if (MSVC)
  if("${MSVC_C_ARCHITECTURE_ID}" STREQUAL "X86")

    add_subdirectory(x86-1.100.2.0) # Metal Slug 3
    add_subdirectory(x86-1.124.0.0) # RPSGame
#    add_subdirectory(x86-0.176.2.6) # AvP2000

  elseif("${MSVC_C_ARCHITECTURE_ID}" STREQUAL "x64")

    add_subdirectory(x64-1.121.2.0) # Aragami 2
    add_subdirectory(x64-1.124.0.0) # RPSGame
    add_subdirectory(x64-1.148.3.0) # RoboQuest
  endif()
endif()
