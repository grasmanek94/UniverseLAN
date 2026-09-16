cmake_minimum_required(VERSION 3.16)

option(ENABLE_UNIVERSELAN_GOG_BEHAVIOUR_TESTS "Register opt-in official-GOG behaviour scenarios" OFF)

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
else()

add_library(universelan-behaviour-test-common STATIC Common/Trace.cxx)
target_include_directories(universelan-behaviour-test-common PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

set(UNIVERSELAN_BEHAVIOUR_TEST_GOG_PEER_OVERLAY "" CACHE PATH "Optional local GalaxyPeer64.dll file or directory staged over the official peer runtime")
if(NOT UNIVERSELAN_BEHAVIOUR_TEST_GOG_PEER_OVERLAY STREQUAL "")
  set(UNIVERSELAN_BEHAVIOUR_TEST_GOG_PEER_OVERLAY_FILE "${UNIVERSELAN_BEHAVIOUR_TEST_GOG_PEER_OVERLAY}")
  if(IS_DIRECTORY "${UNIVERSELAN_BEHAVIOUR_TEST_GOG_PEER_OVERLAY_FILE}")
    set(UNIVERSELAN_BEHAVIOUR_TEST_GOG_PEER_OVERLAY_FILE "${UNIVERSELAN_BEHAVIOUR_TEST_GOG_PEER_OVERLAY_FILE}/GalaxyPeer64.dll")
  endif()
  if(NOT EXISTS "${UNIVERSELAN_BEHAVIOUR_TEST_GOG_PEER_OVERLAY_FILE}")
    message(FATAL_ERROR "BehaviourTests GOG peer overlay must be a GalaxyPeer64.dll file or a directory containing it")
  endif()
endif()

function(get_universelan_behaviour_manifest_path output version scenario_directory manifest)
  set(${output} "${CMAKE_CURRENT_BINARY_DIR}/Scenarios/${version}/${scenario_directory}/${manifest}" PARENT_SCOPE)
endfunction()

function(generate_universelan_behaviour_manifest version scenario_directory manifest)
  set(source_manifest "${CMAKE_CURRENT_SOURCE_DIR}/Scenarios/${scenario_directory}/${manifest}")
  file(READ "${source_manifest}" manifest_content)
  string(REGEX MATCH "\"sdkVersion\"[ \t]*:[ \t]*\"[^\"]*\"" manifest_sdk_version "${manifest_content}")
  if(manifest_sdk_version STREQUAL "")
    message(FATAL_ERROR "BehaviourTests manifest ${source_manifest} has no sdkVersion field")
  endif()
  string(REGEX REPLACE "\"sdkVersion\"[ \t]*:[ \t]*\"[^\"]*\"" "\"sdkVersion\": \"${version}\"" manifest_content "${manifest_content}")
  get_universelan_behaviour_manifest_path(generated_manifest "${version}" "${scenario_directory}" "${manifest}")
  get_filename_component(generated_directory "${generated_manifest}" DIRECTORY)
  file(MAKE_DIRECTORY "${generated_directory}")
  file(WRITE "${generated_manifest}" "${manifest_content}")
endfunction()

set(UNIVERSELAN_BEHAVIOUR_TEST_GOG_SCENARIOS
  "simple-initialize-and-sign-in|Simple|initialize-and-sign-in.json|initialize-and-sign-in"
  "simple-session-id-repeatability|Simple|session-id-repeatability.json|session-id-repeatability"
  "simple-gog-services-state|Simple|gog-services-state.json|gog-services-state"
  "simple-stats-retrieve-self-callback|Simple|stats-retrieve-self-callback.json|stats-retrieve-self-callback"
  "simple-storage-downloaded-shared-file-count|Simple|storage-downloaded-shared-file-count.json|storage-downloaded-shared-file-count"
  "simple-current-game-language|Simple|current-game-language.json|current-game-language"
  "simple-public-lobby-create-list-join-leave|Simple|public-lobby-create-list-join-leave.json|public-lobby-create-list-join-leave"
  "simple-public-lobby-string-filtering|Simple|public-lobby-string-filtering.json|public-lobby-string-filtering"
  "simple-public-lobby-numerical-filtering|Simple|public-lobby-numerical-filtering.json|public-lobby-numerical-filtering"
  "simple-public-lobby-not-joinable-behavior|Simple|public-lobby-not-joinable-behavior.json|public-lobby-not-joinable-behavior"
  "simple-public-lobby-full-join-failure|Simple|public-lobby-full-join-failure.json|public-lobby-full-join-failure"
  "simple-public-lobby-owner-close-lifecycle|Simple|public-lobby-owner-close-lifecycle.json|public-lobby-owner-close-lifecycle"
  "simple-public-lobby-owner-ownership-transition|Simple|public-lobby-owner-ownership-transition.json|public-lobby-owner-ownership-transition"
  "simple-public-lobby-data-propagation|Simple|public-lobby-data-propagation.json|public-lobby-data-propagation"
  "simple-chat-room-message-delivery|Simple|chat-room-message-delivery.json|chat-room-message-delivery"
  "simple-bidirectional-chat-room-message-delivery|Simple|bidirectional-chat-room-message-delivery.json|bidirectional-chat-room-message-delivery"
  "simple-friends-peer-information-retrieval|Simple|friends-peer-information-retrieval.json|friends-peer-information-retrieval"
  "simple-reliable-p2p-listener-peek|Simple|reliable-p2p-listener-peek.json|reliable-p2p-listener-peek"
  "simple-reliable-p2p-after-lobby-leave|Simple|reliable-p2p-after-lobby-leave.json|reliable-p2p-after-lobby-leave"
  "simple-bidirectional-reliable-p2p-listener-peek|Simple|bidirectional-reliable-p2p-listener-peek.json|bidirectional-reliable-p2p-listener-peek"
  "simple-bidirectional-reliable-p2p-poll-read|Simple|bidirectional-reliable-p2p-poll-read.json|bidirectional-reliable-p2p-poll-read"
  "simple-bidirectional-unreliable-p2p-listener-peek|Simple|bidirectional-unreliable-p2p-listener-peek.json|bidirectional-unreliable-p2p-listener-peek"
  "simple-bidirectional-lobby-message-delivery|Simple|bidirectional-lobby-message-delivery.json|bidirectional-lobby-message-delivery"
  "simple-bidirectional-lobby-member-data-propagation|Simple|bidirectional-lobby-member-data-propagation.json|bidirectional-lobby-member-data-propagation"
  "advanced-multiple-lobby-membership-and-message-isolation|Advanced|multiple-lobby-membership-and-message-isolation.json|multiple-lobby-membership-and-message-isolation")

get_property(UNIVERSELAN_BEHAVIOUR_TEST_VERSIONS GLOBAL PROPERTY PROJECT_GALAXY_VERSION_NUMBER_LIST)
foreach(behaviour_manifest_version IN LISTS UNIVERSELAN_BEHAVIOUR_TEST_VERSIONS)
  generate_universelan_behaviour_manifest("${behaviour_manifest_version}" "Simple" "automatic-lobby-member-persona.json")
  foreach(behaviour_scenario IN LISTS UNIVERSELAN_BEHAVIOUR_TEST_GOG_SCENARIOS)
    string(REPLACE "|" ";" behaviour_scenario_parts "${behaviour_scenario}")
    list(GET behaviour_scenario_parts 1 behaviour_scenario_directory)
    list(GET behaviour_scenario_parts 2 behaviour_scenario_manifest)
    generate_universelan_behaviour_manifest("${behaviour_manifest_version}" "${behaviour_scenario_directory}" "${behaviour_scenario_manifest}")
  endforeach()
endforeach()

# This intentionally separate host keeps the modern general-purpose host unchanged.
function(add_universelan_lobby_persona_host target version)
  add_executable(${target} Host/LobbyMemberPersonaMain.cxx)
  target_include_directories(${target} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_BINARY_DIR}"
    "${CMAKE_SOURCE_DIR}/Source/DLLs/${version}")
  target_link_libraries(${target} PRIVATE universelan-behaviour-test-common ${ARGN})
  set(GALAXY_VERSION "${UNIVERSELAN_BEHAVIOUR_TEST_ARCH}-${version}")
  add_version_definitions_to(${target})
  target_compile_definitions(${target} PRIVATE NOMINMAX
    "UNIVERSELAN_BEHAVIOUR_TEST_VERSION=\"${version}\""
    "UNIVERSELAN_BEHAVIOUR_TEST_ARCH=\"${UNIVERSELAN_BEHAVIOUR_TEST_ARCH}\"")
