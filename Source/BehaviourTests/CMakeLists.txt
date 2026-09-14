cmake_minimum_required(VERSION 3.16)

option(ENABLE_UNIVERSELAN_GOG_BEHAVIOUR_TESTS "Register opt-in official-GOG behaviour scenarios" OFF)

set(UNIVERSELAN_BEHAVIOUR_TEST_VERSION "1.152.11")
set(UNIVERSELAN_BEHAVIOUR_TEST_ARCH "x64")
set(UNIVERSELAN_BEHAVIOUR_TEST_CREDENTIALS "${CMAKE_SOURCE_DIR}/Source/TestCommon/credentials.cmake")
set(UNIVERSELAN_BEHAVIOUR_TEST_CREDENTIALS_AVAILABLE OFF)
if(EXISTS "${UNIVERSELAN_BEHAVIOUR_TEST_CREDENTIALS}")
  include("${UNIVERSELAN_BEHAVIOUR_TEST_CREDENTIALS}")
  if(DEFINED GALAXY_SDK_USER_CREDENTIALS_USER1_NAME
      AND DEFINED GALAXY_SDK_USER_CREDENTIALS_USER1_PASSWORD
      AND DEFINED GALAXY_SDK_USER_CREDENTIALS_USER2_NAME
       AND DEFINED GALAXY_SDK_USER_CREDENTIALS_USER2_PASSWORD
       AND DEFINED GALAXY_SDK_CLIENT_ID
       AND DEFINED GALAXY_SDK_CLIENT_SECRET
       AND NOT GALAXY_SDK_USER_CREDENTIALS_USER1_NAME STREQUAL ""
       AND NOT GALAXY_SDK_USER_CREDENTIALS_USER1_PASSWORD STREQUAL ""
       AND NOT GALAXY_SDK_USER_CREDENTIALS_USER2_NAME STREQUAL ""
       AND NOT GALAXY_SDK_USER_CREDENTIALS_USER2_PASSWORD STREQUAL ""
       AND NOT GALAXY_SDK_CLIENT_ID STREQUAL ""
       AND NOT GALAXY_SDK_CLIENT_SECRET STREQUAL "")
    set(UNIVERSELAN_BEHAVIOUR_TEST_CREDENTIALS_AVAILABLE ON)
  endif()
endif()

if(UNIVERSELAN_BEHAVIOUR_TEST_CREDENTIALS_AVAILABLE)
  foreach(credential IN ITEMS
      GALAXY_SDK_USER_CREDENTIALS_USER1_NAME
      GALAXY_SDK_USER_CREDENTIALS_USER1_PASSWORD
      GALAXY_SDK_USER_CREDENTIALS_USER2_NAME
      GALAXY_SDK_USER_CREDENTIALS_USER2_PASSWORD
      GALAXY_SDK_CLIENT_ID
      GALAXY_SDK_CLIENT_SECRET)
    set(UNIVERSELAN_BEHAVIOUR_TEST_${credential} "${${credential}}")
    string(REPLACE "\\" "\\\\" UNIVERSELAN_BEHAVIOUR_TEST_${credential} "${UNIVERSELAN_BEHAVIOUR_TEST_${credential}}")
    string(REPLACE "\"" "\\\"" UNIVERSELAN_BEHAVIOUR_TEST_${credential} "${UNIVERSELAN_BEHAVIOUR_TEST_${credential}}")
  endforeach()
  set(UNIVERSELAN_BEHAVIOUR_TEST_CREDENTIALS_DEFINE 1)
else()
  set(UNIVERSELAN_BEHAVIOUR_TEST_CREDENTIALS_DEFINE 0)
  foreach(credential IN ITEMS
      GALAXY_SDK_USER_CREDENTIALS_USER1_NAME
      GALAXY_SDK_USER_CREDENTIALS_USER1_PASSWORD
      GALAXY_SDK_USER_CREDENTIALS_USER2_NAME
      GALAXY_SDK_USER_CREDENTIALS_USER2_PASSWORD
      GALAXY_SDK_CLIENT_ID
      GALAXY_SDK_CLIENT_SECRET)
    set(UNIVERSELAN_BEHAVIOUR_TEST_${credential} "")
  endforeach()
  message(STATUS "BehaviourTests official-GOG preflight: ignored credentials are unavailable")
