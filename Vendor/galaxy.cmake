cmake_minimum_required(VERSION 3.12)

file(GLOB_RECURSE GALAXY_SRC CONFIGURE_DEPENDS "galaxy/Include/galaxy/*.*")

target_sources(lsfdrmfg-all-headers PUBLIC ${GALAXY_SRC})

target_include_directories(lsfdrmfg-all-headers INTERFACE "galaxy/Include/galaxy/")
target_compile_definitions(lsfdrmfg-all-headers INTERFACE "GALAXY_EXPORT" )
