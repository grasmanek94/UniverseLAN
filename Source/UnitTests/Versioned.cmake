include(GoogleTest)

set(UNIVERSELAN_VERSIONED_UNIT_TESTS_DIR "${CMAKE_CURRENT_LIST_DIR}")

function(define_versioned_unit_tests GALAXY_VERSION GALAXY_VERSION_NUMBER)
  file(GLOB VERSIONED_SHARED_TESTS CONFIGURE_DEPENDS
    "${UNIVERSELAN_VERSIONED_UNIT_TESTS_DIR}/Shared/*Tests.cxx"
    "${UNIVERSELAN_VERSIONED_UNIT_TESTS_DIR}/Shared/Networking/*Tests.cxx"
  )

  add_executable(universelan-shared-${GALAXY_VERSION}-unit-tests ${VERSIONED_SHARED_TESTS})

  target_link_libraries(universelan-shared-${GALAXY_VERSION}-unit-tests PRIVATE
    universelan-common-shared-${GALAXY_VERSION}
    GTest::gtest_main
  )

  set_target_properties(universelan-shared-${GALAXY_VERSION}-unit-tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/tests/${GALAXY_VERSION_NUMBER}/${UNIVERSELAN_EXTRA_BIN_FOLDER}"
  )

  gtest_discover_tests(universelan-shared-${GALAXY_VERSION}-unit-tests)

  file(GLOB VERSIONED_CLIENT_TESTS CONFIGURE_DEPENDS
    "${UNIVERSELAN_VERSIONED_UNIT_TESTS_DIR}/Client/*Tests.cxx"
  )

  add_executable(universelan-client-${GALAXY_VERSION}-unit-tests ${VERSIONED_CLIENT_TESTS})

  target_link_libraries(universelan-client-${GALAXY_VERSION}-unit-tests PRIVATE
    universelan-lib-${GALAXY_VERSION}
    GTest::gtest_main
  )

  set_target_properties(universelan-client-${GALAXY_VERSION}-unit-tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/tests/${GALAXY_VERSION_NUMBER}/${UNIVERSELAN_EXTRA_BIN_FOLDER}"
  )

  gtest_discover_tests(universelan-client-${GALAXY_VERSION}-unit-tests)
endfunction()
