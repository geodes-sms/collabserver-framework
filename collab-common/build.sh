#!/bin/bash

set -x
set -v
set -e

mkdir build || true
cd build

cmake -DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
      -DCOLLAB_DEPENDENCIES_DOWNLOAD=ON \
      -DCOLLAB_TESTS=ON \
      ..

make
make runTests


