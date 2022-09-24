cmake_minimum_required(VERSION 3.12)

if (MSVC)
  if("${MSVC_C_ARCHITECTURE_ID}" STREQUAL "x64")
    message(AUTHOR_WARNING "Choosing Galaxy64.dll (x64, Native Mode)")

    file(GLOB_RECURSE CLIENT_SRC CONFIGURE_DEPENDS "*.*")

    add_library(lsfdrmfg-client SHARED ${CLIENT_SRC} )

    target_sources(lsfdrmfg-client PUBLIC ${CMAKE_SOURCE_DIR}/UniverseLAN64.def)
    set_target_properties(lsfdrmfg-client PROPERTIES OUTPUT_NAME "Galaxy64")

    target_include_directories(lsfdrmfg-client PUBLIC ".")
    target_compile_definitions(lsfdrmfg-client PUBLIC "CLIENT" )
    target_link_libraries(
      lsfdrmfg-client
      PRIVATE lsfdrmfg-common-shared websocketpp boost
    )

  elseif("${MSVC_C_ARCHITECTURE_ID}" STREQUAL "X86")
    message(AUTHOR_WARNING "Choosing Galaxy.dll (x86, Factory Mode)")

    file(GLOB_RECURSE CLIENT_SRC CONFIGURE_DEPENDS "*.*")

    add_library(lsfdrmfg-galaxy-lib STATIC ${CLIENT_SRC} )

    target_include_directories(lsfdrmfg-galaxy-lib PUBLIC ".")
    target_compile_definitions(lsfdrmfg-galaxy-lib PUBLIC "CLIENT" )
    target_link_libraries(
      lsfdrmfg-galaxy-lib
      PUBLIC lsfdrmfg-common-shared websocketpp boost
    )
    
  else()
    message(FATAL_ERROR "Cannot determine architecture")
  endif()
elseif()
  message(FATAL_ERROR "Currently only supports Windows")
endif()

