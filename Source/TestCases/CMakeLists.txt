cmake_minimum_required(VERSION 3.12)

if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/credentials.cmake")
  message("Refusing to build tests without credentials.cmake")
  return()
endif()
message("-- Adding tests...")

include(credentials.cmake)

function(add_simple_test_case GALAXY_VERSION_NUMBER TEST_CASE_NAME PREFIX)
  set(GALAXY_VERSION "${GALAXY_ARCH}-${GALAXY_VERSION_NUMBER}")

  set(ARCH_ADDITION ${GALAXY_ARCH})
  string(REPLACE "x64" "64" ARCH_ADDITION ${ARCH_ADDITION})
  string(REPLACE "x86" "" ARCH_ADDITION ${ARCH_ADDITION})

  # Create a simple DLL/SO host
  set(CURRENT_TEST_TARGET zz-testcase-${GALAXY_VERSION}-${TEST_CASE_NAME})
  set(CURRENT_TEST_OUTPUT "${CMAKE_SOURCE_DIR}/bin/tests/${GALAXY_VERSION_NUMBER}/${UNIVERSELAN_EXTRA_BIN_FOLDER}")
  set(CURRENT_TEST_REFERENCE_DIR "${GALAXY_DLL_VERSIONS_DIR}/${GALAXY_VERSION_NUMBER}/gog")

  file(GLOB_RECURSE TEST_CASES_HEADERS CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/Source/TestCases/Include/*.*")

  add_executable(${CURRENT_TEST_TARGET} "${PREFIX}${TEST_CASE_NAME}.cxx" ${TEST_CASES_HEADERS})
  target_include_directories(${CURRENT_TEST_TARGET} PUBLIC "." "Include/")
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
    file(COPY "${CMAKE_SOURCE_DIR}/ConfigDebug/" DESTINATION "${CURRENT_TEST_OUTPUT}")
    file(COPY "${CURRENT_TEST_REFERENCE_DIR}/lib${MAYBE_RED_GALAXY_PREFIX}Galaxy${ARCH_ADDITION}.so" DESTINATION "${CURRENT_TEST_OUTPUT}/Debug/")

  else()

    set(DLL_FILENAME "${MAYBE_RED_GALAXY_PREFIX}Galaxy${ARCH_ADDITION}.dll")
    if(EXISTS   "${CURRENT_TEST_REFERENCE_DIR}/${DLL_FILENAME}")    
 
      if(BUILD_INTERCEPTOR)
        set(DLL_OUT_DIR "gog/")
      else()
        set(DLL_OUT_DIR "")
      endif()

      file(COPY "${CURRENT_TEST_REFERENCE_DIR}/${DLL_FILENAME}" DESTINATION "${CURRENT_TEST_OUTPUT}/Debug/${DLL_OUT_DIR}")
      file(COPY "${CURRENT_TEST_REFERENCE_DIR}/${DLL_FILENAME}" DESTINATION "${CURRENT_TEST_OUTPUT}/Release/${DLL_OUT_DIR}")

      if(BUILD_INTERCEPTOR)
        file(RENAME "${CURRENT_TEST_OUTPUT}/Debug/${DLL_OUT_DIR}${DLL_FILENAME}" "${CURRENT_TEST_OUTPUT}/Debug/${DLL_OUT_DIR}Real${DLL_FILENAME}")
        file(RENAME "${CURRENT_TEST_OUTPUT}/Release/${DLL_OUT_DIR}${DLL_FILENAME}" "${CURRENT_TEST_OUTPUT}/Release/${DLL_OUT_DIR}Real${DLL_FILENAME}")
      endif()
    endif()

    set(PEER_FILENAME "GalaxyPeer${ARCH_ADDITION}.dll")
    if(EXISTS   "${CURRENT_TEST_REFERENCE_DIR}/${PEER_FILENAME}")
      file(COPY "${CURRENT_TEST_REFERENCE_DIR}/${PEER_FILENAME}" DESTINATION "${CURRENT_TEST_OUTPUT}/Debug/")
      file(COPY "${CURRENT_TEST_REFERENCE_DIR}/${PEER_FILENAME}" DESTINATION "${CURRENT_TEST_OUTPUT}/Release/")
    endif()

    file(COPY "${CMAKE_SOURCE_DIR}/ConfigDebug/" DESTINATION "${CURRENT_TEST_OUTPUT}/Debug/")
    file(COPY "${CMAKE_SOURCE_DIR}/Config/" DESTINATION "${CURRENT_TEST_OUTPUT}/Release/")

    if(BUILD_INTERCEPTOR)
      configure_file("${CMAKE_CURRENT_SOURCE_DIR}/batch/test_gog_user1.bat.in" "${CURRENT_TEST_OUTPUT}/Debug/test_gog_user1.bat" @ONLY)
      configure_file("${CMAKE_CURRENT_SOURCE_DIR}/batch/test_gog_user1.bat.in" "${CURRENT_TEST_OUTPUT}/Release/test_gog_user1.bat" @ONLY)
      configure_file("${CMAKE_CURRENT_SOURCE_DIR}/batch/test_gog_user2.bat.in" "${CURRENT_TEST_OUTPUT}/Debug/test_gog_user2.bat" @ONLY)
      configure_file("${CMAKE_CURRENT_SOURCE_DIR}/batch/test_gog_user2.bat.in" "${CURRENT_TEST_OUTPUT}/Release/test_gog_user2.bat" @ONLY)
    endif()
  endif()

  set(CURRENT_TEST_TARGET ${CURRENT_TEST_TARGET} PARENT_SCOPE)
  set(GALAXY_VERSION ${GALAXY_VERSION} PARENT_SCOPE)
endfunction()

set(GALAXY_DLL_VERSIONS_DIR "${CMAKE_SOURCE_DIR}/Source/DLLs")
get_property(PROJECT_GALAXY_VERSION_NUMBER_LIST GLOBAL PROPERTY PROJECT_GALAXY_VERSION_NUMBER_LIST)

function(add_test_cases)
  file(GLOB test_cases "Source/TestCase_*.cxx")
  foreach(test_case_file ${test_cases})
    get_filename_component(test_case ${test_case_file} NAME_WE)
    string(REPLACE "TestCase_" "" test_case ${test_case})
    
    message("--- ${test_case}")
  
    FOREACH(GALAXY_VERSION_NUMBER ${PROJECT_GALAXY_VERSION_NUMBER_LIST})
      #set(TOTAL_PATH "${GALAXY_DLL_VERSIONS_DIR}/${GALAXY_VERSION_NUMBER}/${GALAXY_ARCH}")
      #if(EXISTS "${TOTAL_PATH}/CMakeLists.txt")
  
      add_simple_test_case("${GALAXY_VERSION_NUMBER}" "${test_case}" "Source/TestCase_")
  
      #else()
      #  message("---- !${GALAXY_DLL_VERSIONS_DIR}/${GALAXY_VERSION_NUMBER}/${GALAXY_ARCH}")
      #endif()
    ENDFOREACH()
  endforeach()
  
  file(GLOB test_cases "Source-unet/TestCase_unet_*.cxx")
  foreach(test_case_file ${test_cases})
    get_filename_component(test_case ${test_case_file} NAME_WE)
    string(REPLACE "TestCase_" "" test_case ${test_case})
    
    message("--- ${test_case}")
  
    FOREACH(GALAXY_VERSION_NUMBER ${PROJECT_GALAXY_VERSION_NUMBER_LIST})
      add_simple_test_case("${GALAXY_VERSION_NUMBER}" "${test_case}"  "Source-unet/TestCase_")
      target_link_libraries(${CURRENT_TEST_TARGET} PUBLIC 
        unet-lib-${GALAXY_VERSION}
      )
    ENDFOREACH()
  endforeach()
endfunction()

add_test_cases()