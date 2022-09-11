cmake_minimum_required(VERSION 3.12)

file(GLOB_RECURSE COMMON_VERSION_SRC CONFIGURE_DEPENDS "*.*")

add_library(lsfdrmfg-common-version STATIC ${COMMON_VERSION_SRC} )

target_include_directories(lsfdrmfg-common-version PUBLIC ".")

add_custom_target(
    custom_version_updater
    COMMAND ${CMAKE_SOURCE_DIR}/Util/UpdateVersion.bat
)

add_dependencies(lsfdrmfg-common-version custom_version_updater)
