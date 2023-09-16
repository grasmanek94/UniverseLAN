cmake_minimum_required(VERSION 3.12)

function(define_galaxy GALAXY_VERSION)
  #message("-- define_galaxy Version: ${GALAXY_VERSION}")

  file(GLOB_RECURSE GALAXY_SRC-${GALAXY_VERSION} CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/Source/DLLs/${GALAXY_VERSION}/galaxy/*.*")

  add_library(universelan-galaxy-${GALAXY_VERSION} STATIC ${GALAXY_SRC-${GALAXY_VERSION}})
  target_sources(universelan-galaxy-${GALAXY_VERSION} PRIVATE ${CMAKE_SOURCE_DIR}/Source/Vendor/dummy.c)

  target_include_directories(universelan-galaxy-${GALAXY_VERSION} PUBLIC "${CMAKE_SOURCE_DIR}/Source/DLLs/${GALAXY_VERSION}/galaxy/")
  target_compile_definitions(universelan-galaxy-${GALAXY_VERSION} PUBLIC "GALAXY_EXPORT")
  add_version_definitions_to(universelan-galaxy-${GALAXY_VERSION})

endfunction()
