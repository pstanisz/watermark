# Copyright (c) 2022, Piotr Staniszewski

cmake_minimum_required(VERSION 3.0)

project(watermark)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(PROJECT_DIR ${CMAKE_SOURCE_DIR})
set(INC_DIR ${PROJECT_DIR}/inc)
set(SRC_DIR ${PROJECT_DIR}/src)
LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/")

set(TARGET_NAME ${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)

find_package(OpenCV REQUIRED)

file(GLOB SOURCES ${SRC_DIR}/*.cpp)

add_library(${TARGET_NAME} SHARED ${SOURCES})

target_include_directories(
    ${TARGET_NAME}
    PUBLIC
    ${INC_DIR}
    ${OpenCV_INCLUDE_DIRS}
)

target_compile_options(${TARGET_NAME} PUBLIC -Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wconversion -pedantic)
target_compile_features(${TARGET_NAME} PUBLIC cxx_std_20)
target_link_libraries(${TARGET_NAME} ${OpenCV_LIBS})

enable_testing()

add_subdirectory(tests)
add_subdirectory(tools/demo)
add_subdirectory(tools/proto)
