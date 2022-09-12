cmake_minimum_required(VERSION 3.12)

file(GLOB_RECURSE GALAXY_SRC CONFIGURE_DEPENDS "galaxy/Include/galaxy/*.*")

add_library(lsfdrmfg-galaxy STATIC ${GALAXY_SRC})
target_sources(lsfdrmfg-galaxy PRIVATE dummy.c)

target_include_directories(lsfdrmfg-galaxy PUBLIC "galaxy/Include/galaxy/")
target_compile_definitions(lsfdrmfg-galaxy PUBLIC "GALAXY_EXPORT" )
