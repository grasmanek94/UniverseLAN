cmake_minimum_required(VERSION 3.12)

function(define_unet_library GALAXY_VERSION GALAXY_VERSION_NUMBER GALAXY_ARCH)
  message("-- define_unet_library Version: ${GALAXY_VERSION}")

  add_library(unet-lib-${GALAXY_VERSION} 
    "${CMAKE_SOURCE_DIR}/Source/Vendor/unet/src/Context.cpp"
    "${CMAKE_SOURCE_DIR}/Source/Vendor/unet/src/guid.cpp"
    "${CMAKE_SOURCE_DIR}/Source/Vendor/unet/src/Lobby.cpp"
    "${CMAKE_SOURCE_DIR}/Source/Vendor/unet/src/LobbyData.cpp"
    "${CMAKE_SOURCE_DIR}/Source/Vendor/unet/src/LobbyFile.cpp"
    "${CMAKE_SOURCE_DIR}/Source/Vendor/unet/src/LobbyInfo.cpp"
    "${CMAKE_SOURCE_DIR}/Source/Vendor/unet/src/LobbyListFilter.cpp"
    "${CMAKE_SOURCE_DIR}/Source/Vendor/unet/src/LobbyMember.cpp"
    "${CMAKE_SOURCE_DIR}/Source/Vendor/unet/src/NetworkMessage.cpp"
    "${CMAKE_SOURCE_DIR}/Source/Vendor/unet/src/Reassembly.cpp"
    "${CMAKE_SOURCE_DIR}/Source/Vendor/unet/src/Results"
    "${CMAKE_SOURCE_DIR}/Source/Vendor/unet/src/Service.cpp"
    "${CMAKE_SOURCE_DIR}/Source/Vendor/unet/src/Services"
    "${CMAKE_SOURCE_DIR}/Source/Vendor/unet/src/ServiceType.cpp"
    "${CMAKE_SOURCE_DIR}/Source/Vendor/unet/src/System"
    "${CMAKE_SOURCE_DIR}/Source/Vendor/unet/src/Unet_common.cpp"
    "${CMAKE_SOURCE_DIR}/Source/Vendor/unet/src/Unet.cpp"
    "${CMAKE_SOURCE_DIR}/Source/Vendor/unet/src/Utils.cpp"
#   "${CMAKE_SOURCE_DIR}/Source/Vendor/unet/src/xxhash.cpp" # XXH_PRIVATE_API == not include src!
    "${CMAKE_SOURCE_DIR}/Source/Vendor/unet/src/Services/ServiceGalaxy.cpp"
    "${CMAKE_SOURCE_DIR}/Source/Vendor/unet/src/Results/LobbyListResult.cpp"
   )
  
  target_include_directories(unet-lib-${GALAXY_VERSION} PUBLIC "${CMAKE_SOURCE_DIR}/Source/Vendor/unet/include/" )
  target_compile_definitions(unet-lib-${GALAXY_VERSION} PUBLIC "UNET_MODULE_GALAXY" "XXH_PRIVATE_API" )
  add_version_definitions_to(unet-lib-${GALAXY_VERSION})

  target_link_libraries(
    unet-lib-${GALAXY_VERSION}
    PUBLIC universelan-galaxy-${GALAXY_VERSION}
  )

  if(NOT MSVC)
    target_link_options(unet-lib-${GALAXY_VERSION} PRIVATE -static-libgcc -static-libstdc++)
    set_property(TARGET unet-lib-${GALAXY_VERSION} APPEND PROPERTY SOURCES
      "${CMAKE_SOURCE_DIR}/Source/Vendor/unet/src/System/SystemLinux.cpp"
    )

    target_link_libraries(
      unet-lib-${GALAXY_VERSION}
      PRIVATE uuid
    )

    target_compile_definitions(unet-lib-${GALAXY_VERSION} PRIVATE 
      "PLATFORM_LINUX"
      "GUID_LIBUUID"
    )
  else()
    set_property(TARGET unet-lib-${GALAXY_VERSION} APPEND PROPERTY SOURCES 
      "${CMAKE_SOURCE_DIR}/Source/Vendor/unet/src/System/SystemWindows.cpp"
    )

    target_compile_definitions(unet-lib-${GALAXY_VERSION} PRIVATE 
      "PLATFORM_WINDOWS" 
      "_CRT_SECURE_NO_WARNINGS" 
      "NOMINMAX" 
      "GUID_WINDOWS"
    )
  endif()

  set_target_properties(unet-lib-${GALAXY_VERSION} PROPERTIES 
    OUTPUT_NAME "unet-lib${GALAXY_ARCH}"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/test/${GALAXY_VERSION_NUMBER}/${UNIVERSELAN_EXTRA_BIN_FOLDER}"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/test/${GALAXY_VERSION_NUMBER}/${UNIVERSELAN_EXTRA_BIN_FOLDER}"
  )

  set_property(TARGET unet-lib-${GALAXY_VERSION} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/test/${GALAXY_VERSION_NUMBER}/Debug/")

endfunction()
