cmake_minimum_required(VERSION 3.12)

add_library(universelan-simpleini STATIC "simpleini-4.22/ConvertUTF.c" "simpleini-4.22/ConvertUTF.h" "simpleini-4.22/SimpleIni.h" )

target_include_directories(universelan-simpleini PUBLIC "simpleini-4.22/")
