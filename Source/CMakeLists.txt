cmake_minimum_required(VERSION 3.12)

if(NOT BUILD_INTERCEPTOR)
  set(BUILD_INTERCEPTOR "" CACHE STRING "If enabled, builds GOG Galaxy SDK call interceptor+logger")
endif()

add_subdirectory(Vendor)
add_subdirectory(Version)
add_subdirectory(Tracer)

add_subdirectory(Shared_NoVer)
add_subdirectory(Client_NoVer)

add_subdirectory(Shared)
add_subdirectory(Client)

if(BUILD_INTERCEPTOR)
  add_subdirectory(InterceptionLogger)
endif()

add_subdirectory(Server)
add_subdirectory(DLLs)

if(BUILD_UNIVERSELAN_SYSTEM_TESTS)
  add_subdirectory(SystemTests)
endif()

if(BUILD_UNIVERSELAN_UNIT_TESTS)
  add_subdirectory(UnitTests)
endif()

if(BUILD_UNIVERSELAN_TEST_CASES)
  add_subdirectory(TestCases)
  add_subdirectory(EnetTest)
endif()
