cmake_minimum_required(VERSION 3.12)

file(GLOB_RECURSE CLIENT_SRC_NO_VER CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/Source/Client_NoVer/*.*")

add_library(universelan-lib-no-ver STATIC ${CLIENT_SRC_NO_VER} )

target_include_directories(universelan-lib-no-ver PUBLIC "${CMAKE_SOURCE_DIR}/Source/Client_NoVer/")
target_compile_definitions(universelan-lib-no-ver PUBLIC "CLIENT_NO_VER")

target_link_libraries(
  universelan-lib-no-ver
  PUBLIC universelan-common-shared-no-ver websocketpp boost
)