endif()
configure_file(Host/Credentials.hxx.in "${CMAKE_CURRENT_BINARY_DIR}/BehaviourTestCredentials.hxx" @ONLY)

if(NOT GALAXY_ARCH STREQUAL UNIVERSELAN_BEHAVIOUR_TEST_ARCH)
  message(STATUS "BehaviourTests support ${UNIVERSELAN_BEHAVIOUR_TEST_ARCH} only; framework targets are unavailable for ${GALAXY_ARCH}")
  return()
endif()

set(UNIVERSELAN_BEHAVIOUR_TEST_VERSION_KEY "${UNIVERSELAN_BEHAVIOUR_TEST_ARCH}-${UNIVERSELAN_BEHAVIOUR_TEST_VERSION}")
set(UNIVERSELAN_BEHAVIOUR_TEST_CLIENT "universelan-client-${UNIVERSELAN_BEHAVIOUR_TEST_VERSION_KEY}")
set(UNIVERSELAN_BEHAVIOUR_TEST_SERVER "universelan-server-${UNIVERSELAN_BEHAVIOUR_TEST_VERSION_KEY}")
set(UNIVERSELAN_BEHAVIOUR_TEST_GOG_DIR "${CMAKE_SOURCE_DIR}/Source/DLLs/${UNIVERSELAN_BEHAVIOUR_TEST_VERSION}/gog")
set(UNIVERSELAN_BEHAVIOUR_TEST_GOG_LIB "${UNIVERSELAN_BEHAVIOUR_TEST_GOG_DIR}/Galaxy64.lib")
set(UNIVERSELAN_BEHAVIOUR_TEST_GOG_DLL "${UNIVERSELAN_BEHAVIOUR_TEST_GOG_DIR}/Galaxy64.dll")
set(UNIVERSELAN_BEHAVIOUR_TEST_GOG_PEER_DLL "${UNIVERSELAN_BEHAVIOUR_TEST_GOG_DIR}/GalaxyPeer64.dll")

if(NOT TARGET ${UNIVERSELAN_BEHAVIOUR_TEST_CLIENT} OR NOT TARGET ${UNIVERSELAN_BEHAVIOUR_TEST_SERVER})
  message(STATUS "BehaviourTests unavailable: UniverseLAN ${UNIVERSELAN_BEHAVIOUR_TEST_VERSION_KEY} client/server targets were not selected")
  return()
endif()

add_library(universelan-behaviour-test-common STATIC Common/Trace.cxx)
target_include_directories(universelan-behaviour-test-common PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

function(add_universelan_behaviour_host target)
  add_executable(${target} Host/Main.cxx)
  target_include_directories(${target} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_BINARY_DIR}"
    "${CMAKE_SOURCE_DIR}/Source/DLLs/${UNIVERSELAN_BEHAVIOUR_TEST_VERSION}")
  target_link_libraries(${target} PRIVATE universelan-behaviour-test-common ${ARGN})
  set(GALAXY_VERSION "${UNIVERSELAN_BEHAVIOUR_TEST_VERSION_KEY}")
  add_version_definitions_to(${target})
  target_compile_definitions(${target} PRIVATE
    "UNIVERSELAN_BEHAVIOUR_TEST_VERSION=\"${UNIVERSELAN_BEHAVIOUR_TEST_VERSION}\""
    "UNIVERSELAN_BEHAVIOUR_TEST_ARCH=\"${UNIVERSELAN_BEHAVIOUR_TEST_ARCH}\"")
endfunction()

add_universelan_behaviour_host(universelan-behaviour-host-universelan-${UNIVERSELAN_BEHAVIOUR_TEST_VERSION_KEY}
  ${UNIVERSELAN_BEHAVIOUR_TEST_CLIENT})

