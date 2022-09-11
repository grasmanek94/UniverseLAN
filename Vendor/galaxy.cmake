cmake_minimum_required(VERSION 3.12)

file(GLOB_RECURSE GALAXY_SRC CONFIGURE_DEPENDS "galaxy/Include/galaxy/*.*")

add_library(lsfdrmfg-galaxy INTERFACE ${GALAXY_SRC} )

target_include_directories(lsfdrmfg-enet INTERFACE "galaxy/Include/galaxy/")
target_compile_definitions(lsfdrmfg-galaxy INTERFACE "GALAXY_EXPORT" )
