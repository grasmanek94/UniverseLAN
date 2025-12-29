cmake_minimum_required(VERSION 3.13)

function(define_shared GALAXY_VERSION)
  #message("-- define_shared Version: ${GALAXY_VERSION}")

  file(GLOB_RECURSE COMMON_SHARED_SRC-${GALAXY_VERSION} CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/Source/Shared/*.*")
  
  add_library(universelan-common-shared-${GALAXY_VERSION} STATIC ${COMMON_SHARED_SRC-${GALAXY_VERSION}} )
  
  target_include_directories(universelan-common-shared-${GALAXY_VERSION} PUBLIC "${CMAKE_SOURCE_DIR}/Source/Shared/")
  add_version_definitions_to(universelan-common-shared-${GALAXY_VERSION})
 
  # Target Win 7
  target_compile_definitions(universelan-common-shared-${GALAXY_VERSION} PRIVATE
    $<$<PLATFORM_ID:Windows>:_WIN32_WINNT=0x0601>
    $<$<PLATFORM_ID:Windows>:WINVER=0x0601>
  )

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
      json
      $<$<PLATFORM_ID:Linux>:tbb>
    PRIVATE
      $<$<PLATFORM_ID:Windows>:IPHLPAPI>
      $<$<PLATFORM_ID:Windows>:Shell32>
      $<$<PLATFORM_ID:Windows>:Ole32>
  )
endfunction()