endfunction()

foreach(lobby_persona_version IN LISTS UNIVERSELAN_BEHAVIOUR_TEST_VERSIONS)
  set(lobby_persona_key "${UNIVERSELAN_BEHAVIOUR_TEST_ARCH}-${lobby_persona_version}")
  set(lobby_persona_client "universelan-client-${lobby_persona_key}")
  set(lobby_persona_server "universelan-server-${lobby_persona_key}")
  set(lobby_persona_gog_dir "${CMAKE_SOURCE_DIR}/Source/DLLs/${lobby_persona_version}/gog")
  set(lobby_persona_gog_lib "${lobby_persona_gog_dir}/Galaxy64.lib")
  set(lobby_persona_gog_dll "${lobby_persona_gog_dir}/Galaxy64.dll")
  set(lobby_persona_gog_peer_dll "${lobby_persona_gog_dir}/GalaxyPeer64.dll")
  get_property(lobby_persona_supported GLOBAL PROPERTY "GALAXY_${lobby_persona_version}_BUILD_FEATURE_IFRIENDS_ONPERSONADATACHANGED")
  if(TARGET ${lobby_persona_client} AND TARGET ${lobby_persona_server} AND lobby_persona_supported)

    add_universelan_lobby_persona_host(universelan-behaviour-lobby-persona-host-universelan-${lobby_persona_key} ${lobby_persona_version}
      ${lobby_persona_client})
    add_executable(universelan-behaviour-lobby-persona-runner-${lobby_persona_key} Runner/Main.cxx)
    target_include_directories(universelan-behaviour-lobby-persona-runner-${lobby_persona_key} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
    target_link_libraries(universelan-behaviour-lobby-persona-runner-${lobby_persona_key} PRIVATE universelan-behaviour-test-common json ixwebsocket)
    set(GALAXY_VERSION "${lobby_persona_key}")
    add_version_definitions_to(universelan-behaviour-lobby-persona-runner-${lobby_persona_key})
    target_compile_definitions(universelan-behaviour-lobby-persona-runner-${lobby_persona_key} PRIVATE NOMINMAX
      "UNIVERSELAN_BEHAVIOUR_TEST_VERSION=\"${lobby_persona_version}\""
      "UNIVERSELAN_BEHAVIOUR_TEST_ARCH=\"${UNIVERSELAN_BEHAVIOUR_TEST_ARCH}\"")
    add_dependencies(universelan-behaviour-lobby-persona-runner-${lobby_persona_key}
      universelan-behaviour-lobby-persona-host-universelan-${lobby_persona_key} ${lobby_persona_client} ${lobby_persona_server})

    if(EXISTS "${lobby_persona_gog_lib}" AND EXISTS "${lobby_persona_gog_dll}" AND EXISTS "${lobby_persona_gog_peer_dll}")
      add_universelan_lobby_persona_host(universelan-behaviour-lobby-persona-host-gog-${lobby_persona_key} ${lobby_persona_version}
        "${lobby_persona_gog_lib}")
      add_dependencies(universelan-behaviour-lobby-persona-runner-${lobby_persona_key}
        universelan-behaviour-lobby-persona-host-gog-${lobby_persona_key})
      if(ENABLE_UNIVERSELAN_GOG_BEHAVIOUR_TESTS AND UNIVERSELAN_BEHAVIOUR_TEST_CREDENTIALS_AVAILABLE)
        get_universelan_behaviour_manifest_path(lobby_persona_manifest "${lobby_persona_version}" "Simple" "automatic-lobby-member-persona.json")
        set(lobby_persona_peer_overlay_argument)
        if(NOT UNIVERSELAN_BEHAVIOUR_TEST_GOG_PEER_OVERLAY STREQUAL "")
          list(APPEND lobby_persona_peer_overlay_argument --gog-peer-overlay "${UNIVERSELAN_BEHAVIOUR_TEST_GOG_PEER_OVERLAY}")
        endif()
        add_test(NAME "universelan-behaviour-automatic-lobby-member-persona-${lobby_persona_key}"
          COMMAND $<TARGET_FILE:universelan-behaviour-lobby-persona-runner-${lobby_persona_key}>
            --manifest "${lobby_persona_manifest}"
            --universelan-host $<TARGET_FILE:universelan-behaviour-lobby-persona-host-universelan-${lobby_persona_key}>
            --gog-host $<TARGET_FILE:universelan-behaviour-lobby-persona-host-gog-${lobby_persona_key}>
            --client-dll $<TARGET_FILE:${lobby_persona_client}>
            --server $<TARGET_FILE:${lobby_persona_server}>
            --gog-runtime-dir "${lobby_persona_gog_dir}"
            ${lobby_persona_peer_overlay_argument})
        set_tests_properties("universelan-behaviour-automatic-lobby-member-persona-${lobby_persona_key}" PROPERTIES
          TIMEOUT 60 RUN_SERIAL TRUE RESOURCE_LOCK "universelan-behaviour-gog-accounts;universelan-system-network"
          LABELS "behavior;gog;Simple;automatic-lobby-member-persona;${lobby_persona_version}")
      endif()
    else()
      message(STATUS "BehaviourTests automatic lobby-member persona GOG host unavailable for ${lobby_persona_key}: matching official runtime artifacts are missing")
    endif()
  else()
    message(STATUS "BehaviourTests automatic lobby-member persona unavailable for ${lobby_persona_key}: matching targets or persona callback support are unavailable")
  endif()
endforeach()

function(add_universelan_behaviour_host target version)
  add_executable(${target} Host/Main.cxx)
  target_include_directories(${target} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_BINARY_DIR}"
    "${CMAKE_SOURCE_DIR}/Source/DLLs/${version}")
  target_link_libraries(${target} PRIVATE universelan-behaviour-test-common ${ARGN})
  set(GALAXY_VERSION "${UNIVERSELAN_BEHAVIOUR_TEST_ARCH}-${version}")
  add_version_definitions_to(${target})
  target_compile_definitions(${target} PRIVATE
    NOMINMAX
    "UNIVERSELAN_BEHAVIOUR_TEST_VERSION=\"${version}\""
    "UNIVERSELAN_BEHAVIOUR_TEST_ARCH=\"${UNIVERSELAN_BEHAVIOUR_TEST_ARCH}\"")
