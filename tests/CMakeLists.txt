# Copyright (c) 2022, Piotr Staniszewski

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.1
)

FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

file(GLOB SOURCES ./*.cpp)

add_executable(watermark_tests ${SOURCES})

target_link_libraries(watermark_tests
    PRIVATE
    GTest::GTest)

add_test(NAME watermark_tests 
         COMMAND watermark_tests)