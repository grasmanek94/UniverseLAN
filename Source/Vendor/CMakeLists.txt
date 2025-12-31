cmake_minimum_required(VERSION 3.12)

add_subdirectory(Enet-IPv6)
add_subdirectory(Enet++)
add_subdirectory(boost)
add_subdirectory(Detours)

if(MSVC)
add_subdirectory(StackWalker)
endif()

include(simpleini.cmake)
include(miniz-cpp.cmake)
include(magic_enum.cmake)

include(cereal.cmake)
include(websocketpp.cmake)

include(galaxy.cmake)
include(unet.cmake)
include(json.cmake)
