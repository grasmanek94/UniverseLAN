cmake_minimum_required(VERSION 3.12)

file(GLOB_RECURSE CLIENT_SRC CONFIGURE_DEPENDS "*.*")

add_library(lsfdrmfg-client SHARED ${CLIENT_SRC} )

target_include_directories(lsfdrmfg-client PUBLIC ".")
target_compile_definitions(lsfdrmfg-client PUBLIC "CLIENT" )

target_link_libraries(
    lsfdrmfg-client
    PUBLIC lsfdrmfg-common-shared
)

if (MSVC)
  if("${MSVC_C_ARCHITECTURE_ID}" STREQUAL "X86")
    list(APPEND CLIENT_SRC ../Galaxy.def)
    set_target_properties(lsfdrmfg-client PROPERTIES OUTPUT_NAME "Galaxy")
  elseif("${MSVC_C_ARCHITECTURE_ID}" STREQUAL "x64")
    list(APPEND CLIENT_SRC ../Galaxy64.def)
    set_target_properties(lsfdrmfg-client PROPERTIES OUTPUT_NAME "Galaxy64")
  endif()
endif()

