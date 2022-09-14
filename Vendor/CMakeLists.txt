cmake_minimum_required(VERSION 3.12)

add_subdirectory(Enet)
add_subdirectory(boost)

include(simpleini.cmake)

include(galaxy.cmake)
include(cereal.cmake)
include(websocketpp.cmake)