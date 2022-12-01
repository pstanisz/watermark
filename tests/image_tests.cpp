// Copyright (c) 2022, Piotr Staniszewski

#include <gtest/gtest.h>

#include <image.h>
#include <exception.h>

TEST(Image_test, test_empty_filepath)
{
    using namespace watermark;

    ASSERT_THROW({
        Image img{""};
    }, Image_exception);
}

TEST(Image_test, test_non_existing_filepath)
{
    using namespace watermark;

    ASSERT_THROW({
        Image img{"non_existing"};
    }, Image_exception);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}