set(UNIVERSELAN_BEHAVIOUR_TEST_GOG_ARTIFACTS_AVAILABLE OFF)
if(EXISTS "${UNIVERSELAN_BEHAVIOUR_TEST_GOG_LIB}" AND EXISTS "${UNIVERSELAN_BEHAVIOUR_TEST_GOG_DLL}" AND EXISTS "${UNIVERSELAN_BEHAVIOUR_TEST_GOG_PEER_DLL}")
  set(UNIVERSELAN_BEHAVIOUR_TEST_GOG_ARTIFACTS_AVAILABLE ON)
  add_universelan_behaviour_host(universelan-behaviour-host-gog-${UNIVERSELAN_BEHAVIOUR_TEST_VERSION_KEY}
    "${UNIVERSELAN_BEHAVIOUR_TEST_GOG_LIB}")
else()
  message(STATUS "BehaviourTests official-GOG host unavailable: matching 1.152.11 x64 import/runtime artifacts are missing")
endif()

add_executable(universelan-behaviour-runner-${UNIVERSELAN_BEHAVIOUR_TEST_VERSION_KEY} Runner/Main.cxx)
target_include_directories(universelan-behaviour-runner-${UNIVERSELAN_BEHAVIOUR_TEST_VERSION_KEY} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(universelan-behaviour-runner-${UNIVERSELAN_BEHAVIOUR_TEST_VERSION_KEY} PRIVATE universelan-behaviour-test-common json)
target_compile_definitions(universelan-behaviour-runner-${UNIVERSELAN_BEHAVIOUR_TEST_VERSION_KEY} PRIVATE
  "UNIVERSELAN_BEHAVIOUR_TEST_VERSION=\"${UNIVERSELAN_BEHAVIOUR_TEST_VERSION}\""
  "UNIVERSELAN_BEHAVIOUR_TEST_ARCH=\"${UNIVERSELAN_BEHAVIOUR_TEST_ARCH}\"")

add_dependencies(universelan-behaviour-runner-${UNIVERSELAN_BEHAVIOUR_TEST_VERSION_KEY}
  universelan-behaviour-host-universelan-${UNIVERSELAN_BEHAVIOUR_TEST_VERSION_KEY}
  ${UNIVERSELAN_BEHAVIOUR_TEST_SERVER})
if(UNIVERSELAN_BEHAVIOUR_TEST_GOG_ARTIFACTS_AVAILABLE)
  add_dependencies(universelan-behaviour-runner-${UNIVERSELAN_BEHAVIOUR_TEST_VERSION_KEY}
    universelan-behaviour-host-gog-${UNIVERSELAN_BEHAVIOUR_TEST_VERSION_KEY})
endif()

function(add_universelan_gog_behaviour_test scenario scenario_directory manifest scenario_label)
  add_test(NAME "universelan-behaviour-${scenario}-${UNIVERSELAN_BEHAVIOUR_TEST_VERSION_KEY}"
    COMMAND $<TARGET_FILE:universelan-behaviour-runner-${UNIVERSELAN_BEHAVIOUR_TEST_VERSION_KEY}>
      --manifest "${CMAKE_CURRENT_SOURCE_DIR}/Scenarios/${scenario_directory}/${manifest}"
      --universelan-host $<TARGET_FILE:universelan-behaviour-host-universelan-${UNIVERSELAN_BEHAVIOUR_TEST_VERSION_KEY}>
      --gog-host $<TARGET_FILE:universelan-behaviour-host-gog-${UNIVERSELAN_BEHAVIOUR_TEST_VERSION_KEY}>
      --client-dll $<TARGET_FILE:${UNIVERSELAN_BEHAVIOUR_TEST_CLIENT}>
      --server $<TARGET_FILE:${UNIVERSELAN_BEHAVIOUR_TEST_SERVER}>
      --gog-runtime-dir "${UNIVERSELAN_BEHAVIOUR_TEST_GOG_DIR}")
  set_tests_properties("universelan-behaviour-${scenario}-${UNIVERSELAN_BEHAVIOUR_TEST_VERSION_KEY}" PROPERTIES
    TIMEOUT 60
    RUN_SERIAL TRUE
    RESOURCE_LOCK "universelan-behaviour-gog-accounts;universelan-system-network"
    LABELS "behavior;gog;${scenario_directory};${scenario_label}")
endfunction()

if(ENABLE_UNIVERSELAN_GOG_BEHAVIOUR_TESTS AND UNIVERSELAN_BEHAVIOUR_TEST_CREDENTIALS_AVAILABLE AND UNIVERSELAN_BEHAVIOUR_TEST_GOG_ARTIFACTS_AVAILABLE)
  add_universelan_gog_behaviour_test("simple-initialize-and-sign-in" "Simple" "initialize-and-sign-in.json" "initialize-and-sign-in")
  add_universelan_gog_behaviour_test("simple-session-id-repeatability" "Simple" "session-id-repeatability.json" "session-id-repeatability")
  add_universelan_gog_behaviour_test("simple-gog-services-state" "Simple" "gog-services-state.json" "gog-services-state")
  add_universelan_gog_behaviour_test("simple-public-lobby-create-list-join-leave" "Simple" "public-lobby-create-list-join-leave.json" "public-lobby-create-list-join-leave")
  add_universelan_gog_behaviour_test("simple-public-lobby-not-joinable-behavior" "Simple" "public-lobby-not-joinable-behavior.json" "public-lobby-not-joinable-behavior")
  add_universelan_gog_behaviour_test("simple-public-lobby-full-join-failure" "Simple" "public-lobby-full-join-failure.json" "public-lobby-full-join-failure")
  add_universelan_gog_behaviour_test("simple-public-lobby-owner-close-lifecycle" "Simple" "public-lobby-owner-close-lifecycle.json" "public-lobby-owner-close-lifecycle")
  add_universelan_gog_behaviour_test("simple-public-lobby-owner-ownership-transition" "Simple" "public-lobby-owner-ownership-transition.json" "public-lobby-owner-ownership-transition")
  add_universelan_gog_behaviour_test("simple-public-lobby-data-propagation" "Simple" "public-lobby-data-propagation.json" "public-lobby-data-propagation")
  add_universelan_gog_behaviour_test("simple-chat-room-message-delivery" "Simple" "chat-room-message-delivery.json" "chat-room-message-delivery")
  add_universelan_gog_behaviour_test("simple-bidirectional-chat-room-message-delivery" "Simple" "bidirectional-chat-room-message-delivery.json" "bidirectional-chat-room-message-delivery")
  add_universelan_gog_behaviour_test("simple-friends-peer-information-retrieval" "Simple" "friends-peer-information-retrieval.json" "friends-peer-information-retrieval")
  add_universelan_gog_behaviour_test("simple-reliable-p2p-listener-peek" "Simple" "reliable-p2p-listener-peek.json" "reliable-p2p-listener-peek")
  add_universelan_gog_behaviour_test("simple-reliable-p2p-after-lobby-leave" "Simple" "reliable-p2p-after-lobby-leave.json" "reliable-p2p-after-lobby-leave")
  add_universelan_gog_behaviour_test("simple-bidirectional-reliable-p2p-listener-peek" "Simple" "bidirectional-reliable-p2p-listener-peek.json" "bidirectional-reliable-p2p-listener-peek")
  add_universelan_gog_behaviour_test("simple-bidirectional-unreliable-p2p-listener-peek" "Simple" "bidirectional-unreliable-p2p-listener-peek.json" "bidirectional-unreliable-p2p-listener-peek")
  add_universelan_gog_behaviour_test("simple-bidirectional-lobby-message-delivery" "Simple" "bidirectional-lobby-message-delivery.json" "bidirectional-lobby-message-delivery")
  add_universelan_gog_behaviour_test("simple-bidirectional-lobby-member-data-propagation" "Simple" "bidirectional-lobby-member-data-propagation.json" "bidirectional-lobby-member-data-propagation")
  add_universelan_gog_behaviour_test("advanced-multiple-lobby-membership-and-message-isolation" "Advanced" "multiple-lobby-membership-and-message-isolation.json" "multiple-lobby-membership-and-message-isolation")
elseif(ENABLE_UNIVERSELAN_GOG_BEHAVIOUR_TESTS)
  message(STATUS "BehaviourTests official-GOG scenario not registered: credentials or matching official runtime artifacts are unavailable")
else()
  message(STATUS "BehaviourTests official-GOG scenarios are not registered; set ENABLE_UNIVERSELAN_GOG_BEHAVIOUR_TESTS=ON after local preflight")
endif()
