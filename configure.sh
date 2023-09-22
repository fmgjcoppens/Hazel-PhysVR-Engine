#!/usr/bin/env bash

# COMPILER=clang++
# CXXFLAGS='-Wall -Wextra -g -O0'
# BUILD_DIR=_build_linux

source vars.sh

cmake \
    -DCMAKE_CXX_COMPILER=${COMPILER} \
    -DCMAKE_CXX_FLAGS="${CXXFLAGS}" \
    -S . -B ${BUILD_DIR}
