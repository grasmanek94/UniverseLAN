cmake_minimum_required(VERSION 3.12)

######################################################################################

project( lsfdrmfg )

enable_language( CXX )
enable_language( C )

if(MSVC)
  add_definitions(/MP)
  # Enable EHa 
  #string(REGEX REPLACE "/EHsc" "/EHa" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/)
file(COPY Config/ DESTINATION ${CMAKE_SOURCE_DIR}/bin/Debug/)
file(COPY Config/ DESTINATION ${CMAKE_SOURCE_DIR}/bin/Release/)

add_subdirectory(Source)
