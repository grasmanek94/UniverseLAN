cmake_minimum_required(VERSION 3.12)

file(GLOB_RECURSE DLLHOST_SRC CONFIGURE_DEPENDS "*.*")

add_executable(lsfdrmfg-dllhost ${DLLHOST_SRC} )

target_include_directories(lsfdrmfg-dllhost PUBLIC ".")
target_compile_definitions(lsfdrmfg-dllhost PUBLIC "DLLHOST" )

target_link_libraries(
    lsfdrmfg-dllhost
    PUBLIC lsfdrmfg-client lsfdrmfg-common-shared
)

if (MSVC)
  if("${MSVC_C_ARCHITECTURE_ID}" STREQUAL "X86")
    set_target_properties(lsfdrmfg-dllhost PROPERTIES OUTPUT_NAME "UniverseLANDllHost")
  elseif("${MSVC_C_ARCHITECTURE_ID}" STREQUAL "x64")
    set_target_properties(lsfdrmfg-dllhost PROPERTIES OUTPUT_NAME "UniverseLANDllHost64")
  endif()
endif()

set_property(TARGET lsfdrmfg-dllhost PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Config/")