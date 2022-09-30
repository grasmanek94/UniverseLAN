cmake_minimum_required(VERSION 3.12)

file(GLOB_RECURSE CLIENT_SRC CONFIGURE_DEPENDS "*.*")

add_library(lsfdrmfg-universelan-lib STATIC ${CLIENT_SRC} )

target_include_directories(lsfdrmfg-universelan-lib PUBLIC ".")
target_compile_definitions(lsfdrmfg-universelan-lib PUBLIC "CLIENT" )
target_link_libraries(
  lsfdrmfg-universelan-lib
  PUBLIC lsfdrmfg-common-shared websocketpp boost
)