endfunction()

function(add_universelan_gog_behaviour_test version scenario scenario_directory manifest scenario_label)
  set(version_key "${UNIVERSELAN_BEHAVIOUR_TEST_ARCH}-${version}")
  set(client_target "universelan-client-${version_key}")
  set(server_target "universelan-server-${version_key}")
  set(gog_dir "${CMAKE_SOURCE_DIR}/Source/DLLs/${version}/gog")
  set(peer_overlay_argument)
  if(NOT UNIVERSELAN_BEHAVIOUR_TEST_GOG_PEER_OVERLAY STREQUAL "")
    list(APPEND peer_overlay_argument --gog-peer-overlay "${UNIVERSELAN_BEHAVIOUR_TEST_GOG_PEER_OVERLAY}")
  endif()
  get_universelan_behaviour_manifest_path(generated_manifest "${version}" "${scenario_directory}" "${manifest}")
  add_test(NAME "universelan-behaviour-${scenario}-${version_key}"
    COMMAND $<TARGET_FILE:universelan-behaviour-runner-${version_key}>
      --manifest "${generated_manifest}"
      --universelan-host $<TARGET_FILE:universelan-behaviour-host-universelan-${version_key}>
      --gog-host $<TARGET_FILE:universelan-behaviour-host-gog-${version_key}>
       --client-dll $<TARGET_FILE:${client_target}>
       --server $<TARGET_FILE:${server_target}>
       --gog-runtime-dir "${gog_dir}"
       ${peer_overlay_argument})
  set_tests_properties("universelan-behaviour-${scenario}-${version_key}" PROPERTIES
    TIMEOUT 60
    RUN_SERIAL TRUE
    RESOURCE_LOCK "universelan-behaviour-gog-accounts;universelan-system-network"
    LABELS "behavior;gog;${scenario_directory};${scenario_label};${version}")
