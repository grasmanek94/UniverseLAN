#!/bin/bash

rm -rf cmake-linux/
mkdir cmake-linux/
cd cmake-linux/

# GCC 13 or 14
GALAXY_ARCH="x$(getconf LONG_BIT)"

if [ "$GALAXY_ARCH" = "x64" ]; then
    echo "Using GALAXY_ARCH=x64"
else
    echo "Using GALAXY_ARCH=x86"
    GALAXY_ARCH="x86"
fi

BUILD_TYPE="Debug" # Release Debug RelWithDebInfo MinSizeRel
COMPILER_PATH=/usr/local/bin/

cmake -D CMAKE_C_COMPILER="${COMPILER_PATH}/gcc" -D CMAKE_CXX_COMPILER="${COMPILER_PATH}/g++" -D GALAXY_ARCH="${GALAXY_ARCH}" -DCMAKE_BUILD_TYPE="${BUILD_TYPE}" ..
