cmake_minimum_required(VERSION 3.12)

add_library(lsfdrmfg-magic_enum STATIC "dummy.c" )

target_include_directories(lsfdrmfg-magic_enum PUBLIC "magic_enum/include/")
