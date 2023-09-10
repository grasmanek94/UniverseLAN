cmake_minimum_required(VERSION 3.12)

get_filename_component(GALAXY_VERSION ${CMAKE_CURRENT_SOURCE_DIR} NAME)

define_projects_for_version(${GALAXY_VERSION})

include(dll.cmake)
include(dllhost.cmake)