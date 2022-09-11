cmake_minimum_required(VERSION 3.12)

######################################################################################

project( lsfdrmfg )

enable_language( CXX )
enable_language( C )

set(CMAKE_CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)

include(enet.cmake)
include(version.cmake)
include(shared.cmake)
include(galaxy.cmake)
include(simpleini.cmake)
include(cereal.cmake)
include(client.cmake)
include(server.cmake)
