cmake_minimum_required(VERSION 3.12)

if(NOT BUILD_TEST_CASES)
  set(BUILD_TEST_CASES "" CACHE STRING "If enabled, all test cases will be built")
endif()

if(NOT BUILD_INTERCEPTOR)
  set(BUILD_INTERCEPTOR "" CACHE STRING "If enabled, builds GOG Galaxy SDK call interceptor+logger")
endif()

add_subdirectory(Vendor)
add_subdirectory(Version)
add_subdirectory(Tracer)
add_subdirectory(Shared)
add_subdirectory(Client)
if(BUILD_INTERCEPTOR)
  add_subdirectory(InterceptionLogger)
endif()
add_subdirectory(Server)
add_subdirectory(DLLs)

if(BUILD_TEST_CASES)
  add_subdirectory(TestCases)
endif()
