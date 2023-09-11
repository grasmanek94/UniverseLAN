cmake_minimum_required(VERSION 3.12)

function(define_shared GALAXY_VERSION)
  #message("-- define_shared Version: ${GALAXY_VERSION}")

  file(GLOB_RECURSE COMMON_SHARED_SRC-${GALAXY_VERSION} CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/Source/Shared/*.*")
  
  add_library(lsfdrmfg-common-shared-${GALAXY_VERSION} STATIC ${COMMON_SHARED_SRC-${GALAXY_VERSION}} )
  
  target_include_directories(lsfdrmfg-common-shared-${GALAXY_VERSION} PUBLIC "${CMAKE_SOURCE_DIR}/Source/Shared/")
  add_version_definitions_to(lsfdrmfg-common-shared-${GALAXY_VERSION})
 
  target_link_libraries(
    lsfdrmfg-common-shared-${GALAXY_VERSION}
    PUBLIC
      lsfdrmfg-galaxy-${GALAXY_VERSION}
      lsfdrmfg-cereal
      lsfdrmfg-enet
      lsfdrmfg-simpleini
      lsfdrmfg-common-version
      lsfdrmfg-common-tracer
    PRIVATE
      $<$<PLATFORM_ID:Windows>:IPHLPAPI>
  )
endfunction()
