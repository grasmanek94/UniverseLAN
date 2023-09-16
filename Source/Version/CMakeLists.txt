cmake_minimum_required(VERSION 3.12)

file(GLOB_RECURSE COMMON_VERSION_SRC CONFIGURE_DEPENDS "*.*")

add_library(universelan-common-version STATIC ${COMMON_VERSION_SRC} )

target_include_directories(universelan-common-version PUBLIC ".")

add_custom_target(
    custom_version_updater
    COMMAND ${CMAKE_SOURCE_DIR}/Util/UpdateVersion.bat
)

add_dependencies(universelan-common-version custom_version_updater)
