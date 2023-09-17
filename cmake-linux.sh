#!/bin/bash

rm -rf cmake-linux/
mkdir cmake-linux/
cd cmake-linux/

# GCC 13 or 14
cmake -D CMAKE_C_COMPILER=/usr/local/bin/gcc -D CMAKE_CXX_COMPILER=/usr/local/bin/g++ ..