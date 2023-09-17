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

cmake -D CMAKE_C_COMPILER=/usr/local/bin/gcc -D CMAKE_CXX_COMPILER=/usr/local/bin/g++ -D GALAXY_ARCH="${GALAXY_ARCH}" ..