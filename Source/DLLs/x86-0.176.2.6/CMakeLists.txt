cmake_minimum_required(VERSION 3.12)

get_filename_component(GALAXY_VERSION ${CMAKE_CURRENT_SOURCE_DIR} NAME)

string(REPLACE "." "" GALAXY_VERSION_DEF ${GALAXY_VERSION})
string(REPLACE "x64-" "" GALAXY_VERSION_DEF ${GALAXY_VERSION_DEF})
string(REPLACE "x86-" "" GALAXY_VERSION_DEF ${GALAXY_VERSION_DEF})

define_galaxy(${GALAXY_VERSION})
define_shared(${GALAXY_VERSION})
define_client(${GALAXY_VERSION})
define_server(${GALAXY_VERSION})

include(factory.cmake)
include(factoryhost.cmake)