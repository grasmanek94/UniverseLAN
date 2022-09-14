cmake_minimum_required(VERSION 3.12)

file(GLOB_RECURSE BOOST_SRC CONFIGURE_DEPENDS "libs/**/src/*.*")

add_library(boost STATIC ${BOOST_SRC} )

target_compile_definitions(boost PRIVATE "")
target_compile_definitions(boost PUBLIC "BOOST_ALL_NO_LIB" )
target_include_directories(boost PUBLIC ".")
