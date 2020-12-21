# CollabServer - Client Interface

[![license](https://img.shields.io/badge/license-LGPLv3.0-blue.svg)](https://github.com/CollabServer/collabserver-client/blob/master/LICENSE.txt)
[![build-status-master](https://travis-ci.org/CollabServer/collabserver-client.svg?branch=master)](https://travis-ci.org/CollabServer/collabserver-client)

| master | dev |
| :-----: | :----: |
| [![build-status-master](https://travis-ci.org/CollabServer/collabserver-client.svg?branch=master)](https://travis-ci.org/CollabServer/collabserver-client) | [![build-status-master](https://travis-ci.org/CollabServer/collabserver-client.svg?branch=dev)](https://travis-ci.org/CollabServer/collabserver-client) |

## Overview

---

End-user interface to connect and work with a running instance of collab-server.

## Getting Started

---

1. Make sure you have all the requirements
1. Build this project (see build instructions)
1. Include the `collabdata` headers
1. Include the `collabclient` headers
1. Link your application with `libcollabclient.a` (built in the previous step)

## Features

---

- Server
  - Connect to a CollabServer
  - Disconnect from a CollabServer
- Data
  - Start a collaborative room for a data
  - Join a collaborative room for an existing data
  - Leave the current room

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
  - [collabserver-network](https://github.com/CollabServer/collabserver-network)
  - [collabserver-datatypes](https://github.com/CollabServer/collabserver-datatypes)

```bash
# Build the tests and examples

mkdir build
cd build
cmake -DCOLLABSERVER_CLIENT_TESTS=ON -DCOLLABSERVER_CLIENT_EXAMPLES=ON ..
make
make runTests
make runExamples

# Or use the build script
./build.sh
```

| CMake option | Description |
| --- | --- |
| COLLABSERVER_CLIENT_TESTS | (ON / OFF) Set ON to build unit tests |
| COLLABSERVER_CLIENT_EXAMPLES | (ON / OFF) Set ON to build examples |
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
