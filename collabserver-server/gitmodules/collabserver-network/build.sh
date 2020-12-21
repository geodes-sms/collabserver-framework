#!/bin/bash

set -x
set -v
set -e

mkdir build || true
cd build

cmake -DCMAKE_BUILD_TYPE=${ENV_BUILD_TYPE} \
      -DCOLLABSERVER_NETWORK_TESTS=ON \
      ..

make
make runTests


