cmake_minimum_required(VERSION 3.12)

add_library(universelan-miniz-cpp STATIC "dummy.c" "miniz-cpp-nyq-miniz-version-upgrade/miniz_cpp.hpp" )

target_include_directories(universelan-simpleini PUBLIC "miniz-cpp-nyq-miniz-version-upgrade/")
