cmake_minimum_required(VERSION 3.0)

project(proto)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_subdirectory(${PROJECT_DIR})

