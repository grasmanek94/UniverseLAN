cmake_minimum_required(VERSION 3.12)

function(define_client GALAXY_VERSION)
  message("-- define_client Version: ${GALAXY_VERSION}")

  file(GLOB_RECURSE CLIENT_SRC-${GALAXY_VERSION} CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/Source/Client/*.*")

  add_library(lsfdrmfg-universelan-lib-${GALAXY_VERSION} STATIC ${CLIENT_SRC-${GALAXY_VERSION}} )

  target_include_directories(lsfdrmfg-universelan-lib-${GALAXY_VERSION} PUBLIC "${CMAKE_SOURCE_DIR}/Source/Client/")
  target_compile_definitions(lsfdrmfg-universelan-lib-${GALAXY_VERSION} PUBLIC "CLIENT")
  add_version_definitions_to(lsfdrmfg-universelan-lib-${GALAXY_VERSION})

  target_link_libraries(
    lsfdrmfg-universelan-lib-${GALAXY_VERSION}
    PUBLIC lsfdrmfg-common-shared-${GALAXY_VERSION} websocketpp boost
  )
endfunction()
