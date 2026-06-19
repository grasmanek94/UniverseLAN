cmake_minimum_required(VERSION 3.12)

file(GLOB_RECURSE ENET_TEST_SRC CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/Source/EnetTest/*.*")

# Server

add_executable(enet-test-server ${ENET_TEST_SRC} )

target_include_directories(enet-test-server PUBLIC "${ENET_TEST_SRC}")
target_compile_definitions(enet-test-server PUBLIC "ENET_TEST_SERVER=1" )

target_link_libraries(
    enet-test-server

    PUBLIC
      enet-ipv6
    PRIVATE
        $<$<PLATFORM_ID:Windows>:Winmm>
        $<$<PLATFORM_ID:Windows>:Ws2_32>
)

if(NOT MSVC)
  target_link_options(enet-test-server PRIVATE -static-libgcc -static-libstdc++)
endif()

set_target_properties(enet-test-server PROPERTIES 
  OUTPUT_NAME "EnetTestServer"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/tests/EnetTests/"
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/tests/EnetTests/"
)

set_property(TARGET enet-test-server PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/tests/EnetTests/")

# Client

add_executable(enet-test-client ${ENET_TEST_SRC} )

target_include_directories(enet-test-client PUBLIC "${ENET_TEST_SRC}")
target_compile_definitions(enet-test-client PUBLIC "ENET_TEST_CLIENT=1" )

target_link_libraries(
    enet-test-client

    PUBLIC
      enet-ipv6
    PRIVATE
        $<$<PLATFORM_ID:Windows>:Winmm>
        $<$<PLATFORM_ID:Windows>:Ws2_32>
)

if(NOT MSVC)
  target_link_options(enet-test-client PRIVATE -static-libgcc -static-libstdc++)
endif()

set_target_properties(enet-test-client PROPERTIES 
  OUTPUT_NAME "EnetTestClient"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/tests/EnetTests/"
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/tests/EnetTests/"
)

set_property(TARGET enet-test-client PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/tests/EnetTests/")
