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

  add_executable(${SYSTEM_TEST_HOST} SystemTestHost.cxx)
  target_include_directories(${SYSTEM_TEST_HOST} PRIVATE "${CMAKE_SOURCE_DIR}/Source/DLLs/${GALAXY_VERSION_NUMBER}/galaxy")
  target_link_libraries(${SYSTEM_TEST_HOST} PRIVATE ${SYSTEM_TEST_CLIENT_TARGET} ixwebsocket)
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

  add_executable(${SYSTEM_TEST_RUNNER} SystemTestRunner.cxx)
  target_link_libraries(${SYSTEM_TEST_RUNNER} PRIVATE json ixwebsocket)
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
  get_property(SYSTEM_TEST_HAS_TYPED_GALAXY_IDS GLOBAL PROPERTY "GALAXY_${GALAXY_VERSION_NUMBER}_BUILD_FEATURE_GALAXYID_HAS_IDTYPE")
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
  endif()

  if(SYSTEM_TEST_HAS_LOBBY_LISTENERS AND SYSTEM_TEST_HAS_TYPED_GALAXY_IDS)
    foreach(SYSTEM_TEST_P2P_SCENARIO IN ITEMS raw-p2p-bidirectional raw-p2p-three-peer-routing)
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

  get_property(SYSTEM_TEST_HAS_ICHAT GLOBAL PROPERTY "GALAXY_${GALAXY_VERSION_NUMBER}_BUILD_FEATURE_HAS_ICHAT")
  get_property(SYSTEM_TEST_HAS_ICHAT_ROOMLISTENERS GLOBAL PROPERTY "GALAXY_${GALAXY_VERSION_NUMBER}_BUILD_FEATURE_HAS_ICHAT_ROOMLISTENERS")
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
endforeach()
