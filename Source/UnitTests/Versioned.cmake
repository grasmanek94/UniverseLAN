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
    "${UNIVERSELAN_VERSIONED_UNIT_TESTS_DIR}/Shared/Versioned/SharedFileUtilsTests.cxx"
    "${UNIVERSELAN_VERSIONED_UNIT_TESTS_DIR}/Shared/Versioned/Networking/PingMessageTests.cxx"
    "${UNIVERSELAN_VERSIONED_UNIT_TESTS_DIR}/Shared/Versioned/Networking/KeyChallengeMessageTests.cxx"
    "${UNIVERSELAN_VERSIONED_UNIT_TESTS_DIR}/Shared/Versioned/Networking/OnlineStatusChangeMessageTests.cxx"
    "${UNIVERSELAN_VERSIONED_UNIT_TESTS_DIR}/Shared/Versioned/Networking/JoinLobbyMessageTests.cxx"
    "${UNIVERSELAN_VERSIONED_UNIT_TESTS_DIR}/Shared/Versioned/Networking/LeaveLobbyMessageTests.cxx"
    "${UNIVERSELAN_VERSIONED_UNIT_TESTS_DIR}/Shared/Versioned/Networking/SetLobbyJoinableMessageTests.cxx"
    "${UNIVERSELAN_VERSIONED_UNIT_TESTS_DIR}/Shared/Versioned/Networking/SetUserDataMessageTests.cxx"
    "${UNIVERSELAN_VERSIONED_UNIT_TESTS_DIR}/Shared/Versioned/Networking/SetLobbyDataMessageTests.cxx"
    "${UNIVERSELAN_VERSIONED_UNIT_TESTS_DIR}/Shared/Versioned/Networking/SetLobbyMemberDataMessageTests.cxx"
    "${UNIVERSELAN_VERSIONED_UNIT_TESTS_DIR}/Shared/Versioned/Networking/RichPresenceChangeMessageTests.cxx"
    "${UNIVERSELAN_VERSIONED_UNIT_TESTS_DIR}/Shared/Versioned/Networking/SetLobbyTypeMessageTests.cxx"
    "${UNIVERSELAN_VERSIONED_UNIT_TESTS_DIR}/Shared/Versioned/Networking/SetLobbyMaxMembersMessageTests.cxx"
    "${UNIVERSELAN_VERSIONED_UNIT_TESTS_DIR}/Shared/Versioned/Networking/LobbyOwnerChangeMessageTests.cxx"
    "${UNIVERSELAN_VERSIONED_UNIT_TESTS_DIR}/Shared/Versioned/Networking/LobbyMemberStateChangeMessageTests.cxx"
    "${UNIVERSELAN_VERSIONED_UNIT_TESTS_DIR}/Shared/Versioned/Networking/InvitationMessageTests.cxx"
    "${UNIVERSELAN_VERSIONED_UNIT_TESTS_DIR}/Shared/Versioned/Networking/RequestChatRoomWithUserMessageTests.cxx"
    "${UNIVERSELAN_VERSIONED_UNIT_TESTS_DIR}/Shared/Versioned/Networking/RequestChatRoomMessagesMessageTests.cxx"
    "${UNIVERSELAN_VERSIONED_UNIT_TESTS_DIR}/Shared/Versioned/Networking/RequestLobbyListMessageTests.cxx"
    "${UNIVERSELAN_VERSIONED_UNIT_TESTS_DIR}/Shared/Versioned/Networking/SendToLobbyMessageTests.cxx"
    "${UNIVERSELAN_VERSIONED_UNIT_TESTS_DIR}/Shared/Versioned/Networking/SendToChatRoomMessageTests.cxx"
    "${UNIVERSELAN_VERSIONED_UNIT_TESTS_DIR}/Shared/Versioned/Networking/UserHelloDataMessageTests.cxx"
    "${UNIVERSELAN_VERSIONED_UNIT_TESTS_DIR}/Shared/Versioned/Networking/RequestSpecificUserDataMessageTests.cxx"
    "${UNIVERSELAN_VERSIONED_UNIT_TESTS_DIR}/Shared/Versioned/Networking/RequestLobbyDataMessageTests.cxx"
    "${UNIVERSELAN_VERSIONED_UNIT_TESTS_DIR}/Shared/Versioned/Networking/FileRequestMessageTests.cxx"
    "${UNIVERSELAN_VERSIONED_UNIT_TESTS_DIR}/Shared/Versioned/Networking/FileShareMessageTests.cxx"
    "${UNIVERSELAN_VERSIONED_UNIT_TESTS_DIR}/Shared/Versioned/Networking/FileShareResponseMessageTests.cxx"
    "${UNIVERSELAN_VERSIONED_UNIT_TESTS_DIR}/Shared/Versioned/Networking/P2PNetworkPacketMessageTests.cxx"
    "${UNIVERSELAN_VERSIONED_UNIT_TESTS_DIR}/Shared/Versioned/Networking/P2PServerNetworkPacketMessageTests.cxx"
    "${UNIVERSELAN_VERSIONED_UNIT_TESTS_DIR}/Shared/Versioned/Networking/CreateLobbyMessageTests.cxx"
    "${UNIVERSELAN_VERSIONED_UNIT_TESTS_DIR}/Shared/Versioned/Networking/CreateLobbyResponseMessageTests.cxx"
  )

  target_link_libraries(universelan-shared-${GALAXY_VERSION}-unit-tests PRIVATE
    universelan-common-shared-${GALAXY_VERSION}
    GTest::gtest_main
  )

  set_target_properties(universelan-shared-${GALAXY_VERSION}-unit-tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/tests/${GALAXY_VERSION_NUMBER}/${UNIVERSELAN_EXTRA_BIN_FOLDER}"
  )

  gtest_discover_tests(universelan-shared-${GALAXY_VERSION}-unit-tests)

  add_executable(universelan-client-${GALAXY_VERSION}-unit-tests
    "${UNIVERSELAN_VERSIONED_UNIT_TESTS_DIR}/Client/Versioned/ErrorsTests.cxx"
  )

  target_link_libraries(universelan-client-${GALAXY_VERSION}-unit-tests PRIVATE
    universelan-lib-${GALAXY_VERSION}
    GTest::gtest_main
  )

  set_target_properties(universelan-client-${GALAXY_VERSION}-unit-tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/tests/${GALAXY_VERSION_NUMBER}/${UNIVERSELAN_EXTRA_BIN_FOLDER}"
  )

  gtest_discover_tests(universelan-client-${GALAXY_VERSION}-unit-tests)
endfunction()
