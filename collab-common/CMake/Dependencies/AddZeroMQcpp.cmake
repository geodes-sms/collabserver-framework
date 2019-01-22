# ------------------------------------------------------------------------------
# Download ZMQ (CPP Header) at cmake time
# Inspired from googletest
# See: https://github.com/google/googletest/tree/master/googletest
# ------------------------------------------------------------------------------

# Alias variables
set(COLLAB_CPPZMQ_DIR      "${COLLAB_DEPENDENCIES_DIR}/cppzmq")

set(COLLAB_CPPZMQ_SOURCES  "${COLLAB_CPPZMQ_DIR}/sources")
set(COLLAB_CPPZMQ_HEADERS  "${COLLAB_CPPZMQ_DIR}/include")
set(COLLAB_CPPZMQ_DOWNLOAD "${CMAKE_BINARY_DIR}/cppzmq-download")
set(COLLAB_CPPZMQ_BUILD    "${CMAKE_BINARY_DIR}/cppzmq-build")


if(COLLAB_DEPENDENCIES_DOWNLOAD)
    # Create dep folder content
    file(MAKE_DIRECTORY "${COLLAB_CPPZMQ_SOURCES}")
    file(MAKE_DIRECTORY "${COLLAB_CPPZMQ_HEADERS}")


    # Create Download CMakeLists
    configure_file(
        "${CMAKE_SOURCE_DIR}/CMake/ExternalProjects/ZeroMQcpp.cmake"
        "${COLLAB_CPPZMQ_DOWNLOAD}/CMakeLists.txt")

    # Setup Download (in download folder)
    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY "${COLLAB_CPPZMQ_DOWNLOAD}")
    if(result)
        message(FATAL_ERROR "CMake step for CPP ZeroMQ failed: ${result}")
    endif()

    # Clone (in sources folder)
    execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY "${COLLAB_CPPZMQ_DOWNLOAD}")
    if(result)
        message(FATAL_ERROR "Build step for CPP ZeroMQ failed: ${result}")
    endif()

    # Copy headers (To follow dependency folder style)
    file(COPY "${COLLAB_CPPZMQ_SOURCES}/zmq.hpp"
         DESTINATION "${COLLAB_CPPZMQ_HEADERS}")
    file(COPY "${COLLAB_CPPZMQ_SOURCES}/zmq_addon.hpp"
         DESTINATION "${COLLAB_CPPZMQ_HEADERS}")

elseif(NOT IS_DIRECTORY "${COLLAB_CPPZMQ_DIR}")
    message("WARNING: CPP ZeroMQ dependency is missing.")
    message("To download it automatically, set -DCOLLAB_DEPENDENCIES_DOWNLOAD=ON")
    message(FATAL_ERROR "Missing dependency...")
endif()


include_directories("${COLLAB_CPPZMQ_HEADERS}")


