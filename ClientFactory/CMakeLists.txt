cmake_minimum_required(VERSION 3.12)

file(GLOB_RECURSE CLIENT_FACTORY_SRC CONFIGURE_DEPENDS "*.*")

add_library(lsfdrmfg-client-factory SHARED ${CLIENT_FACTORY_SRC} )

target_include_directories(lsfdrmfg-client-factory PUBLIC ".")
target_compile_definitions(lsfdrmfg-client-factory PUBLIC "CLIENT_FACTORY" )

target_link_libraries(
    lsfdrmfg-client-factory
    PRIVATE lsfdrmfg-common-shared websocketpp boost lsfdrmfg-client-lib
)

if (MSVC)
  if("${MSVC_C_ARCHITECTURE_ID}" STREQUAL "X86")
    list(APPEND CLIENT_SRC ../UniverseLAN86-Factory.def)
    set_target_properties(lsfdrmfg-client PROPERTIES OUTPUT_NAME "GalaxyFactory")
  elseif("${MSVC_C_ARCHITECTURE_ID}" STREQUAL "x64")
    list(APPEND CLIENT_SRC ../UniverseLAN64-Factory.def)
    set_target_properties(lsfdrmfg-client PROPERTIES OUTPUT_NAME "GalaxyFactory64")
  endif()
endif()
