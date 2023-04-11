// Copyright (c) 2023, Piotr Staniszewski
#include <size.h>

#include <gmock/gmock.h>

namespace watermark
{

    namespace test
    {

        TEST(Size_test, check_default_ctor)
        {
            watermark::Size size{};
            ASSERT_TRUE(size.is_empty());
        }

        using Size_ctor_test_params = std::tuple<int, int, bool>;
        class Size_ctor_test : public ::testing::TestWithParam<Size_ctor_test_params>
        {
        };

        TEST_P(Size_ctor_test, check_ctor)
        {
            const auto &[width, height, empty] = GetParam();
            watermark::Size size{width, height};

            ASSERT_EQ(size.width(), width);
            ASSERT_EQ(size.height(), height);
            ASSERT_EQ(size.is_empty(), empty);
        }

        INSTANTIATE_TEST_CASE_P(
            Size_test,
            Size_ctor_test,
            ::testing::Values(
                std::make_tuple(0, 0, true),
                std::make_tuple(0, 10, true),
                std::make_tuple(10, 0, true),
                std::make_tuple(-1, 50, true),
                std::make_tuple(50, -2, true),
                std::make_tuple(1, 999, false),
                std::make_tuple(1234, 5678, false),
                std::make_tuple(99, 88, false)));
    }
}
