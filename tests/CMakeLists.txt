# Copyright (c) 2022, Piotr Staniszewski

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.12.1
)

FetchContent_MakeAvailable(googletest)
add_library(
    GTest::GTest 
    INTERFACE 
    IMPORTED)

target_link_libraries(
    GTest::GTest
    INTERFACE
    gtest_main)

set(TARGET_NAME ${PROJECT_NAME}_tests)

file(GLOB SOURCES ./*.cpp ${SRC_DIR}/*.cpp)

add_executable(
    ${TARGET_NAME}
    ${SOURCES}
    )

target_include_directories(
    ${TARGET_NAME}
    PRIVATE
    ${INC_DIR}
    mocks
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
    GTest::GTest)

add_test(
    NAME ${TARGET_NAME} 
    COMMAND ${TARGET_NAME})