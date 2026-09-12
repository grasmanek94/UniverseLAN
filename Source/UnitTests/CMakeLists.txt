cmake_minimum_required(VERSION 3.16)

include(GoogleTest)

add_executable(universelan-common-shared-no-ver-unit-tests
  Shared_NoVer/AchievementDataTests.cxx
  Shared_NoVer/AchievementsAndStatsContainerTests.cxx
  Shared_NoVer/ConstHashTests.cxx
  Shared_NoVer/ContainerGetByIndexTests.cxx
  Shared_NoVer/GlobalUniqueIDTests.cxx
  Shared_NoVer/MemoryInputBufferTests.cxx
  Shared_NoVer/MemoryInputStreamTests.cxx
  Shared_NoVer/Networking/MessageUniqueIDTests.cxx
  Shared_NoVer/PreprocessorControlIfTests.cxx
  Shared_NoVer/SafeStringCopyTests.cxx
  Shared_NoVer/ConcurrentQueueTests.cxx
)

target_link_libraries(universelan-common-shared-no-ver-unit-tests PRIVATE
  universelan-common-shared-no-ver
  GTest::gtest_main
)

set_target_properties(universelan-common-shared-no-ver-unit-tests PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/tests/${UNIVERSELAN_EXTRA_BIN_FOLDER}"
)

gtest_discover_tests(universelan-common-shared-no-ver-unit-tests)

add_executable(universelan-client-no-ver-unit-tests
  Client_NoVer/DelayRunnerTests.cxx
  Client_NoVer/NotificationParamScopeExtenderTests.cxx
)

target_link_libraries(universelan-client-no-ver-unit-tests PRIVATE
  universelan-lib-no-ver
  GTest::gtest_main
)

set_target_properties(universelan-client-no-ver-unit-tests PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/tests/${UNIVERSELAN_EXTRA_BIN_FOLDER}"
)

gtest_discover_tests(universelan-client-no-ver-unit-tests)
