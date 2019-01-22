cmake_minimum_required(VERSION 2.8.2 FATAL_ERROR)
project(collab-client-interface)

if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
    message(FATAL_ERROR "in-source build not allowed. Use another directory.")
endif()


# ------------------------------------------------------------------------------
# Dependencies / Misc
# ------------------------------------------------------------------------------
set(COLLAB_GITMODULES_DIR "${CMAKE_SOURCE_DIR}/gitmodules/")

include("CMake/AddCompilerFlags.cmake")
include("CMake/AddDependencies.cmake")


# ------------------------------------------------------------------------------
# Client Interface (Static LIB)
# ------------------------------------------------------------------------------
include_directories("${CMAKE_SOURCE_DIR}/include")

file(GLOB_RECURSE srcFiles "${CMAKE_SOURCE_DIR}/src/*.cpp")

# DevNote:
# This is actually ugly and a big trick. The goal is to concat the static lib
# libcollabcommon straight into collabclient so that, the end user (Who uses
# collabclient). Doesn't have to know about collabcommon!!
# The 'best' way I found is to use extract both lib (ar -x) and create the
# final lib from all .o files.

add_library(collabclient_ONLY STATIC ${srcFiles})
add_dependencies(collabclient_ONLY collab-common)

set(COLLABCLIENT_LIB ${CMAKE_BINARY_DIR}/libcollabclient.a)
set(COLLABCOMMON_DIR "${CMAKE_BINARY_DIR}/collab-common-build")

add_custom_target(combine_common
    COMMAND ar -x $<TARGET_FILE:collabcommon>
    COMMAND ar -x $<TARGET_FILE:collabclient_ONLY>
    COMMAND ar -qcs "${COLLABCLIENT_LIB}" *.o
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
    DEPENDS collabclient_ONLY collabcommon
    )

add_library(collabclient STATIC IMPORTED GLOBAL)
add_dependencies(collabclient combine_common)
add_custom_target(buildCollabclient ALL DEPENDS collabclient)

set_target_properties(collabclient PROPERTIES
    IMPORTED_LOCATION "${COLLABCLIENT_LIB}")


# ------------------------------------------------------------------------------
# Examples
# ------------------------------------------------------------------------------
option(COLLAB_EXAMPLES "Build examples" OFF)

if(COLLAB_EXAMPLES)
    message(STATUS "Building examples")

    add_executable(exampleClient examples/exampleClient.cpp)
    add_custom_target(runExampleClient exampleClient)
    target_link_libraries(exampleClient collabclient zmq pthread)
endif()


# ------------------------------------------------------------------------------
# Tests
# ------------------------------------------------------------------------------
option(COLLAB_TESTS "Build tests" OFF)

if(COLLAB_TESTS)
    message(STATUS "Building tests")
    enable_testing()

    file(GLOB_RECURSE srcFilesTests "${CMAKE_SOURCE_DIR}/test/*.cpp")

    add_executable(tests ${srcFilesTests})
    add_test(NAME googletests COMMAND tests)
    add_custom_target(runTests tests)
    target_link_libraries(tests gtest collabclient zmq pthread)
endif()


