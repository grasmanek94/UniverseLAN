#!/bin/bash

rm -rf cmake-linux-x64/
mkdir cmake-linux-x64/
cd cmake-linux-x64/

GALAXY_ARCH="x64"
BUILD_TYPE="Debug" # Release Debug RelWithDebInfo MinSizeRel
COMPILER_PATH=/usr/local/bin # GCC 13 or 14

cmake -D CMAKE_C_COMPILER="${COMPILER_PATH}/gcc" -D CMAKE_CXX_COMPILER="${COMPILER_PATH}/g++" -D GALAXY_ARCH="${GALAXY_ARCH}" -DCMAKE_BUILD_TYPE="${BUILD_TYPE}" ..
