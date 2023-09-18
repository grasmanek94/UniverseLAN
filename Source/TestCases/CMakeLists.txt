cmake_minimum_required(VERSION 3.12)

if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/credentials.cmake")
  message("Refusing to build tests without credentials.cmake")
  return()
endif()
message("-- Adding tests...")

include(credentials.cmake)

function(add_simple_test_case GALAXY_VERSION_NUMBER TEST_CASE_NAME)
  set(GALAXY_VERSION "${GALAXY_ARCH}-${GALAXY_VERSION_NUMBER}")

  set(ARCH_ADDITION ${GALAXY_ARCH})
  string(REPLACE "x64" "64" ARCH_ADDITION ${ARCH_ADDITION})
  string(REPLACE "x86" "" ARCH_ADDITION ${ARCH_ADDITION})

  # Create a simple DLL/SO host
  set(CURRENT_TEST_TARGET zz-testcase-${GALAXY_VERSION}-${TEST_CASE_NAME})
  set(CURRENT_TEST_OUTPUT "${CMAKE_SOURCE_DIR}/bin/tests/${GALAXY_VERSION_NUMBER}/${UNIVERSELAN_EXTRA_BIN_FOLDER}")
  set(CURRENT_TEST_REFERENCE_DIR "${GALAXY_DLL_VERSIONS_DIR}/${GALAXY_VERSION_NUMBER}/gog")

  add_executable(${CURRENT_TEST_TARGET} "TestCase_${TEST_CASE_NAME}.cxx" "TestCaseClientDetails.hxx")
  target_include_directories(${CURRENT_TEST_TARGET} PUBLIC ".")
  target_compile_definitions(${CURRENT_TEST_TARGET} PUBLIC 
    "TEST_CASE=1"
    "TEST_CASE_${TEST_CASE_NAME}=1"
    "GALAXY_SDK_USER_CREDENTIALS_USER1_NAME=\"${GALAXY_SDK_USER_CREDENTIALS_USER1_NAME}\"sv"
    "GALAXY_SDK_USER_CREDENTIALS_USER1_PASSWORD=\"${GALAXY_SDK_USER_CREDENTIALS_USER1_PASSWORD}\"sv"
    "GALAXY_SDK_USER_CREDENTIALS_USER2_NAME=\"${GALAXY_SDK_USER_CREDENTIALS_USER2_NAME}\"sv"
    "GALAXY_SDK_USER_CREDENTIALS_USER2_PASSWORD=\"${GALAXY_SDK_USER_CREDENTIALS_USER2_PASSWORD}\"sv"
    "GALAXY_SDK_CLIENT_ID=\"${GALAXY_SDK_CLIENT_ID}\""
    "GALAXY_SDK_CLIENT_SECRET=\"${GALAXY_SDK_CLIENT_SECRET}\""
  )

  # some SDK versions use REDGalaxy instead of Galaxy for lib name
  get_property(GALAXY_BUILD_FEATURE_HAS_RED_PREFIX GLOBAL PROPERTY "GALAXY_${GALAXY_VERSION_NUMBER}_BUILD_FEATURE_HAS_RED_PREFIX")
  if(GALAXY_BUILD_FEATURE_HAS_RED_PREFIX)
    set(MAYBE_RED_GALAXY_PREFIX "RED")
  else()
    set(MAYBE_RED_GALAXY_PREFIX "")
  endif()

  target_link_libraries(${CURRENT_TEST_TARGET} PUBLIC 
    universelan-magic_enum
    universelan-galaxy-${GALAXY_VERSION} 
    universelan-common-tracer
    universelan-common-version
    "${CURRENT_TEST_REFERENCE_DIR}/${MAYBE_RED_GALAXY_PREFIX}Galaxy${ARCH_ADDITION}.lib"
  )

  set_target_properties(${CURRENT_TEST_TARGET} PROPERTIES 
    OUTPUT_NAME "TestCase${ARCH_ADDITION}_${TEST_CASE_NAME}"
    RUNTIME_OUTPUT_DIRECTORY "${CURRENT_TEST_OUTPUT}"
    LIBRARY_OUTPUT_DIRECTORY "${CURRENT_TEST_OUTPUT}"
  )

  set_property(TARGET ${CURRENT_TEST_TARGET} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CURRENT_TEST_OUTPUT}/Debug")

  if(NOT MSVC)

    target_link_options(${CURRENT_TEST_TARGET} PRIVATE -static-libgcc -static-libstdc++)
    file(COPY "${CMAKE_SOURCE_DIR}/Config/" DESTINATION "${CURRENT_TEST_OUTPUT}")
    file(COPY "${CURRENT_TEST_REFERENCE_DIR}/lib${MAYBE_RED_GALAXY_PREFIX}Galaxy${ARCH_ADDITION}.so" DESTINATION "${CURRENT_TEST_OUTPUT}/Debug/")

  else()

    file(COPY "${CURRENT_TEST_REFERENCE_DIR}/${MAYBE_RED_GALAXY_PREFIX}Galaxy${ARCH_ADDITION}.dll" DESTINATION "${CURRENT_TEST_OUTPUT}/Debug/")
    file(COPY "${CURRENT_TEST_REFERENCE_DIR}/${MAYBE_RED_GALAXY_PREFIX}Galaxy${ARCH_ADDITION}.dll" DESTINATION "${CURRENT_TEST_OUTPUT}/Release/")

    file(COPY "${CMAKE_SOURCE_DIR}/Config/" DESTINATION "${CURRENT_TEST_OUTPUT}/Debug/")
    file(COPY "${CMAKE_SOURCE_DIR}/Config/" DESTINATION "${CURRENT_TEST_OUTPUT}/Release/")

  endif()

endfunction()

set(GALAXY_DLL_VERSIONS_DIR "${CMAKE_SOURCE_DIR}/Source/DLLs")
SUBDIRLIST(SUBDIRS "${GALAXY_DLL_VERSIONS_DIR}/")

file(GLOB test_cases "TestCase_*.cxx")
foreach(test_case_file ${test_cases})
  get_filename_component(test_case ${test_case_file} NAME_WE)
  string(REPLACE "TestCase_" "" test_case ${test_case})
  
  message("--- ${test_case}")

  FOREACH(GALAXY_VERSION_NUMBER ${SUBDIRS})
    set(TOTAL_PATH "${GALAXY_DLL_VERSIONS_DIR}/${GALAXY_VERSION_NUMBER}/${GALAXY_ARCH}")
    if(EXISTS "${TOTAL_PATH}/CMakeLists.txt")
      add_simple_test_case("${GALAXY_VERSION_NUMBER}" "${test_case}")
    endif()
  ENDFOREACH()
endforeach()
