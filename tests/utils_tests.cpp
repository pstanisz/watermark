// Copyright (c) 2023, Piotr Staniszewski
#include <utils.h>
#include <layout.h>
#include <point.h>
#include <size.h>

#include "mocks/cv_mock.h"

#include <gmock/gmock.h>
#include <tuple>

namespace watermark
{
    namespace mock
    {
        Imread_mock *g_imread_mock;
    }

    namespace test
    {

        TEST(Position_by_layout_test, assert_when_empty_source_size)
        {
            using namespace watermark;

            ASSERT_DEBUG_DEATH(position_by_layout(Layout::Center, Size(), Size(1, 1)), "source_size cannot be empty");
        }

        TEST(Position_by_layout_test, assert_when_empty_mark_size)
        {
            using namespace watermark;

            ASSERT_DEBUG_DEATH(position_by_layout(Layout::Center, Size(1, 1), Size(0, 0)), "mark_size cannot be empty");
        }

        TEST(Position_by_layout_test, assert_when_empty_source_size_and_empty_mark_size)
        {
            using namespace watermark;

            ASSERT_DEBUG_DEATH(position_by_layout(Layout::Center, Size(0, 0), Size(0, 0)), "cannot be empty");
        }

        using Position_by_layout_test_params = std::tuple<watermark::Layout, watermark::Size, watermark::Size, watermark::Point>;
        class Position_by_layout_test : public ::testing::TestWithParam<Position_by_layout_test_params>
        {
        };

        TEST_P(Position_by_layout_test, calculate_position_by_layout)
        {
            const auto &[layout, source_size, mark_size, expected_pos] = GetParam();
            auto point = position_by_layout(layout, source_size, mark_size);

            ASSERT_EQ(point, expected_pos);
        }

        INSTANTIATE_TEST_CASE_P(
            Utils_test,
            Position_by_layout_test,
            ::testing::Values(
                std::make_tuple(Layout::Top_left, Size(10, 10), Size(1, 1), Point(0, 0)),
                std::make_tuple(Layout::Top_middle, Size(10, 10), Size(1, 1), Point(5, 0)),
                std::make_tuple(Layout::Top_right, Size(10, 10), Size(1, 1), Point(9, 0)),
                std::make_tuple(Layout::Middle_left, Size(10, 10), Size(1, 1), Point(0, 5)),
                std::make_tuple(Layout::Center, Size(10, 10), Size(1, 1), Point(5, 5)),
                std::make_tuple(Layout::Middle_right, Size(10, 10), Size(1, 1), Point(9, 5)),
                std::make_tuple(Layout::Bottom_left, Size(10, 10), Size(1, 1), Point(0, 9)),
                std::make_tuple(Layout::Bottom_middle, Size(10, 10), Size(1, 1), Point(5, 9)),
                std::make_tuple(Layout::Bottom_right, Size(10, 10), Size(1, 1), Point(9, 9)),
                std::make_tuple(Layout::Top_left, Size(10, 10), Size(10, 10), Point(0, 0)),
                std::make_tuple(Layout::Top_middle, Size(10, 10), Size(10, 10), Point(0, 0)),
                std::make_tuple(Layout::Top_right, Size(10, 10), Size(10, 10), Point(0, 0)),
                std::make_tuple(Layout::Middle_left, Size(10, 10), Size(10, 10), Point(0, 0)),
                std::make_tuple(Layout::Center, Size(10, 10), Size(10, 10), Point(0, 0)),
                std::make_tuple(Layout::Middle_right, Size(10, 10), Size(10, 10), Point(0, 0)),
                std::make_tuple(Layout::Bottom_left, Size(10, 10), Size(10, 10), Point(0, 0)),
                std::make_tuple(Layout::Bottom_middle, Size(10, 10), Size(10, 10), Point(0, 0)),
                std::make_tuple(Layout::Bottom_right, Size(10, 10), Size(10, 10), Point(0, 0)),
                std::make_tuple(Layout::Top_left, Size(10, 10), Size(2, 2), Point(0, 0)),
                std::make_tuple(Layout::Top_middle, Size(10, 10), Size(2, 2), Point(4, 0)),
                std::make_tuple(Layout::Top_right, Size(10, 10), Size(2, 2), Point(8, 0)),
                std::make_tuple(Layout::Middle_left, Size(10, 10), Size(2, 2), Point(0, 4)),
                std::make_tuple(Layout::Center, Size(10, 10), Size(2, 2), Point(4, 4)),
                std::make_tuple(Layout::Middle_right, Size(10, 10), Size(2, 2), Point(8, 4)),
                std::make_tuple(Layout::Bottom_left, Size(10, 10), Size(2, 2), Point(0, 8)),
                std::make_tuple(Layout::Bottom_middle, Size(10, 10), Size(2, 2), Point(4, 8)),
                std::make_tuple(Layout::Bottom_right, Size(10, 10), Size(2, 2), Point(8, 8))));

    }
}