endfunction()

function(add_universelan_game_server_p2p_test version client_target server_target gog_lib)
  set(version_key "${UNIVERSELAN_BEHAVIOUR_TEST_ARCH}-${version}")
  get_property(has_igalaxy GLOBAL PROPERTY "GALAXY_${version}_BUILD_FEATURE_HAS_IGALAXY")
  get_property(has_server_networking GLOBAL PROPERTY "GALAXY_${version}_BUILD_FEATURE_HAS_ISERVERNETWORKING")
  get_property(has_lobby_features GLOBAL PROPERTY "GALAXY_${version}_BUILD_FEATURE_HAS_1_73_LOBBY_FEATURES")
  if(has_igalaxy AND has_server_networking AND has_lobby_features AND EXISTS "${gog_lib}")
    add_executable(universelan-behaviour-game-server-p2p-host-${version_key} GameServerP2PSenderIdentityHost.cxx)
    target_include_directories(universelan-behaviour-game-server-p2p-host-${version_key} PRIVATE
      "${CMAKE_CURRENT_BINARY_DIR}"
      "${CMAKE_SOURCE_DIR}/Source/DLLs/${version}")
    target_link_libraries(universelan-behaviour-game-server-p2p-host-${version_key} PRIVATE "${gog_lib}")
    set(GALAXY_VERSION "${version_key}")
    add_version_definitions_to(universelan-behaviour-game-server-p2p-host-${version_key})
    target_compile_definitions(universelan-behaviour-game-server-p2p-host-${version_key} PRIVATE NOMINMAX
      "UNIVERSELAN_BEHAVIOUR_TEST_VERSION=\"${version}\""
      "UNIVERSELAN_BEHAVIOUR_TEST_ARCH=\"${UNIVERSELAN_BEHAVIOUR_TEST_ARCH}\"")
    add_executable(universelan-behaviour-game-server-p2p-runner-${version_key} GameServerP2PSenderIdentityRunner.cxx)
    set(GALAXY_VERSION "${version_key}")
    add_version_definitions_to(universelan-behaviour-game-server-p2p-runner-${version_key})
    target_compile_definitions(universelan-behaviour-game-server-p2p-runner-${version_key} PRIVATE NOMINMAX
      "UNIVERSELAN_BEHAVIOUR_TEST_VERSION=\"${version}\""
      "UNIVERSELAN_BEHAVIOUR_TEST_ARCH=\"${UNIVERSELAN_BEHAVIOUR_TEST_ARCH}\"")
    add_dependencies(universelan-behaviour-game-server-p2p-runner-${version_key}
      universelan-behaviour-game-server-p2p-host-${version_key} ${client_target} ${server_target})
    add_test(NAME "universelan-behaviour-game-server-p2p-${version_key}"
      COMMAND $<TARGET_FILE:universelan-behaviour-game-server-p2p-runner-${version_key}>
        --host $<TARGET_FILE:universelan-behaviour-game-server-p2p-host-${version_key}>
        --client-dll $<TARGET_FILE:${client_target}>
        --server $<TARGET_FILE:${server_target}>)
    set_tests_properties("universelan-behaviour-game-server-p2p-${version_key}" PROPERTIES
      LABELS "behavior;universelan;characterization;game-server-p2p;${version}"
      TIMEOUT 60
      RUN_SERIAL TRUE)
  endif()
