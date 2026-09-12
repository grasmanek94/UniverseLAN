include(GoogleTest)

set(UNIVERSELAN_VERSIONED_UNIT_TESTS_DIR "${CMAKE_CURRENT_LIST_DIR}")

function(define_versioned_unit_tests GALAXY_VERSION GALAXY_VERSION_NUMBER)
  add_executable(universelan-shared-${GALAXY_VERSION}-unit-tests
    "${UNIVERSELAN_VERSIONED_UNIT_TESTS_DIR}/Shared/Versioned/DynamicReturnTests.cxx"
    "${UNIVERSELAN_VERSIONED_UNIT_TESTS_DIR}/Shared/Versioned/GalaxyIDTests.cxx"
    "${UNIVERSELAN_VERSIONED_UNIT_TESTS_DIR}/Shared/Versioned/GalaxyIDSerializationTests.cxx"
    "${UNIVERSELAN_VERSIONED_UNIT_TESTS_DIR}/Shared/Versioned/GalaxyUserDataTests.cxx"
    "${UNIVERSELAN_VERSIONED_UNIT_TESTS_DIR}/Shared/Versioned/ChatMessageTests.cxx"
    "${UNIVERSELAN_VERSIONED_UNIT_TESTS_DIR}/Shared/Versioned/ChatRoomTests.cxx"
    "${UNIVERSELAN_VERSIONED_UNIT_TESTS_DIR}/Shared/Versioned/ChatRoomManagerTests.cxx"
    "${UNIVERSELAN_VERSIONED_UNIT_TESTS_DIR}/Shared/Versioned/LobbyTests.cxx"
    "${UNIVERSELAN_VERSIONED_UNIT_TESTS_DIR}/Shared/Versioned/LobbyManagerTests.cxx"
  )

  target_link_libraries(universelan-shared-${GALAXY_VERSION}-unit-tests PRIVATE
    universelan-common-shared-${GALAXY_VERSION}
    GTest::gtest_main
  )

  set_target_properties(universelan-shared-${GALAXY_VERSION}-unit-tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/tests/${GALAXY_VERSION_NUMBER}/${UNIVERSELAN_EXTRA_BIN_FOLDER}"
  )

  gtest_discover_tests(universelan-shared-${GALAXY_VERSION}-unit-tests)
endfunction()
