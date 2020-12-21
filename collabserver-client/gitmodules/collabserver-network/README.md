# CollabServer - Network

[![license](https://img.shields.io/badge/license-LGPLv3.0-blue.svg)](https://github.com/CollabServer/collabserver-network/blob/master/LICENSE.txt)
[![Build Status](https://travis-ci.org/CollabServer/collabserver-network.svg?branch=master)](https://travis-ci.org/CollabServer/collabserver-network)

| master | dev |
| :-----: | :-----: |
| [![Build Status](https://travis-ci.org/CollabServer/collabserver-network.svg?branch=master)](https://travis-ci.org/CollabServer/collabserver-network) | [![Build Status](https://travis-ci.org/CollabServer/collabserver-network.svg?branch=dev)](https://travis-ci.org/CollabServer/collabserver-network) |

## Overview

---

This is an internal library for the CollabServer framework. It provides the networking components such as messaging and sockets.

## Features

---

- Messaging system
- Socket wrapper

## Build (CMake)

---

- Requirements
  - [CMake](https://cmake.org/)
  - C++11
  - `pragma once` support
  - Tested with gcc 4.8.4
  - Tested with clang 5.0.0
  - Tested only on Linux. No support certified for Mac and Windows
- Dependencies (already in the repo and built by CMake)
  - [GoogleTest](https://github.com/google/googletest)
  - [MessagePack](https://msgpack.org/)
  - [ZeroMQ CPP](https://zeromq.org/languages/cplusplus/)
  - [ZeroMQ](http://zeromq.org/)

```bash
# Build the tests
mkdir build
cd build
cmake -DCOLLABSERVER_NETWORK_TESTS=ON ..
make
make runTests

# Or use the build script
./build.sh
```

| CMake option | Description |
| --- | --- |
| COLLABSERVER_NETWORK_TESTS | (ON / OFF) Set ON to build unit tests |
| CMAKE_BUILD_TYPE | Debug, Release, RelWithDebInfo, MinSizeRel |

## Generate Documentation

---

1. Install [Doxygen](https://www.stack.nl/~dimitri/doxygen/)
1. Run `doxygen Doxyfile`
1. Files are placed in `doc` folder

## Contribution

---

Feel free to ask me any question, share your ideas or open an issue.
I started this project during my master thesis at University of Montreal.
Format uses clang-format with the Google Coding style <https://google.github.io/styleguide/cppguide.html> (see `.clang-format` for further information).
Make sure you autoformat on save (see <https://clang.llvm.org/docs/ClangFormat.html>)
