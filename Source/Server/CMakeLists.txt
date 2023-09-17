cmake_minimum_required(VERSION 3.12)

function(define_server GALAXY_VERSION GALAXY_VERSION_NUMBER GALAXY_ARCH)
  #message("-- define_server Version: ${GALAXY_VERSION}")

  file(GLOB_RECURSE SERVER_SRC-${GALAXY_VERSION} CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/Source/Server/*.*")
  
  add_executable(universelan-server-${GALAXY_VERSION} ${SERVER_SRC-${GALAXY_VERSION}} )
  
  target_include_directories(universelan-server-${GALAXY_VERSION} PUBLIC "${CMAKE_SOURCE_DIR}/Source/Server/")
  target_compile_definitions(universelan-server-${GALAXY_VERSION} PUBLIC "SERVER" )
  add_version_definitions_to(universelan-server-${GALAXY_VERSION})

  target_link_libraries(
    universelan-server-${GALAXY_VERSION}
    PUBLIC universelan-common-shared-${GALAXY_VERSION}
  )
  

  set_target_properties(universelan-server-${GALAXY_VERSION} PROPERTIES 
    OUTPUT_NAME "UniverseLANServer${GALAXY_ARCH}"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${GALAXY_VERSION_NUMBER}/"
  )

  set_property(TARGET universelan-server-${GALAXY_VERSION} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${GALAXY_VERSION_NUMBER}/Debug/")

endfunction()
