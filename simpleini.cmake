cmake_minimum_required(VERSION 3.12)

file(GLOB SIMPLEINI_SRC CONFIGURE_DEPENDS "Vendor/simpleini-4.19/*.h")

add_library(lsfdrmfg-simpleini INTERFACE ${SIMPLEINI_SRC} )

target_include_directories(lsfdrmfg-simpleini INTERFACE "Vendor/simpleini-4.19/")
