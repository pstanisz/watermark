// Copyright (c) 2022, Piotr Staniszewski

#include <gtest/gtest.h>

TEST(Image_test, test_one)
{
    ASSERT_EQ(1, 1);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}