endfunction()

function(add_universelan_behaviour_version version)
  set(version_key "${UNIVERSELAN_BEHAVIOUR_TEST_ARCH}-${version}")
  set(client_target "universelan-client-${version_key}")
  set(server_target "universelan-server-${version_key}")
  set(gog_dir "${CMAKE_SOURCE_DIR}/Source/DLLs/${version}/gog")
  set(gog_lib "${gog_dir}/Galaxy64.lib")
  set(gog_dll "${gog_dir}/Galaxy64.dll")
  set(gog_peer_dll "${gog_dir}/GalaxyPeer64.dll")
  if(TARGET ${client_target} AND TARGET ${server_target})
    add_universelan_behaviour_host(universelan-behaviour-host-universelan-${version_key} "${version}" ${client_target})
    add_executable(universelan-behaviour-runner-${version_key} Runner/Main.cxx)
    target_include_directories(universelan-behaviour-runner-${version_key} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
    target_link_libraries(universelan-behaviour-runner-${version_key} PRIVATE universelan-behaviour-test-common json ixwebsocket)
    set(GALAXY_VERSION "${version_key}")
    add_version_definitions_to(universelan-behaviour-runner-${version_key})
    target_compile_definitions(universelan-behaviour-runner-${version_key} PRIVATE NOMINMAX
      "UNIVERSELAN_BEHAVIOUR_TEST_VERSION=\"${version}\""
      "UNIVERSELAN_BEHAVIOUR_TEST_ARCH=\"${UNIVERSELAN_BEHAVIOUR_TEST_ARCH}\"")
    add_dependencies(universelan-behaviour-runner-${version_key}
      universelan-behaviour-host-universelan-${version_key} ${client_target} ${server_target})

    add_universelan_game_server_p2p_test("${version}" "${client_target}" "${server_target}" "${gog_lib}")

    if(EXISTS "${gog_lib}" AND EXISTS "${gog_dll}" AND EXISTS "${gog_peer_dll}")
      add_universelan_behaviour_host(universelan-behaviour-host-gog-${version_key} "${version}" "${gog_lib}")
      add_dependencies(universelan-behaviour-runner-${version_key} universelan-behaviour-host-gog-${version_key})
      if(ENABLE_UNIVERSELAN_GOG_BEHAVIOUR_TESTS AND UNIVERSELAN_BEHAVIOUR_TEST_CREDENTIALS_AVAILABLE)
        foreach(behaviour_scenario IN LISTS UNIVERSELAN_BEHAVIOUR_TEST_GOG_SCENARIOS)
          string(REPLACE "|" ";" behaviour_scenario_parts "${behaviour_scenario}")
          list(GET behaviour_scenario_parts 0 behaviour_scenario_name)
          list(GET behaviour_scenario_parts 1 behaviour_scenario_directory)
          list(GET behaviour_scenario_parts 2 behaviour_scenario_manifest)
          list(GET behaviour_scenario_parts 3 behaviour_scenario_label)
          add_universelan_gog_behaviour_test("${version}" "${behaviour_scenario_name}" "${behaviour_scenario_directory}" "${behaviour_scenario_manifest}" "${behaviour_scenario_label}")
        endforeach()
      elseif(ENABLE_UNIVERSELAN_GOG_BEHAVIOUR_TESTS)
        message(STATUS "BehaviourTests official-GOG scenarios unavailable for ${version_key}: credentials are unavailable")
      else()
        message(STATUS "BehaviourTests official-GOG scenarios are not registered for ${version_key}; set ENABLE_UNIVERSELAN_GOG_BEHAVIOUR_TESTS=ON after local preflight")
      endif()
    else()
      message(STATUS "BehaviourTests official-GOG host unavailable for ${version_key}: matching runtime artifacts are missing")
    endif()
  else()
    message(STATUS "BehaviourTests unavailable for ${version_key}: matching UniverseLAN client/server targets were not selected")
  endif()
endfunction()

foreach(behaviour_version IN LISTS UNIVERSELAN_BEHAVIOUR_TEST_VERSIONS)
  add_universelan_behaviour_version("${behaviour_version}")
endforeach()
endif()
