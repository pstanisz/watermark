// Copyright (c) 2023, Piotr Staniszewski
#include <size.h>
#include <exception.h>

#include <gmock/gmock.h>
#include <limits>

namespace watermark
{

    namespace test
    {
        constexpr const unsigned int MAX_UNSIGNED_INT = std::numeric_limits<unsigned int>::max();

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

        using Size_add_point_test_params = std::tuple<Size, Point, Size, bool>;
        class Size_add_point_test : public ::testing::TestWithParam<Size_add_point_test_params>
        {
        };

        TEST_P(Size_add_point_test, check_add_point)
        {
            const auto &[input_size, point, output_size, is_exception] = GetParam();

            if (is_exception)
            {
                ASSERT_THROW(input_size + point, Size_exception);
            }
            else
            {
                ASSERT_EQ(input_size + point, output_size);
            }
        }

        INSTANTIATE_TEST_CASE_P(
            Size_test,
            Size_add_point_test,
            ::testing::Values(
                std::make_tuple(Size{}, Point{}, Size{}, false),
                std::make_tuple(Size{0U, 0U}, Point{1U, 1U}, Size{1U, 1U}, false),
                std::make_tuple(Size{0U, 5U}, Point{1U, 0U}, Size{1U, 5U}, false),
                std::make_tuple(Size{5U, 0U}, Point{0U, 1U}, Size{5U, 1U}, false),
                std::make_tuple(Size{10U, 10U}, Point{0U, 0U}, Size{10U, 10U}, false),
                std::make_tuple(Size{10U, 10U}, Point{5U, 0U}, Size{15U, 10U}, false),
                std::make_tuple(Size{5U, 3U}, Point{0U, 2U}, Size{5U, 5U}, false),
                std::make_tuple(Size{999U, 1234U}, Point{100U, 200U}, Size{1099U, 1434U}, false),
                std::make_tuple(Size{MAX_UNSIGNED_INT, MAX_UNSIGNED_INT}, Point{0U, 0U}, Size{MAX_UNSIGNED_INT, MAX_UNSIGNED_INT}, false),
                std::make_tuple(Size{1U, MAX_UNSIGNED_INT}, Point{1U, 1U}, Size{}, true),
                std::make_tuple(Size{MAX_UNSIGNED_INT, 1U}, Point{1U, 1U}, Size{}, true),
                std::make_tuple(Size{MAX_UNSIGNED_INT, MAX_UNSIGNED_INT}, Point{1U, 1U}, Size{}, true)));

        using Size_sub_point_test_params = std::tuple<Size, Point, Size, bool>;
        class Size_sub_point_test : public ::testing::TestWithParam<Size_sub_point_test_params>
        {
        };

        TEST_P(Size_sub_point_test, check_subtract_point)
        {
            const auto &[input_size, point, output_size, is_exception] = GetParam();

            if (is_exception)
            {
                ASSERT_THROW(input_size - point, Size_exception);
            }
            else
            {
                ASSERT_EQ(input_size - point, output_size);
            }
        }

        INSTANTIATE_TEST_CASE_P(
            Size_test,
            Size_sub_point_test,
            ::testing::Values(
                std::make_tuple(Size{}, Point{}, Size{}, false),
                std::make_tuple(Size{0U, 0U}, Point{1U, 1U}, Size{}, true),
                std::make_tuple(Size{0U, 5U}, Point{1U, 0U}, Size{}, true),
                std::make_tuple(Size{5U, 0U}, Point{0U, 1U}, Size{}, true),
                std::make_tuple(Size{10U, 10U}, Point{0U, 0U}, Size{10U, 10U}, false),
                std::make_tuple(Size{10U, 10U}, Point{5U, 0U}, Size{5U, 10U}, false),
                std::make_tuple(Size{5U, 3U}, Point{0U, 2U}, Size{5U, 1U}, false),
                std::make_tuple(Size{999U, 1234U}, Point{100U, 200U}, Size{899U, 1034U}, false)));
    }
}
