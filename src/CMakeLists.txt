# Copyright (c) 2022, Piotr Staniszewski

set(TARGET_NAME ${PROJECT_NAME})

find_package(OpenCV REQUIRED)

file(GLOB SOURCES ${SRC_DIR}/*.cpp)

add_library(
    ${TARGET_NAME}
    SHARED
    ${SOURCES})

target_include_directories(
    ${TARGET_NAME}
    PUBLIC
    ${INC_DIR}
    ${OpenCV_INCLUDE_DIRS})

target_compile_options(
    ${TARGET_NAME}
    PUBLIC
    -Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wconversion -pedantic)

target_compile_features(
    ${TARGET_NAME}
    PUBLIC
    cxx_std_20)

target_link_libraries(
    ${TARGET_NAME}
    ${OpenCV_LIBS})
