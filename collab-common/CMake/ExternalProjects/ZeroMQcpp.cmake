cmake_minimum_required(VERSION 2.8.2 FATAL_ERROR)

project(cppzmq-download NONE)

include(ExternalProject)
ExternalProject_Add(msgpack
    GIT_REPOSITORY      "https://github.com/zeromq/cppzmq.git"
    GIT_TAG             "v4.3.0"
    SOURCE_DIR          "${COLLAB_CPPZMQ_SOURCES}"
    BINARY_DIR          "${COLLAB_CPPZMQ_BUILD}"
    CONFIGURE_COMMAND   ""
    BUILD_COMMAND       ""
    INSTALL_COMMAND     ""
    TEST_COMMAND        ""
    CMAKE_ARGS          ""
)


