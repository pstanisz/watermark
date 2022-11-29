# Copyright (c) 2022, Piotr Staniszewski

set(TARGET_NAME ${PROJECT_NAME}_proto)

find_package(OpenCV REQUIRED)

file(GLOB SOURCES ./*.cpp)

add_executable(
    ${TARGET_NAME}
    ${SOURCES})

target_include_directories(
    ${TARGET_NAME}
    PUBLIC
    ${OpenCV_INCLUDE_DIRS}
)

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
    PRIVATE
    ${OpenCV_LIBS})
