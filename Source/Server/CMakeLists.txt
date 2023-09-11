cmake_minimum_required(VERSION 3.12)

function(define_server GALAXY_VERSION)
  #message("-- define_server Version: ${GALAXY_VERSION}")

  file(GLOB_RECURSE SERVER_SRC-${GALAXY_VERSION} CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/Source/Server/*.*")
  
  add_executable(lsfdrmfg-server-${GALAXY_VERSION} ${SERVER_SRC-${GALAXY_VERSION}} )
  
  target_include_directories(lsfdrmfg-server-${GALAXY_VERSION} PUBLIC "${CMAKE_SOURCE_DIR}/Source/Server/")
  target_compile_definitions(lsfdrmfg-server-${GALAXY_VERSION} PUBLIC "SERVER" )
  add_version_definitions_to(lsfdrmfg-server-${GALAXY_VERSION})

  target_link_libraries(
    lsfdrmfg-server-${GALAXY_VERSION}
    PUBLIC lsfdrmfg-common-shared-${GALAXY_VERSION}
  )
  
  if (MSVC)
    if("${MSVC_C_ARCHITECTURE_ID}" STREQUAL "X86")
      set_target_properties(lsfdrmfg-server-${GALAXY_VERSION} PROPERTIES OUTPUT_NAME "UniverseLANServer-${GALAXY_VERSION}")
    elseif("${MSVC_C_ARCHITECTURE_ID}" STREQUAL "x64")
      set_target_properties(lsfdrmfg-server-${GALAXY_VERSION} PROPERTIES OUTPUT_NAME "UniverseLANServer64-${GALAXY_VERSION}")
    endif()
  endif()
  
  set_property(TARGET lsfdrmfg-server-${GALAXY_VERSION} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/Debug/")
endfunction()
