cmake_minimum_required(VERSION 3.12)

file(GLOB_RECURSE SERVER_SRC CONFIGURE_DEPENDS "*.*")

add_executable(lsfdrmfg-server ${SERVER_SRC} )

target_include_directories(lsfdrmfg-server PUBLIC ".")
target_compile_definitions(lsfdrmfg-server PUBLIC "SERVER" )

target_link_libraries(
    lsfdrmfg-server
    PUBLIC lsfdrmfg-common-shared
)

if (MSVC)
  if("${MSVC_C_ARCHITECTURE_ID}" STREQUAL "X86")
    set_target_properties(lsfdrmfg-server PROPERTIES OUTPUT_NAME "GalaxyServer")
  elseif("${MSVC_C_ARCHITECTURE_ID}" STREQUAL "x64")
    set_target_properties(lsfdrmfg-server PROPERTIES OUTPUT_NAME "GalaxyServer64")
  endif()
endif()

