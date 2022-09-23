cmake_minimum_required(VERSION 3.12)

if (MSVC)
  if("${MSVC_C_ARCHITECTURE_ID}" STREQUAL "X86")
    file(GLOB_RECURSE CLIENT_FACTORY_SRC CONFIGURE_DEPENDS "*.*")

    add_library(lsfdrmfg-client SHARED ${CLIENT_FACTORY_SRC} )

    target_include_directories(lsfdrmfg-client PUBLIC ".")
    target_compile_definitions(lsfdrmfg-client PUBLIC "CLIENT_FACTORY" )

    target_link_libraries(lsfdrmfg-client PRIVATE lsfdrmfg-galaxy-lib)

    set_target_properties(lsfdrmfg-client PROPERTIES OUTPUT_NAME "Galaxy")
    target_sources(lsfdrmfg-client PUBLIC ${CMAKE_SOURCE_DIR}/UniverseLAN86.def)

  elseif("${MSVC_C_ARCHITECTURE_ID}" STREQUAL "x64")
    message(AUTHOR_WARNING "Factory not built when arch is x64")
  endif()
endif()
