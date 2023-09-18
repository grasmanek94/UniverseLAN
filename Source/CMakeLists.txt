cmake_minimum_required(VERSION 3.12)

add_subdirectory(Vendor)
add_subdirectory(Version)
add_subdirectory(Tracer)
add_subdirectory(Shared)
add_subdirectory(Client)
add_subdirectory(Server)
add_subdirectory(DLLs)

if(NOT BUILD_TEST_CASES)
  set(BUILD_TEST_CASES "" CACHE STRING "If enabled, all test cases will be built")
endif()

if(BUILD_TEST_CASES)
  add_subdirectory(TestCases)
endif()
