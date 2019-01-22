cmake_minimum_required(VERSION 2.8.2 FATAL_ERROR)
project(collab-common)

if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
    message(FATAL_ERROR "in-source build not allowed. Use another directory.")
endif()


# ------------------------------------------------------------------------------
# Dependencies and Misc
# ------------------------------------------------------------------------------
include("CMake/AddCompilerFlags.cmake")
include("CMake/AddDependencies.cmake")


# ------------------------------------------------------------------------------
# Static lib and Object lib
# ------------------------------------------------------------------------------
message(STATUS "Building static library")
include_directories("${CMAKE_SOURCE_DIR}/include/")
file(GLOB_RECURSE srcCommonFiles "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_library(collabcommon STATIC ${srcCommonFiles})


# ------------------------------------------------------------------------------
# Tests
# ------------------------------------------------------------------------------
option(COLLAB_TESTS "Build tests" OFF)

if(COLLAB_TESTS)
    message(STATUS "Building tests")
    enable_testing()

    file(GLOB_RECURSE srcFilesTests "${CMAKE_SOURCE_DIR}/test/*.cpp")

    add_executable(tests ${srcFilesTests})
    target_link_libraries(tests collabcommon gtest zmq)

    add_test(NAME googletests COMMAND tests)
    add_custom_target(runTests tests)
endif()


