# Copyright (c) 2023, Piotr Staniszewski

set(TARGET_NAME ${PROJECT_NAME}_cli)

file(GLOB SOURCES ./*.cpp)

add_executable(
    ${TARGET_NAME}
    ${SOURCES})

target_include_directories(
    ${TARGET_NAME}
    PUBLIC
    ${INC_DIR}
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
    ${PROJECT_NAME})
