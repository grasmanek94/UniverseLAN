cmake_minimum_required(VERSION 3.12)

function(define_shared GALAXY_VERSION)
  #message("-- define_shared Version: ${GALAXY_VERSION}")

  file(GLOB_RECURSE COMMON_SHARED_SRC-${GALAXY_VERSION} CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/Source/Shared/*.*")
  
  add_library(universelan-common-shared-${GALAXY_VERSION} STATIC ${COMMON_SHARED_SRC-${GALAXY_VERSION}} )
  
  target_include_directories(universelan-common-shared-${GALAXY_VERSION} PUBLIC "${CMAKE_SOURCE_DIR}/Source/Shared/")
  add_version_definitions_to(universelan-common-shared-${GALAXY_VERSION})
 
  target_link_libraries(
    universelan-common-shared-${GALAXY_VERSION}
    PUBLIC
      universelan-galaxy-${GALAXY_VERSION}
      universelan-magic_enum
      universelan-cereal
      universelan-enet
      universelan-simpleini
      universelan-common-version
      universelan-common-tracer
      $<$<PLATFORM_ID:Linux>:libtbb>
    PRIVATE
      $<$<PLATFORM_ID:Windows>:IPHLPAPI>
  )
endfunction()
