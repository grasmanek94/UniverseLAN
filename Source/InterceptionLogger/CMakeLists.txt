cmake_minimum_required(VERSION 3.12)

function(define_interception_logger GALAXY_VERSION)
  #message("-- define_interception_logger Version: ${GALAXY_VERSION}")

  file(GLOB_RECURSE INTERCEPT_LOGGER_SRC-${GALAXY_VERSION} CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/Source/InterceptionLogger/*.*")

  add_library(universelan-interception-logger-lib-${GALAXY_VERSION} STATIC ${INTERCEPT_LOGGER_SRC-${GALAXY_VERSION}} )

  target_include_directories(universelan-interception-logger-lib-${GALAXY_VERSION} PUBLIC "${CMAKE_SOURCE_DIR}/Source/InterceptionLogger/")
  target_compile_definitions(universelan-interception-logger-lib-${GALAXY_VERSION} PUBLIC "INTERCEPTION_LOGGER")
  add_version_definitions_to(universelan-interception-logger-lib-${GALAXY_VERSION})

  target_link_libraries(
    universelan-interception-logger-lib-${GALAXY_VERSION}
    PUBLIC universelan-common-shared-${GALAXY_VERSION}
  )
endfunction()
