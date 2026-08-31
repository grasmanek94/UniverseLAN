cmake_minimum_required(VERSION 3.12)

add_library(boost STATIC empty.cxx )

target_compile_definitions(boost PUBLIC "BOOST_ALL_NO_LIB" )
target_include_directories(boost PUBLIC ".")
