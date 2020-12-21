cmake_minimum_required(VERSION 3.14)
project(collabserver-network)
message(STATUS "Building project ${PROJECT_NAME}")

if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
    message(FATAL_ERROR "in-source build not allowed. Use another directory.")
endif()


# Compiler flags
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
include_directories("${PROJECT_SOURCE_DIR}/extern/cppzmq-4.7.1") # Header only
include_directories("${PROJECT_SOURCE_DIR}/extern/msgpack-c-3.3.0/include") # Header only
add_subdirectory("${PROJECT_SOURCE_DIR}/extern/libzmq-4.3.3")


# Library
message(STATUS "Building static library for ${PROJECT_NAME}")
include_directories("${PROJECT_SOURCE_DIR}/include/")
file(GLOB_RECURSE srcLibFiles "${PROJECT_SOURCE_DIR}/src/*.cpp")
add_library(${PROJECT_NAME}-lib STATIC ${srcLibFiles})
target_link_libraries(${PROJECT_NAME}-lib libzmq-static)


# Tests
option(COLLABSERVER_NETWORK_TESTS "Build tests" OFF)
if(COLLABSERVER_NETWORK_TESTS)
    message(STATUS "Building tests for ${PROJECT_NAME}")
    enable_testing()

    # Tests executable
    include_directories("${PROJECT_SOURCE_DIR}/include/")
    file(GLOB_RECURSE srcTestFiles "${PROJECT_SOURCE_DIR}/tests/*.cpp")
    add_executable(${PROJECT_NAME}-tests ${srcTestFiles})
    target_link_libraries(${PROJECT_NAME}-tests ${PROJECT_NAME}-lib)

    # Googletest dependency
    include_directories("${PROJECT_SOURCE_DIR}/extern/googletest/googletest/include/")
    add_subdirectory("${PROJECT_SOURCE_DIR}/extern/googletest-1.10.0")
    target_link_libraries(${PROJECT_NAME}-tests gtest)

    # Tests target
    add_test(NAME googletests COMMAND ${PROJECT_NAME}-tests)
    add_custom_target(runTests ${PROJECT_NAME}-tests)
endif()

