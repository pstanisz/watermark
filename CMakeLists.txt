# Copyright (c) 2022, Piotr Staniszewski

cmake_minimum_required(VERSION 3.20)

project(watermark)

message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(PROJECT_DIR ${CMAKE_SOURCE_DIR})
set(INC_DIR ${PROJECT_DIR}/inc)
set(SRC_DIR ${PROJECT_DIR}/src)

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(tools)
