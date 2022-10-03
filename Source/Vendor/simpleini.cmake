cmake_minimum_required(VERSION 3.12)

add_library(lsfdrmfg-simpleini STATIC "simpleini-4.19/ConvertUTF.c" "simpleini-4.19/ConvertUTF.h" "simpleini-4.19/SimpleIni.h" )

target_include_directories(lsfdrmfg-simpleini PUBLIC "simpleini-4.19/")
