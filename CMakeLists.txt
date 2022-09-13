cmake_minimum_required(VERSION 3.12)

######################################################################################

project( lsfdrmfg )

enable_language( CXX )
enable_language( C )

set(CMAKE_CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)

add_subdirectory(Vendor)
add_subdirectory(Common)
add_subdirectory(Client)
add_subdirectory(Server)
add_subdirectory(clientDllHost)