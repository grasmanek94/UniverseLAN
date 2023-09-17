cmake_minimum_required(VERSION 3.12)

######################################################################################

project( universelan )

set(CMAKE_CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_REQUIRED True)

enable_language( CXX )
enable_language( C )

if(MSVC)
  add_definitions(/MP)
  # Enable EHa 
  #string(REGEX REPLACE "/EHsc" "/EHa" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
else()
  set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/)

add_subdirectory(Source)
