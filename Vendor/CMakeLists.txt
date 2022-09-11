cmake_minimum_required(VERSION 3.12)

add_subdirectory(Enet)
include(simpleini.cmake)

add_library(lsfdrmfg-all-headers INTERFACE "dummy.h" )

include(galaxy.cmake)
include(cereal.cmake)


