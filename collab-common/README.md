# Collab Common

[![license](https://img.shields.io/badge/license-LGPLv3.0-blue.svg)](https://github.com/CollabServer/collab-common/blob/master/LICENSE.txt)
[![Build Status](https://travis-ci.org/CollabServer/collab-common.svg?branch=master)](https://travis-ci.org/CollabServer/collab-common)

| master | dev |
| :-----: | :-----: |
| [![Build Status](https://travis-ci.org/CollabServer/collab-common.svg?branch=master)](https://travis-ci.org/CollabServer/collab-common) | [![Build Status](https://travis-ci.org/CollabServer/collab-common.svg?branch=dev)](https://travis-ci.org/CollabServer/collab-common) |


# Overview
Common library used by both collab-server and collab-client-interface projects.


# Features
- Messaging system
- Network wrapper
- Utility components


# Build on Linux (CMake)
**Build static lib**
```bash
# Warning: be sure you have all the system-wide dependencies and requirements

mkdir build
cd build
cmake -DCOLLAB_DEPENDENCIES_DOWNLOAD=ON ..
make
```

**Build tests**
```bash
# Warning: be sure you have all the system-wide dependencies and requirements

mkdir build
cd build
cmake -DCOLLAB_DEPENDENCIES_DOWNLOAD=ON -DCOLLAB_TESTS=ON ..
make
make runTests

# Or use build script
./build.sh
```

**CMake options**

| CMake option name | Description |
| --- | --- |
| COLLAB_DEPENDENCIES_DIR | (STRING) Path to a directory where to find all dependencies (By default, uses current cmake build). If this option is not set but the environment variable `COLLAB_DEPENDENCIES_DIR` exists, this one is used instead of the default value. |
| COLLAB_DEPENDENCIES_DOWNLOAD | (ON/OFF) Set ON to also download dependencies at cmake time. This is useful the first time you setup the project. Dependencies are placed in COLLAB_DEPENDENCIES_DIR. (By default: OFF).|
| COLLAB_TESTS | (ON/OFF) Set ON to build unit tests |
| CMAKE_BUILD_TYPE | Debug, Release, RelWithDebInfo, MinSizeRel |


# Requirements
- C++11
- `pragma once` support
- Tested with gcc 4.8.4
- Tested with clang 5.0.0
- Tested only on Linux. **Not support certified for Mac and Windows**
- CMake (2.8.2 or higher)


# Dependencies
- System-Wide (**Must be installed manually**)
    - [ZeroMQ](http://zeromq.org/) (Release 3.1.1)
        - ArchLinux: `pacman -S zeromq`
        - Ubuntu: `apt-get install libzmq3 libzmq3-dev`
        - There is also a [Windows binary here](http://zeromq.org/distro:microsoft-windows) (Not tested yet)
- Automatically downloaded and built by CMake
    - [MessagePack](https://msgpack.org/)
    - [GoogleTest](https://github.com/google/googletest) (Release 1.8.1)

**Option: save dependencies for offline use**
> Dependencies downloaded by CMake are placed in the current CMake build folder
> (in `dependencies` folder).
> This is useful the firs time.
> To speedup the cmake process, you may keep these downloaded and built dependencies
> in a safe place and change the CMake dependencies path (See CMake options).

**Option: use environment variable for dependencies path**
> If `COLLAB_DEPENDENCIES_DIR` environment variable is set, CMake will use
> it as the current dependencies path.


# Generate Documentation
1. Install [Doxygen](https://www.stack.nl/~dimitri/doxygen/)
1. `doxygen Doxyfile`
1. Files are placed in `doc` folder


# Contribution
Feel free to ask me any question, share your ideas or open an issue.
I created this project during my master thesis at University of Montreal.
I generally try to follow the [Google C++ Coding Style](https://google.github.io/styleguide/cppguide.html)
with some exceptions (For instance, I use 4 space indentation).


# Author
- Constantin Masson ([constantinmasson.com](http://constantinmasson.com/))


