cmake_minimum_required(VERSION 3.16)

set(UNIVERSELAN_SYSTEM_TEST_CREDENTIALS "${CMAKE_SOURCE_DIR}/Source/TestCommon/credentials.cmake")
set(UNIVERSELAN_SYSTEM_TEST_CREDENTIALS_AVAILABLE 0)
if(EXISTS "${UNIVERSELAN_SYSTEM_TEST_CREDENTIALS}")
  include("${UNIVERSELAN_SYSTEM_TEST_CREDENTIALS}")
  if(DEFINED GALAXY_SDK_USER_CREDENTIALS_USER1_NAME
      AND DEFINED GALAXY_SDK_USER_CREDENTIALS_USER1_PASSWORD
      AND DEFINED GALAXY_SDK_USER_CREDENTIALS_USER2_NAME
      AND DEFINED GALAXY_SDK_USER_CREDENTIALS_USER2_PASSWORD
      AND DEFINED GALAXY_SDK_CLIENT_ID
      AND DEFINED GALAXY_SDK_CLIENT_SECRET)
    set(UNIVERSELAN_SYSTEM_TEST_CREDENTIALS_AVAILABLE 1)
  endif()
endif()

get_property(SYSTEM_TEST_VERSIONS GLOBAL PROPERTY PROJECT_GALAXY_VERSION_NUMBER_LIST)

add_library(universelan-system-test-common STATIC Common/Protocol.cxx)

