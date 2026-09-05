#!/bin/bash
set -euo pipefail

GALAXY_ARCH="x86"

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="${SCRIPT_DIR}/cmake-linux-${GALAXY_ARCH}"
SOURCE_DIR="${SCRIPT_DIR}"

rm -rf "${BUILD_DIR}"
mkdir -p "${BUILD_DIR}"

BUILD_TYPE="Debug" # Release Debug RelWithDebInfo MinSizeRel
COMPILER_PATH="/usr/bin" # GCC 13 or 14

cmake   -S "${SOURCE_DIR}"   -B "${BUILD_DIR}"   -D CMAKE_C_COMPILER="${COMPILER_PATH}/gcc"   -D CMAKE_CXX_COMPILER="${COMPILER_PATH}/g++"   -D GALAXY_ARCH="${GALAXY_ARCH}"   -D CMAKE_BUILD_TYPE="${BUILD_TYPE}"
