#!/bin/bash

rm -rf cmake-linux-x86/
mkdir cmake-linux-x86/
cd cmake-linux-x86/

GALAXY_ARCH="x86"
BUILD_TYPE="Debug" # Release Debug RelWithDebInfo MinSizeRel
COMPILER_PATH=/usr/local/bin # GCC 13 or 14

cmake -D CMAKE_C_COMPILER="${COMPILER_PATH}/gcc" -D CMAKE_CXX_COMPILER="${COMPILER_PATH}/g++" -D GALAXY_ARCH="${GALAXY_ARCH}" -DCMAKE_BUILD_TYPE="${BUILD_TYPE}" ..