foreach(GALAXY_VERSION_NUMBER IN LISTS SYSTEM_TEST_VERSIONS)
  set(GALAXY_VERSION "${GALAXY_ARCH}-${GALAXY_VERSION_NUMBER}")
  set(SYSTEM_TEST_CLIENT_TARGET "universelan-client-${GALAXY_VERSION}")
  set(SYSTEM_TEST_SERVER_TARGET "universelan-server-${GALAXY_VERSION}")

  if(NOT TARGET ${SYSTEM_TEST_CLIENT_TARGET} OR NOT TARGET ${SYSTEM_TEST_SERVER_TARGET})
    message(WARNING "Skipping system tests for ${GALAXY_VERSION}: matching client or server target is unavailable")
    continue()
  endif()

  set(SYSTEM_TEST_HOST "universelan-system-test-host-${GALAXY_VERSION}")
  set(SYSTEM_TEST_RUNNER "universelan-system-test-runner-${GALAXY_VERSION}")
  get_property(SYSTEM_TEST_HAS_ITELEMETRY GLOBAL PROPERTY "GALAXY_${GALAXY_VERSION_NUMBER}_BUILD_FEATURE_HAS_ITELEMETRY")

  add_executable(${SYSTEM_TEST_HOST}
    Host/Main.cxx
    Host/Lobby.cxx
    Host/P2P.cxx
    Host/Chat.cxx
    Host/Friends.cxx
    Host/Stats.cxx
    Host/UserData.cxx
    Host/CustomNetworking.cxx
    Host/Storage.cxx
    Host/CloudStorage.cxx
    Host/Apps.cxx
    Host/Utils.cxx
  )
  if(SYSTEM_TEST_HAS_ITELEMETRY)
    target_sources(${SYSTEM_TEST_HOST} PRIVATE Host/Telemetry.cxx)
  endif()
  target_include_directories(${SYSTEM_TEST_HOST} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_SOURCE_DIR}/Source/DLLs/${GALAXY_VERSION_NUMBER}/galaxy"
  )
  target_link_libraries(${SYSTEM_TEST_HOST} PRIVATE universelan-system-test-common ${SYSTEM_TEST_CLIENT_TARGET} ixwebsocket)
  add_version_definitions_to(${SYSTEM_TEST_HOST})
  if(CMAKE_DL_LIBS)
    target_link_libraries(${SYSTEM_TEST_HOST} PRIVATE ${CMAKE_DL_LIBS})
  endif()
  target_compile_definitions(${SYSTEM_TEST_HOST} PRIVATE
    "UNIVERSELAN_SYSTEM_TEST_VERSION=\"${GALAXY_VERSION_NUMBER}\""
    "UNIVERSELAN_SYSTEM_TEST_ARCH=\"${GALAXY_ARCH}\""
    "UNIVERSELAN_SYSTEM_TEST_CREDENTIALS_AVAILABLE=${UNIVERSELAN_SYSTEM_TEST_CREDENTIALS_AVAILABLE}"
  )
  if(UNIVERSELAN_SYSTEM_TEST_CREDENTIALS_AVAILABLE)
    target_compile_definitions(${SYSTEM_TEST_HOST} PRIVATE
      "UNIVERSELAN_SYSTEM_TEST_CREDENTIALS_USER1_NAME=\"${GALAXY_SDK_USER_CREDENTIALS_USER1_NAME}\""
      "UNIVERSELAN_SYSTEM_TEST_CREDENTIALS_USER1_PASSWORD=\"${GALAXY_SDK_USER_CREDENTIALS_USER1_PASSWORD}\""
      "UNIVERSELAN_SYSTEM_TEST_CREDENTIALS_USER2_NAME=\"${GALAXY_SDK_USER_CREDENTIALS_USER2_NAME}\""
      "UNIVERSELAN_SYSTEM_TEST_CREDENTIALS_USER2_PASSWORD=\"${GALAXY_SDK_USER_CREDENTIALS_USER2_PASSWORD}\""
      "UNIVERSELAN_SYSTEM_TEST_CLIENT_ID=\"${GALAXY_SDK_CLIENT_ID}\""
      "UNIVERSELAN_SYSTEM_TEST_CLIENT_SECRET=\"${GALAXY_SDK_CLIENT_SECRET}\""
    )
  endif()

  add_executable(${SYSTEM_TEST_RUNNER}
    Runner/Main.cxx
    Runner/Model.cxx
    Runner/Configuration.cxx
    Runner/Process.cxx
  )
  target_include_directories(${SYSTEM_TEST_RUNNER} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
  target_link_libraries(${SYSTEM_TEST_RUNNER} PRIVATE universelan-system-test-common json ixwebsocket)
  if(WIN32)
    target_link_libraries(${SYSTEM_TEST_RUNNER} PRIVATE Ws2_32)
  endif()
  target_compile_definitions(${SYSTEM_TEST_RUNNER} PRIVATE
    "UNIVERSELAN_SYSTEM_TEST_VERSION=\"${GALAXY_VERSION_NUMBER}\""
    "UNIVERSELAN_SYSTEM_TEST_ARCH=\"${GALAXY_ARCH}\""
  )
  add_dependencies(${SYSTEM_TEST_RUNNER} ${SYSTEM_TEST_HOST} ${SYSTEM_TEST_CLIENT_TARGET} ${SYSTEM_TEST_SERVER_TARGET})

  add_test(
    NAME "universelan-system-initialize-and-sign-in-${GALAXY_VERSION}"
    COMMAND $<TARGET_FILE:${SYSTEM_TEST_RUNNER}>
      --manifest "${CMAKE_CURRENT_SOURCE_DIR}/Scenarios/initialize-and-sign-in.json"
      --host $<TARGET_FILE:${SYSTEM_TEST_HOST}>
      --client-dll $<TARGET_FILE:${SYSTEM_TEST_CLIENT_TARGET}>
      --server $<TARGET_FILE:${SYSTEM_TEST_SERVER_TARGET}>
      --gog-runtime-dir "${CMAKE_SOURCE_DIR}/Source/DLLs/${GALAXY_VERSION_NUMBER}/gog"
      --runtime-name $<TARGET_FILE_NAME:${SYSTEM_TEST_CLIENT_TARGET}>
      --version "${GALAXY_VERSION_NUMBER}"
      --arch "${GALAXY_ARCH}"
  )
  set_tests_properties("universelan-system-initialize-and-sign-in-${GALAXY_VERSION}" PROPERTIES
    TIMEOUT 30
    RUN_SERIAL TRUE
    RESOURCE_LOCK universelan-system-network
    LABELS system
    SKIP_REGULAR_EXPRESSION "SYSTEM_TEST SKIP"
  )

  get_property(SYSTEM_TEST_HAS_LOBBY_LISTENERS GLOBAL PROPERTY "GALAXY_${GALAXY_VERSION_NUMBER}_BUILD_FEATURE_LOBBY_LISTENERS")
  get_property(SYSTEM_TEST_HAS_LOBBY_TOPOLOGY_TYPE GLOBAL PROPERTY "GALAXY_${GALAXY_VERSION_NUMBER}_BUILD_FEATURE_HAS_LOBBYTOPOLOGYTYPE_ENUM")
   get_property(SYSTEM_TEST_HAS_TYPED_GALAXY_IDS GLOBAL PROPERTY "GALAXY_${GALAXY_VERSION_NUMBER}_BUILD_FEATURE_GALAXYID_HAS_IDTYPE")
   get_property(SYSTEM_TEST_HAS_CONNECTION_TYPE GLOBAL PROPERTY "GALAXY_${GALAXY_VERSION_NUMBER}_BUILD_FEATURE_HAS_CONNECTION_TYPE")
  get_property(SYSTEM_TEST_HAS_ISTORAGE GLOBAL PROPERTY "GALAXY_${GALAXY_VERSION_NUMBER}_BUILD_FEATURE_HAS_ISTORAGE")
   get_property(SYSTEM_TEST_HAS_ICLOUDSTORAGE GLOBAL PROPERTY "GALAXY_${GALAXY_VERSION_NUMBER}_BUILD_FEATURE_HAS_ICLOUDSTORAGE")
   get_property(SYSTEM_TEST_HAS_IAPPS GLOBAL PROPERTY "GALAXY_${GALAXY_VERSION_NUMBER}_BUILD_FEATURE_HAS_IAPPS")
   get_property(SYSTEM_TEST_HAS_GETCURRENTGAMELANGUAGE GLOBAL PROPERTY "GALAXY_${GALAXY_VERSION_NUMBER}_BUILD_FEATURE_HAS_GETCURRENTGAMELANGUAGE")
   get_property(SYSTEM_TEST_HAS_IUTILS GLOBAL PROPERTY "GALAXY_${GALAXY_VERSION_NUMBER}_BUILD_FEATURE_HAS_IUTILS")
   get_property(SYSTEM_TEST_HAS_IUTILS_SHOWOVERLAYWITHWEBPAGE GLOBAL PROPERTY "GALAXY_${GALAXY_VERSION_NUMBER}_BUILD_FEATURE_HAS_IUTILS_SHOWOVERLAYWITHWEBPAGE")
   get_property(SYSTEM_TEST_HAS_OVERLAYSTATE_ENUM GLOBAL PROPERTY "GALAXY_${GALAXY_VERSION_NUMBER}_BUILD_FEATURE_OVERLAYSTATE_ENUM")
   get_property(SYSTEM_TEST_HAS_DISABLEOVERLAYPOPUPS GLOBAL PROPERTY "GALAXY_${GALAXY_VERSION_NUMBER}_BUILD_FEATURE_HAS_DISABLEOVERLAYPOPUPS")
    if(SYSTEM_TEST_HAS_IUTILS AND SYSTEM_TEST_HAS_IUTILS_SHOWOVERLAYWITHWEBPAGE
        AND SYSTEM_TEST_HAS_OVERLAYSTATE_ENUM AND SYSTEM_TEST_HAS_DISABLEOVERLAYPOPUPS)
     add_test(
       NAME "universelan-system-utils-overlay-disabled-invariant-${GALAXY_VERSION}"
       COMMAND $<TARGET_FILE:${SYSTEM_TEST_RUNNER}>
         --manifest "${CMAKE_CURRENT_SOURCE_DIR}/Scenarios/utils-overlay-disabled-invariant.json"
         --host $<TARGET_FILE:${SYSTEM_TEST_HOST}>
         --client-dll $<TARGET_FILE:${SYSTEM_TEST_CLIENT_TARGET}>
         --server $<TARGET_FILE:${SYSTEM_TEST_SERVER_TARGET}>
         --gog-runtime-dir "${CMAKE_SOURCE_DIR}/Source/DLLs/${GALAXY_VERSION_NUMBER}/gog"
         --runtime-name $<TARGET_FILE_NAME:${SYSTEM_TEST_CLIENT_TARGET}>
         --version "${GALAXY_VERSION_NUMBER}"
         --arch "${GALAXY_ARCH}"
     )
     set_tests_properties("universelan-system-utils-overlay-disabled-invariant-${GALAXY_VERSION}" PROPERTIES
       TIMEOUT 30
       RUN_SERIAL TRUE
       RESOURCE_LOCK universelan-system-network
       LABELS system
       SKIP_REGULAR_EXPRESSION "SYSTEM_TEST SKIP"
     )
   endif()
    if(SYSTEM_TEST_HAS_IAPPS AND SYSTEM_TEST_HAS_GETCURRENTGAMELANGUAGE)
     add_test(
       NAME "universelan-system-apps-config-and-dlc-ownership-${GALAXY_VERSION}"
       COMMAND $<TARGET_FILE:${SYSTEM_TEST_RUNNER}>
         --manifest "${CMAKE_CURRENT_SOURCE_DIR}/Scenarios/apps-config-and-dlc-ownership.json"
         --host $<TARGET_FILE:${SYSTEM_TEST_HOST}>
         --client-dll $<TARGET_FILE:${SYSTEM_TEST_CLIENT_TARGET}>
         --server $<TARGET_FILE:${SYSTEM_TEST_SERVER_TARGET}>
         --gog-runtime-dir "${CMAKE_SOURCE_DIR}/Source/DLLs/${GALAXY_VERSION_NUMBER}/gog"
         --runtime-name $<TARGET_FILE_NAME:${SYSTEM_TEST_CLIENT_TARGET}>
         --version "${GALAXY_VERSION_NUMBER}"
         --arch "${GALAXY_ARCH}"
     )
     set_tests_properties("universelan-system-apps-config-and-dlc-ownership-${GALAXY_VERSION}" PROPERTIES
       TIMEOUT 30
       RUN_SERIAL TRUE
       RESOURCE_LOCK universelan-system-network
       LABELS system
       SKIP_REGULAR_EXPRESSION "SYSTEM_TEST SKIP"
     )
   endif()
   if(SYSTEM_TEST_HAS_ISTORAGE)
    add_test(
      NAME "universelan-system-file-share-server-persisted-roundtrip-${GALAXY_VERSION}"
      COMMAND $<TARGET_FILE:${SYSTEM_TEST_RUNNER}>
        --manifest "${CMAKE_CURRENT_SOURCE_DIR}/Scenarios/file-share-server-persisted-roundtrip.json"
        --host $<TARGET_FILE:${SYSTEM_TEST_HOST}>
        --client-dll $<TARGET_FILE:${SYSTEM_TEST_CLIENT_TARGET}>
        --server $<TARGET_FILE:${SYSTEM_TEST_SERVER_TARGET}>
        --gog-runtime-dir "${CMAKE_SOURCE_DIR}/Source/DLLs/${GALAXY_VERSION_NUMBER}/gog"
        --runtime-name $<TARGET_FILE_NAME:${SYSTEM_TEST_CLIENT_TARGET}>
        --version "${GALAXY_VERSION_NUMBER}"
        --arch "${GALAXY_ARCH}"
    )
    set_tests_properties("universelan-system-file-share-server-persisted-roundtrip-${GALAXY_VERSION}" PROPERTIES
      TIMEOUT 45
      RUN_SERIAL TRUE
      RESOURCE_LOCK universelan-system-network
      LABELS system
      SKIP_REGULAR_EXPRESSION "SYSTEM_TEST SKIP"
    )
     if(SYSTEM_TEST_HAS_ISTORAGE)
      add_test(
        NAME "universelan-system-file-share-server-policy-denied-${GALAXY_VERSION}"
        COMMAND $<TARGET_FILE:${SYSTEM_TEST_RUNNER}>
          --manifest "${CMAKE_CURRENT_SOURCE_DIR}/Scenarios/file-share-server-policy-denied.json"
          --host $<TARGET_FILE:${SYSTEM_TEST_HOST}>
          --client-dll $<TARGET_FILE:${SYSTEM_TEST_CLIENT_TARGET}>
          --server $<TARGET_FILE:${SYSTEM_TEST_SERVER_TARGET}>
          --gog-runtime-dir "${CMAKE_SOURCE_DIR}/Source/DLLs/${GALAXY_VERSION_NUMBER}/gog"
          --runtime-name $<TARGET_FILE_NAME:${SYSTEM_TEST_CLIENT_TARGET}>
          --version "${GALAXY_VERSION_NUMBER}"
          --arch "${GALAXY_ARCH}"
      )
      set_tests_properties("universelan-system-file-share-server-policy-denied-${GALAXY_VERSION}" PROPERTIES
        TIMEOUT 45
        RUN_SERIAL TRUE
        RESOURCE_LOCK universelan-system-network
        LABELS system
        SKIP_REGULAR_EXPRESSION "SYSTEM_TEST SKIP"
      )
      add_test(
        NAME "universelan-system-file-share-server-download-policy-denied-${GALAXY_VERSION}"
        COMMAND $<TARGET_FILE:${SYSTEM_TEST_RUNNER}>
          --manifest "${CMAKE_CURRENT_SOURCE_DIR}/Scenarios/file-share-server-download-policy-denied.json"
          --host $<TARGET_FILE:${SYSTEM_TEST_HOST}>
          --client-dll $<TARGET_FILE:${SYSTEM_TEST_CLIENT_TARGET}>
          --server $<TARGET_FILE:${SYSTEM_TEST_SERVER_TARGET}>
          --gog-runtime-dir "${CMAKE_SOURCE_DIR}/Source/DLLs/${GALAXY_VERSION_NUMBER}/gog"
          --runtime-name $<TARGET_FILE_NAME:${SYSTEM_TEST_CLIENT_TARGET}>
          --version "${GALAXY_VERSION_NUMBER}"
          --arch "${GALAXY_ARCH}"
      )
      set_tests_properties("universelan-system-file-share-server-download-policy-denied-${GALAXY_VERSION}" PROPERTIES
        TIMEOUT 45
        RUN_SERIAL TRUE
        RESOURCE_LOCK universelan-system-network
        LABELS system
        SKIP_REGULAR_EXPRESSION "SYSTEM_TEST SKIP"
      )
    endif()
  endif()
  if(SYSTEM_TEST_HAS_ICLOUDSTORAGE)
    add_test(
      NAME "universelan-system-cloud-storage-local-roundtrip-${GALAXY_VERSION}"
      COMMAND $<TARGET_FILE:${SYSTEM_TEST_RUNNER}>
        --manifest "${CMAKE_CURRENT_SOURCE_DIR}/Scenarios/cloud-storage-local-roundtrip.json"
        --host $<TARGET_FILE:${SYSTEM_TEST_HOST}>
        --client-dll $<TARGET_FILE:${SYSTEM_TEST_CLIENT_TARGET}>
        --server $<TARGET_FILE:${SYSTEM_TEST_SERVER_TARGET}>
        --gog-runtime-dir "${CMAKE_SOURCE_DIR}/Source/DLLs/${GALAXY_VERSION_NUMBER}/gog"
        --runtime-name $<TARGET_FILE_NAME:${SYSTEM_TEST_CLIENT_TARGET}>
        --version "${GALAXY_VERSION_NUMBER}"
        --arch "${GALAXY_ARCH}"
    )
    set_tests_properties("universelan-system-cloud-storage-local-roundtrip-${GALAXY_VERSION}" PROPERTIES
      TIMEOUT 45
      RUN_SERIAL TRUE
      RESOURCE_LOCK universelan-system-network
      LABELS system
      SKIP_REGULAR_EXPRESSION "SYSTEM_TEST SKIP"
    )
  endif()
  if(SYSTEM_TEST_HAS_LOBBY_LISTENERS)
    add_test(
      NAME "universelan-system-lobby-create-list-join-${GALAXY_VERSION}"
      COMMAND $<TARGET_FILE:${SYSTEM_TEST_RUNNER}>
        --manifest "${CMAKE_CURRENT_SOURCE_DIR}/Scenarios/lobby-create-list-join.json"
        --host $<TARGET_FILE:${SYSTEM_TEST_HOST}>
        --client-dll $<TARGET_FILE:${SYSTEM_TEST_CLIENT_TARGET}>
        --server $<TARGET_FILE:${SYSTEM_TEST_SERVER_TARGET}>
        --gog-runtime-dir "${CMAKE_SOURCE_DIR}/Source/DLLs/${GALAXY_VERSION_NUMBER}/gog"
        --runtime-name $<TARGET_FILE_NAME:${SYSTEM_TEST_CLIENT_TARGET}>
        --version "${GALAXY_VERSION_NUMBER}"
        --arch "${GALAXY_ARCH}"
    )
    set_tests_properties("universelan-system-lobby-create-list-join-${GALAXY_VERSION}" PROPERTIES
      TIMEOUT 45
      RUN_SERIAL TRUE
      RESOURCE_LOCK universelan-system-network
      LABELS system
      SKIP_REGULAR_EXPRESSION "SYSTEM_TEST SKIP"
    )

    add_test(
      NAME "universelan-system-lobby-data-member-propagation-${GALAXY_VERSION}"
      COMMAND $<TARGET_FILE:${SYSTEM_TEST_RUNNER}>
        --manifest "${CMAKE_CURRENT_SOURCE_DIR}/Scenarios/lobby-data-member-propagation.json"
        --host $<TARGET_FILE:${SYSTEM_TEST_HOST}>
        --client-dll $<TARGET_FILE:${SYSTEM_TEST_CLIENT_TARGET}>
        --server $<TARGET_FILE:${SYSTEM_TEST_SERVER_TARGET}>
        --gog-runtime-dir "${CMAKE_SOURCE_DIR}/Source/DLLs/${GALAXY_VERSION_NUMBER}/gog"
        --runtime-name $<TARGET_FILE_NAME:${SYSTEM_TEST_CLIENT_TARGET}>
        --version "${GALAXY_VERSION_NUMBER}"
        --arch "${GALAXY_ARCH}"
    )
    set_tests_properties("universelan-system-lobby-data-member-propagation-${GALAXY_VERSION}" PROPERTIES
      TIMEOUT 45
      RUN_SERIAL TRUE
      RESOURCE_LOCK universelan-system-network
      LABELS system
      SKIP_REGULAR_EXPRESSION "SYSTEM_TEST SKIP"
    )

    add_test(
      NAME "universelan-system-lobby-member-leave-lifecycle-${GALAXY_VERSION}"
      COMMAND $<TARGET_FILE:${SYSTEM_TEST_RUNNER}>
        --manifest "${CMAKE_CURRENT_SOURCE_DIR}/Scenarios/lobby-member-leave-lifecycle.json"
        --host $<TARGET_FILE:${SYSTEM_TEST_HOST}>
        --client-dll $<TARGET_FILE:${SYSTEM_TEST_CLIENT_TARGET}>
        --server $<TARGET_FILE:${SYSTEM_TEST_SERVER_TARGET}>
        --gog-runtime-dir "${CMAKE_SOURCE_DIR}/Source/DLLs/${GALAXY_VERSION_NUMBER}/gog"
        --runtime-name $<TARGET_FILE_NAME:${SYSTEM_TEST_CLIENT_TARGET}>
        --version "${GALAXY_VERSION_NUMBER}"
        --arch "${GALAXY_ARCH}"
    )
    set_tests_properties("universelan-system-lobby-member-leave-lifecycle-${GALAXY_VERSION}" PROPERTIES
      TIMEOUT 45
      RUN_SERIAL TRUE
      RESOURCE_LOCK universelan-system-network
      LABELS system
      SKIP_REGULAR_EXPRESSION "SYSTEM_TEST SKIP"
    )

    if(SYSTEM_TEST_HAS_LOBBY_TOPOLOGY_TYPE)
      add_test(
        NAME "universelan-system-lobby-owner-ownership-transfer-${GALAXY_VERSION}"
        COMMAND $<TARGET_FILE:${SYSTEM_TEST_RUNNER}>
          --manifest "${CMAKE_CURRENT_SOURCE_DIR}/Scenarios/lobby-owner-ownership-transfer.json"
          --host $<TARGET_FILE:${SYSTEM_TEST_HOST}>
          --client-dll $<TARGET_FILE:${SYSTEM_TEST_CLIENT_TARGET}>
          --server $<TARGET_FILE:${SYSTEM_TEST_SERVER_TARGET}>
          --gog-runtime-dir "${CMAKE_SOURCE_DIR}/Source/DLLs/${GALAXY_VERSION_NUMBER}/gog"
          --runtime-name $<TARGET_FILE_NAME:${SYSTEM_TEST_CLIENT_TARGET}>
          --version "${GALAXY_VERSION_NUMBER}"
          --arch "${GALAXY_ARCH}"
      )
      set_tests_properties("universelan-system-lobby-owner-ownership-transfer-${GALAXY_VERSION}" PROPERTIES
        TIMEOUT 45
        RUN_SERIAL TRUE
        RESOURCE_LOCK universelan-system-network
        LABELS system
        SKIP_REGULAR_EXPRESSION "SYSTEM_TEST SKIP"
      )

      add_test(
        NAME "universelan-system-lobby-owner-close-lifecycle-${GALAXY_VERSION}"
        COMMAND $<TARGET_FILE:${SYSTEM_TEST_RUNNER}>
          --manifest "${CMAKE_CURRENT_SOURCE_DIR}/Scenarios/lobby-owner-close-lifecycle.json"
          --host $<TARGET_FILE:${SYSTEM_TEST_HOST}>
          --client-dll $<TARGET_FILE:${SYSTEM_TEST_CLIENT_TARGET}>
          --server $<TARGET_FILE:${SYSTEM_TEST_SERVER_TARGET}>
          --gog-runtime-dir "${CMAKE_SOURCE_DIR}/Source/DLLs/${GALAXY_VERSION_NUMBER}/gog"
          --runtime-name $<TARGET_FILE_NAME:${SYSTEM_TEST_CLIENT_TARGET}>
          --version "${GALAXY_VERSION_NUMBER}"
          --arch "${GALAXY_ARCH}"
      )
      set_tests_properties("universelan-system-lobby-owner-close-lifecycle-${GALAXY_VERSION}" PROPERTIES
        TIMEOUT 45
        RUN_SERIAL TRUE
        RESOURCE_LOCK universelan-system-network
        LABELS system
        SKIP_REGULAR_EXPRESSION "SYSTEM_TEST SKIP"
      )
    endif()
  endif()

  if(SYSTEM_TEST_HAS_LOBBY_LISTENERS AND SYSTEM_TEST_HAS_TYPED_GALAXY_IDS)
    set(SYSTEM_TEST_P2P_SCENARIOS raw-p2p-bidirectional raw-p2p-three-peer-routing)
    list(APPEND SYSTEM_TEST_P2P_SCENARIOS raw-p2p-channel-boundary-routing raw-p2p-leave-revokes-routing)
    foreach(SYSTEM_TEST_P2P_SCENARIO IN LISTS SYSTEM_TEST_P2P_SCENARIOS)
      add_test(
        NAME "universelan-system-${SYSTEM_TEST_P2P_SCENARIO}-${GALAXY_VERSION}"
        COMMAND $<TARGET_FILE:${SYSTEM_TEST_RUNNER}>
          --manifest "${CMAKE_CURRENT_SOURCE_DIR}/Scenarios/${SYSTEM_TEST_P2P_SCENARIO}.json"
          --host $<TARGET_FILE:${SYSTEM_TEST_HOST}>
          --client-dll $<TARGET_FILE:${SYSTEM_TEST_CLIENT_TARGET}>
          --server $<TARGET_FILE:${SYSTEM_TEST_SERVER_TARGET}>
          --gog-runtime-dir "${CMAKE_SOURCE_DIR}/Source/DLLs/${GALAXY_VERSION_NUMBER}/gog"
          --runtime-name $<TARGET_FILE_NAME:${SYSTEM_TEST_CLIENT_TARGET}>
          --version "${GALAXY_VERSION_NUMBER}"
          --arch "${GALAXY_ARCH}"
      )
      set_tests_properties("universelan-system-${SYSTEM_TEST_P2P_SCENARIO}-${GALAXY_VERSION}" PROPERTIES
        TIMEOUT 60
        RUN_SERIAL TRUE
        RESOURCE_LOCK universelan-system-network
        LABELS system
        SKIP_REGULAR_EXPRESSION "SYSTEM_TEST SKIP"
      )
    endforeach()
  endif()

  if(SYSTEM_TEST_HAS_CONNECTION_TYPE AND SYSTEM_TEST_HAS_TYPED_GALAXY_IDS)
    add_test(
      NAME "universelan-system-raw-p2p-offline-recipient-${GALAXY_VERSION}"
      COMMAND $<TARGET_FILE:${SYSTEM_TEST_RUNNER}>
        --manifest "${CMAKE_CURRENT_SOURCE_DIR}/Scenarios/raw-p2p-offline-recipient.json"
        --host $<TARGET_FILE:${SYSTEM_TEST_HOST}>
        --client-dll $<TARGET_FILE:${SYSTEM_TEST_CLIENT_TARGET}>
        --server $<TARGET_FILE:${SYSTEM_TEST_SERVER_TARGET}>
        --gog-runtime-dir "${CMAKE_SOURCE_DIR}/Source/DLLs/${GALAXY_VERSION_NUMBER}/gog"
        --runtime-name $<TARGET_FILE_NAME:${SYSTEM_TEST_CLIENT_TARGET}>
        --version "${GALAXY_VERSION_NUMBER}"
        --arch "${GALAXY_ARCH}"
    )
    set_tests_properties("universelan-system-raw-p2p-offline-recipient-${GALAXY_VERSION}" PROPERTIES
      TIMEOUT 30
      RUN_SERIAL TRUE
      RESOURCE_LOCK universelan-system-network
      LABELS system
      SKIP_REGULAR_EXPRESSION "SYSTEM_TEST SKIP"
    )
  endif()

  get_property(SYSTEM_TEST_HAS_ICHAT GLOBAL PROPERTY "GALAXY_${GALAXY_VERSION_NUMBER}_BUILD_FEATURE_HAS_ICHAT")
  get_property(SYSTEM_TEST_HAS_ICHAT_ROOMLISTENERS GLOBAL PROPERTY "GALAXY_${GALAXY_VERSION_NUMBER}_BUILD_FEATURE_HAS_ICHAT_ROOMLISTENERS")
  get_property(SYSTEM_TEST_HAS_ICHATROOMMESSAGERETRIEVELISTENER GLOBAL PROPERTY "GALAXY_${GALAXY_VERSION_NUMBER}_BUILD_FEATURE_HAS_ICHATROOMMESSAGERETRIEVELISTENER")
  get_property(SYSTEM_TEST_HAS_ICHAT_MESSAGETYPE GLOBAL PROPERTY "GALAXY_${GALAXY_VERSION_NUMBER}_BUILD_FEATURE_HAS_ICHAT_MESSAGETYPE")
  get_property(SYSTEM_TEST_HAS_IFRIENDS_ONPERSONADATACHANGED GLOBAL PROPERTY "GALAXY_${GALAXY_VERSION_NUMBER}_BUILD_FEATURE_IFRIENDS_ONPERSONADATACHANGED")
  get_property(SYSTEM_TEST_HAS_IFRIENDS_INFORMATIONLISTENERS GLOBAL PROPERTY "GALAXY_${GALAXY_VERSION_NUMBER}_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS")
  get_property(SYSTEM_TEST_HAS_FRIENDADDLISTENER GLOBAL PROPERTY "GALAXY_${GALAXY_VERSION_NUMBER}_BUILD_FEATURE_HAS_FRIENDADDLISTENER")
  get_property(SYSTEM_TEST_HAS_IGAMEINVITATIONRECEIVEDLISTENER GLOBAL PROPERTY "GALAXY_${GALAXY_VERSION_NUMBER}_BUILD_FEATURE_HAS_IGAMEINVITATIONRECEIVEDLISTENER")
  get_property(SYSTEM_TEST_HAS_GAMEJOINREQUESTEDLISTENER GLOBAL PROPERTY "GALAXY_${GALAXY_VERSION_NUMBER}_BUILD_FEATURE_HAS_GAMEJOINREQUESTEDLISTENER")
  get_property(SYSTEM_TEST_HAS_ISENDINVITATIONLISTENER GLOBAL PROPERTY "GALAXY_${GALAXY_VERSION_NUMBER}_BUILD_FEATURE_HAS_ISENDINVITATIONLISTENER")
  get_property(SYSTEM_TEST_HAS_IFRIENDS_SET_DEL_CLR_RICHPRESENCE GLOBAL PROPERTY "GALAXY_${GALAXY_VERSION_NUMBER}_BUILD_FEATURE_IFRIENDS_SET_DEL_CLR_RICHPRESENCE")
  get_property(SYSTEM_TEST_HAS_ADDED_RICH_PRESENCE_LISTENERS GLOBAL PROPERTY "GALAXY_${GALAXY_VERSION_NUMBER}_BUILD_FEATURE_ADDED_RICH_PRESENCE_LISTENERS")
  if(SYSTEM_TEST_HAS_ICHAT AND SYSTEM_TEST_HAS_ICHAT_ROOMLISTENERS AND SYSTEM_TEST_HAS_TYPED_GALAXY_IDS)
    add_test(
      NAME "universelan-system-chat-room-message-delivery-${GALAXY_VERSION}"
      COMMAND $<TARGET_FILE:${SYSTEM_TEST_RUNNER}>
        --manifest "${CMAKE_CURRENT_SOURCE_DIR}/Scenarios/chat-room-message-delivery.json"
        --host $<TARGET_FILE:${SYSTEM_TEST_HOST}>
        --client-dll $<TARGET_FILE:${SYSTEM_TEST_CLIENT_TARGET}>
        --server $<TARGET_FILE:${SYSTEM_TEST_SERVER_TARGET}>
        --gog-runtime-dir "${CMAKE_SOURCE_DIR}/Source/DLLs/${GALAXY_VERSION_NUMBER}/gog"
        --runtime-name $<TARGET_FILE_NAME:${SYSTEM_TEST_CLIENT_TARGET}>
        --version "${GALAXY_VERSION_NUMBER}"
        --arch "${GALAXY_ARCH}"
    )
    set_tests_properties("universelan-system-chat-room-message-delivery-${GALAXY_VERSION}" PROPERTIES
      TIMEOUT 45
      RUN_SERIAL TRUE
      RESOURCE_LOCK universelan-system-network
      LABELS system
      SKIP_REGULAR_EXPRESSION "SYSTEM_TEST SKIP"
    )
  endif()

  if(SYSTEM_TEST_HAS_ICHAT AND SYSTEM_TEST_HAS_TYPED_GALAXY_IDS)
    foreach(SYSTEM_TEST_CHAT_SCENARIO IN ITEMS chat-room-reuse chat-room-unknown-send-failure)
      add_test(
        NAME "universelan-system-${SYSTEM_TEST_CHAT_SCENARIO}-${GALAXY_VERSION}"
        COMMAND $<TARGET_FILE:${SYSTEM_TEST_RUNNER}>
          --manifest "${CMAKE_CURRENT_SOURCE_DIR}/Scenarios/${SYSTEM_TEST_CHAT_SCENARIO}.json"
          --host $<TARGET_FILE:${SYSTEM_TEST_HOST}>
          --client-dll $<TARGET_FILE:${SYSTEM_TEST_CLIENT_TARGET}>
          --server $<TARGET_FILE:${SYSTEM_TEST_SERVER_TARGET}>
          --gog-runtime-dir "${CMAKE_SOURCE_DIR}/Source/DLLs/${GALAXY_VERSION_NUMBER}/gog"
          --runtime-name $<TARGET_FILE_NAME:${SYSTEM_TEST_CLIENT_TARGET}>
          --version "${GALAXY_VERSION_NUMBER}"
          --arch "${GALAXY_ARCH}"
      )
      set_tests_properties("universelan-system-${SYSTEM_TEST_CHAT_SCENARIO}-${GALAXY_VERSION}" PROPERTIES
        TIMEOUT 45
        RUN_SERIAL TRUE
        RESOURCE_LOCK universelan-system-network
        LABELS system
        SKIP_REGULAR_EXPRESSION "SYSTEM_TEST SKIP"
      )
    endforeach()
  endif()

  if(SYSTEM_TEST_HAS_ICHAT AND SYSTEM_TEST_HAS_ICHAT_ROOMLISTENERS
      AND SYSTEM_TEST_HAS_ICHATROOMMESSAGERETRIEVELISTENER
      AND SYSTEM_TEST_HAS_ICHAT_MESSAGETYPE AND SYSTEM_TEST_HAS_TYPED_GALAXY_IDS)
    add_test(
      NAME "universelan-system-chat-room-history-retrieval-${GALAXY_VERSION}"
      COMMAND $<TARGET_FILE:${SYSTEM_TEST_RUNNER}>
        --manifest "${CMAKE_CURRENT_SOURCE_DIR}/Scenarios/chat-room-history-retrieval.json"
        --host $<TARGET_FILE:${SYSTEM_TEST_HOST}>
        --client-dll $<TARGET_FILE:${SYSTEM_TEST_CLIENT_TARGET}>
        --server $<TARGET_FILE:${SYSTEM_TEST_SERVER_TARGET}>
        --gog-runtime-dir "${CMAKE_SOURCE_DIR}/Source/DLLs/${GALAXY_VERSION_NUMBER}/gog"
        --runtime-name $<TARGET_FILE_NAME:${SYSTEM_TEST_CLIENT_TARGET}>
        --version "${GALAXY_VERSION_NUMBER}"
        --arch "${GALAXY_ARCH}"
    )
    set_tests_properties("universelan-system-chat-room-history-retrieval-${GALAXY_VERSION}" PROPERTIES
      TIMEOUT 45
      RUN_SERIAL TRUE
      RESOURCE_LOCK universelan-system-network
      LABELS system
      SKIP_REGULAR_EXPRESSION "SYSTEM_TEST SKIP"
    )
  endif()

   if(SYSTEM_TEST_HAS_IFRIENDS_ONPERSONADATACHANGED AND SYSTEM_TEST_HAS_IFRIENDS_INFORMATIONLISTENERS
      AND SYSTEM_TEST_HAS_FRIENDADDLISTENER AND SYSTEM_TEST_HAS_IGAMEINVITATIONRECEIVEDLISTENER
      AND SYSTEM_TEST_HAS_GAMEJOINREQUESTEDLISTENER AND SYSTEM_TEST_HAS_ISENDINVITATIONLISTENER
      AND SYSTEM_TEST_HAS_TYPED_GALAXY_IDS)
    add_test(
      NAME "universelan-system-online-persona-game-invitation-${GALAXY_VERSION}"
      COMMAND $<TARGET_FILE:${SYSTEM_TEST_RUNNER}>
        --manifest "${CMAKE_CURRENT_SOURCE_DIR}/Scenarios/online-persona-game-invitation.json"
        --host $<TARGET_FILE:${SYSTEM_TEST_HOST}>
        --client-dll $<TARGET_FILE:${SYSTEM_TEST_CLIENT_TARGET}>
        --server $<TARGET_FILE:${SYSTEM_TEST_SERVER_TARGET}>
        --gog-runtime-dir "${CMAKE_SOURCE_DIR}/Source/DLLs/${GALAXY_VERSION_NUMBER}/gog"
        --runtime-name $<TARGET_FILE_NAME:${SYSTEM_TEST_CLIENT_TARGET}>
        --version "${GALAXY_VERSION_NUMBER}"
        --arch "${GALAXY_ARCH}"
    )
    set_tests_properties("universelan-system-online-persona-game-invitation-${GALAXY_VERSION}" PROPERTIES
      TIMEOUT 45
      RUN_SERIAL TRUE
      RESOURCE_LOCK universelan-system-network
      LABELS system
      SKIP_REGULAR_EXPRESSION "SYSTEM_TEST SKIP"
    )
   endif()
   if(SYSTEM_TEST_HAS_ITELEMETRY)
     add_test(
       NAME "universelan-system-telemetry-local-event-result-${GALAXY_VERSION}"
       COMMAND $<TARGET_FILE:${SYSTEM_TEST_RUNNER}>
         --manifest "${CMAKE_CURRENT_SOURCE_DIR}/Scenarios/telemetry-local-event-result.json"
         --host $<TARGET_FILE:${SYSTEM_TEST_HOST}>
         --client-dll $<TARGET_FILE:${SYSTEM_TEST_CLIENT_TARGET}>
         --server $<TARGET_FILE:${SYSTEM_TEST_SERVER_TARGET}>
         --gog-runtime-dir "${CMAKE_SOURCE_DIR}/Source/DLLs/${GALAXY_VERSION_NUMBER}/gog"
         --runtime-name $<TARGET_FILE_NAME:${SYSTEM_TEST_CLIENT_TARGET}>
         --version "${GALAXY_VERSION_NUMBER}"
         --arch "${GALAXY_ARCH}"
     )
     set_tests_properties("universelan-system-telemetry-local-event-result-${GALAXY_VERSION}" PROPERTIES
       TIMEOUT 30
       RUN_SERIAL TRUE
       RESOURCE_LOCK universelan-system-network
       LABELS system
       SKIP_REGULAR_EXPRESSION "SYSTEM_TEST SKIP"
     )
   endif()

   if(SYSTEM_TEST_HAS_IFRIENDS_SET_DEL_CLR_RICHPRESENCE AND SYSTEM_TEST_HAS_ADDED_RICH_PRESENCE_LISTENERS)
    add_test(
      NAME "universelan-system-rich-presence-live-propagation-${GALAXY_VERSION}"
      COMMAND $<TARGET_FILE:${SYSTEM_TEST_RUNNER}>
        --manifest "${CMAKE_CURRENT_SOURCE_DIR}/Scenarios/rich-presence-live-propagation.json"
        --host $<TARGET_FILE:${SYSTEM_TEST_HOST}>
        --client-dll $<TARGET_FILE:${SYSTEM_TEST_CLIENT_TARGET}>
        --server $<TARGET_FILE:${SYSTEM_TEST_SERVER_TARGET}>
        --gog-runtime-dir "${CMAKE_SOURCE_DIR}/Source/DLLs/${GALAXY_VERSION_NUMBER}/gog"
        --runtime-name $<TARGET_FILE_NAME:${SYSTEM_TEST_CLIENT_TARGET}>
        --version "${GALAXY_VERSION_NUMBER}"
        --arch "${GALAXY_ARCH}"
    )
    set_tests_properties("universelan-system-rich-presence-live-propagation-${GALAXY_VERSION}" PROPERTIES
      TIMEOUT 45
      RUN_SERIAL TRUE
      RESOURCE_LOCK universelan-system-network
      LABELS system
      SKIP_REGULAR_EXPRESSION "SYSTEM_TEST SKIP"
    )
   endif()

   get_property(SYSTEM_TEST_HAS_ISTATS_UPDATE_1_125 GLOBAL PROPERTY "GALAXY_${GALAXY_VERSION_NUMBER}_BUILD_FEATURE_ISTATS_UPDATE_1_125")
   if(SYSTEM_TEST_HAS_IFRIENDS_SET_DEL_CLR_RICHPRESENCE AND SYSTEM_TEST_HAS_ADDED_RICH_PRESENCE_LISTENERS
       AND SYSTEM_TEST_HAS_ISTATS_UPDATE_1_125)
     add_test(
       NAME "universelan-system-stats-achievement-user-data-propagation-${GALAXY_VERSION}"
       COMMAND $<TARGET_FILE:${SYSTEM_TEST_RUNNER}>
         --manifest "${CMAKE_CURRENT_SOURCE_DIR}/Scenarios/stats-achievement-user-data-propagation.json"
         --host $<TARGET_FILE:${SYSTEM_TEST_HOST}>
         --client-dll $<TARGET_FILE:${SYSTEM_TEST_CLIENT_TARGET}>
         --server $<TARGET_FILE:${SYSTEM_TEST_SERVER_TARGET}>
         --gog-runtime-dir "${CMAKE_SOURCE_DIR}/Source/DLLs/${GALAXY_VERSION_NUMBER}/gog"
         --runtime-name $<TARGET_FILE_NAME:${SYSTEM_TEST_CLIENT_TARGET}>
         --version "${GALAXY_VERSION_NUMBER}"
         --arch "${GALAXY_ARCH}"
     )
     set_tests_properties("universelan-system-stats-achievement-user-data-propagation-${GALAXY_VERSION}" PROPERTIES
       TIMEOUT 45
       RUN_SERIAL TRUE
       RESOURCE_LOCK universelan-system-network
       LABELS system
       SKIP_REGULAR_EXPRESSION "SYSTEM_TEST SKIP"
     )
    endif()

     if(SYSTEM_TEST_HAS_ISTATS_UPDATE_1_125)
      add_test(
        NAME "universelan-system-stats-achievement-durable-persistence-${GALAXY_VERSION}"
        COMMAND $<TARGET_FILE:${SYSTEM_TEST_RUNNER}>
          --manifest "${CMAKE_CURRENT_SOURCE_DIR}/Scenarios/stats-achievement-durable-persistence.json"
          --host $<TARGET_FILE:${SYSTEM_TEST_HOST}>
          --client-dll $<TARGET_FILE:${SYSTEM_TEST_CLIENT_TARGET}>
          --server $<TARGET_FILE:${SYSTEM_TEST_SERVER_TARGET}>
          --gog-runtime-dir "${CMAKE_SOURCE_DIR}/Source/DLLs/${GALAXY_VERSION_NUMBER}/gog"
          --runtime-name $<TARGET_FILE_NAME:${SYSTEM_TEST_CLIENT_TARGET}>
          --version "${GALAXY_VERSION_NUMBER}"
          --arch "${GALAXY_ARCH}"
      )
      set_tests_properties("universelan-system-stats-achievement-durable-persistence-${GALAXY_VERSION}" PROPERTIES
        TIMEOUT 45
        RUN_SERIAL TRUE
        RESOURCE_LOCK universelan-system-network
        LABELS system
        SKIP_REGULAR_EXPRESSION "SYSTEM_TEST SKIP"
      )
    endif()

    get_property(SYSTEM_TEST_HAS_SPECIFICUSERDATALISTENER GLOBAL PROPERTY "GALAXY_${GALAXY_VERSION_NUMBER}_BUILD_FEATURE_HAS_SPECIFICUSERDATALISTENER")
   if(SYSTEM_TEST_HAS_SPECIFICUSERDATALISTENER AND SYSTEM_TEST_HAS_TYPED_GALAXY_IDS)
     add_test(
       NAME "universelan-system-user-data-live-propagation-${GALAXY_VERSION}"
       COMMAND $<TARGET_FILE:${SYSTEM_TEST_RUNNER}>
         --manifest "${CMAKE_CURRENT_SOURCE_DIR}/Scenarios/user-data-live-propagation.json"
         --host $<TARGET_FILE:${SYSTEM_TEST_HOST}>
         --client-dll $<TARGET_FILE:${SYSTEM_TEST_CLIENT_TARGET}>
         --server $<TARGET_FILE:${SYSTEM_TEST_SERVER_TARGET}>
         --gog-runtime-dir "${CMAKE_SOURCE_DIR}/Source/DLLs/${GALAXY_VERSION_NUMBER}/gog"
         --runtime-name $<TARGET_FILE_NAME:${SYSTEM_TEST_CLIENT_TARGET}>
         --version "${GALAXY_VERSION_NUMBER}"
         --arch "${GALAXY_ARCH}"
     )
     set_tests_properties("universelan-system-user-data-live-propagation-${GALAXY_VERSION}" PROPERTIES
       TIMEOUT 45
       RUN_SERIAL TRUE
       RESOURCE_LOCK universelan-system-network
       LABELS system
       SKIP_REGULAR_EXPRESSION "SYSTEM_TEST SKIP"
     )
   endif()

     get_property(SYSTEM_TEST_HAS_ICUSTOMNETWORKING GLOBAL PROPERTY "GALAXY_${GALAXY_VERSION_NUMBER}_BUILD_FEATURE_HAS_ICUSTOMNETWORKING")
  get_property(SYSTEM_TEST_HAS_ICONNECTIONLISTENERS GLOBAL PROPERTY "GALAXY_${GALAXY_VERSION_NUMBER}_BUILD_FEATURE_HAS_ICONNECTIONLISTENERS")
   if(SYSTEM_TEST_HAS_ICUSTOMNETWORKING AND SYSTEM_TEST_HAS_ICONNECTIONLISTENERS)
    add_test(
      NAME "universelan-system-custom-networking-echo-${GALAXY_VERSION}"
      COMMAND $<TARGET_FILE:${SYSTEM_TEST_RUNNER}>
        --manifest "${CMAKE_CURRENT_SOURCE_DIR}/Scenarios/custom-networking-echo.json"
        --host $<TARGET_FILE:${SYSTEM_TEST_HOST}>
        --client-dll $<TARGET_FILE:${SYSTEM_TEST_CLIENT_TARGET}>
        --server $<TARGET_FILE:${SYSTEM_TEST_SERVER_TARGET}>
        --gog-runtime-dir "${CMAKE_SOURCE_DIR}/Source/DLLs/${GALAXY_VERSION_NUMBER}/gog"
        --runtime-name $<TARGET_FILE_NAME:${SYSTEM_TEST_CLIENT_TARGET}>
        --version "${GALAXY_VERSION_NUMBER}"
        --arch "${GALAXY_ARCH}"
    )
    set_tests_properties("universelan-system-custom-networking-echo-${GALAXY_VERSION}" PROPERTIES
      TIMEOUT 45
      RUN_SERIAL TRUE
      RESOURCE_LOCK universelan-system-network
      LABELS system
      SKIP_REGULAR_EXPRESSION "SYSTEM_TEST SKIP"
    )
   endif()
   if(SYSTEM_TEST_HAS_ICUSTOMNETWORKING AND GALAXY_ARCH STREQUAL "x64")
     add_test(
       NAME "universelan-system-custom-networking-close-${GALAXY_VERSION}"
       COMMAND $<TARGET_FILE:${SYSTEM_TEST_RUNNER}>
         --manifest "${CMAKE_CURRENT_SOURCE_DIR}/Scenarios/custom-networking-close.json"
         --host $<TARGET_FILE:${SYSTEM_TEST_HOST}>
         --client-dll $<TARGET_FILE:${SYSTEM_TEST_CLIENT_TARGET}>
         --server $<TARGET_FILE:${SYSTEM_TEST_SERVER_TARGET}>
         --gog-runtime-dir "${CMAKE_SOURCE_DIR}/Source/DLLs/${GALAXY_VERSION_NUMBER}/gog"
         --runtime-name $<TARGET_FILE_NAME:${SYSTEM_TEST_CLIENT_TARGET}>
         --version "${GALAXY_VERSION_NUMBER}"
         --arch "${GALAXY_ARCH}"
     )
     set_tests_properties("universelan-system-custom-networking-close-${GALAXY_VERSION}" PROPERTIES
       TIMEOUT 45
       RUN_SERIAL TRUE
       RESOURCE_LOCK universelan-system-network
       LABELS system
       SKIP_REGULAR_EXPRESSION "SYSTEM_TEST SKIP"
     )
   endif()
endforeach()
