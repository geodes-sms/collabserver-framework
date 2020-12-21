cmake_minimum_required(VERSION 3.14)
project(collabserver-client)
message(STATUS "Building project ${PROJECT_NAME}")

if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
    message(FATAL_ERROR "in-source build not allowed. Use another directory.")
endif()


# Compiler Flags
message(STATUS "Detected Operating System: ${CMAKE_SYSTEM_NAME}")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    message(WARNING "No CMAKE_BUILD_TYPE set for ${PROJECT_NAME}: uses default Release")
    message(WARNING "Available build types: Debug Release RelWithDebInfo MinSizeRel")
    set(CMAKE_BUILD_TYPE Release)
endif()
message(STATUS "CMAKE_BUILD_TYPE for ${PROJECT_NAME}: ${CMAKE_BUILD_TYPE}")


# Dependencies
message(STATUS "Adding dependencies for ${PROJECT_NAME}")
include_directories("${PROJECT_SOURCE_DIR}/gitmodules/collabserver-datatypes/include")
include_directories("${PROJECT_SOURCE_DIR}/gitmodules/collabserver-network/include")
add_subdirectory("${PROJECT_SOURCE_DIR}/gitmodules/collabserver-datatypes")
add_subdirectory("${PROJECT_SOURCE_DIR}/gitmodules/collabserver-network")

# TODO use zmq that is the collabserver-network, but this should be removed (and abstracted by collabserver-network)
include_directories("${PROJECT_SOURCE_DIR}/gitmodules/collabserver-network/extern/cppzmq-4.7.1")


# Library
include_directories("${PROJECT_SOURCE_DIR}/include")
file(GLOB_RECURSE srcFiles "${PROJECT_SOURCE_DIR}/src/*.cpp")
add_library(${PROJECT_NAME}-lib STATIC ${srcFiles})
target_link_libraries(${PROJECT_NAME}-lib collabserver-network-lib)


# Examples
option(COLLABSERVER_CLIENT_EXAMPLES "Build examples" OFF)
if(COLLABSERVER_CLIENT_EXAMPLES)
    message(STATUS "Building examples for ${PROJECT_NAME}")

    add_executable(${PROJECT_NAME}-example examples/exampleClient.cpp)
    add_custom_target(runExamples ${PROJECT_NAME}-example)
    target_link_libraries(${PROJECT_NAME}-example collabserver-client-lib pthread)
endif()


# Tests
option(COLLABSERVER_CLIENT_TESTS "Build Tests" OFF)
if(COLLABSERVER_CLIENT_TESTS)
    message(STATUS "Build tests for ${PROJECT_NAME}")
    enable_testing()

    include_directories("${PROJECT_SOURCE_DIR}/include/")
    file(GLOB_RECURSE srcFilesTests "${PROJECT_SOURCE_DIR}/tests/*.cpp")
    add_executable(${PROJECT_NAME}-tests ${srcFilesTests} ${srcFilesRoom})

    # Googletest dependency
    include_directories("${PROJECT_SOURCE_DIR}/extern/googletest/googletest/include/")
    add_subdirectory("${PROJECT_SOURCE_DIR}/extern/googletest-1.10.0")
    target_link_libraries(${PROJECT_NAME}-tests gtest)

    # Lib dependency
    target_link_libraries(${PROJECT_NAME}-tests collabserver-client-lib pthread)

    # Tests target
    add_test(NAME googletests COMMAND ${PROJECT_NAME}-tests)
    add_custom_target(runTests ${PROJECT_NAME}-tests)
endif()

