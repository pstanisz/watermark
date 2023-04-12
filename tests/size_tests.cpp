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

        using Size_ctor_test_params = std::tuple<unsigned int, unsigned int, bool>;
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
                std::make_tuple(1, 999, false),
                std::make_tuple(1234, 5678, false),
                std::make_tuple(99, 88, false)));

        using Size_eq_fits_in_test_params = std::tuple<Size, Size, bool, bool>;
        class Size_eq_fits_in_test : public ::testing::TestWithParam<Size_eq_fits_in_test_params>
        {
        };

        TEST_P(Size_eq_fits_in_test, check_equal_and_fits_in)
        {
            const auto &[size1, size2, equal, fits_in] = GetParam();

            ASSERT_EQ((size1 == size2), equal);
            ASSERT_EQ((size1 != size2), !equal);
            ASSERT_EQ(size1.fits_in(size2), fits_in);
        }

        INSTANTIATE_TEST_CASE_P(
            Size_test,
            Size_eq_fits_in_test,
            ::testing::Values(
                std::make_tuple(Size{}, Size{}, true, true),
                std::make_tuple(Size{0, 0}, Size{0, 0}, true, true),
                std::make_tuple(Size{0, 1}, Size{1, 0}, false, false),
                std::make_tuple(Size{10, 10}, Size{10, 10}, true, true),
                std::make_tuple(Size{10, 10}, Size{10, 20}, false, true),
                std::make_tuple(Size{20, 21}, Size{20, 20}, false, false),
                std::make_tuple(Size{1, 90}, Size{78, 90}, false, true),
                std::make_tuple(Size{1235, 5679}, Size{1234, 5678}, false, false),
                std::make_tuple(Size{11, 15}, Size{10, 15}, false, false),
                std::make_tuple(Size{111, 111}, Size{999, 999}, false, true)));
    }
}
