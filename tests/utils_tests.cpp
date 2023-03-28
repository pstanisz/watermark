// Copyright (c) 2023, Piotr Staniszewski
#include <utils.h>
#include <layout.h>
#include <point.h>
#include <size.h>

#include "mocks/cv_mock.h"

#include <gmock/gmock.h>

namespace watermark
{
    namespace mock
    {
        Imread_mock *g_imread_mock;
    }
}

namespace test
{

    // Point position_by_layout(Layout layout, const Size &source_size, const Size &mark_size)
    TEST(Utils_test, assert_when_empty_source_size)
    {
        using namespace watermark;

        ASSERT_DEBUG_DEATH(position_by_layout(Layout::Center, Size(), Size(1, 1)), "source_size cannot be empty");
    }

    TEST(Utils_test, assert_when_empty_mark_size)
    {
        using namespace watermark;

        ASSERT_DEBUG_DEATH(position_by_layout(Layout::Center, Size(1, 1), Size(0, 0)), "mark_size cannot be empty");
    }

    //TODO: parametrized
    TEST(Utils_test, returns_point_when_proper_size1)
    {
        using namespace watermark;

        auto point = position_by_layout(Layout::Center, Size(10, 10), Size(1, 1));
        ASSERT_EQ(point.m_x, 5);
        ASSERT_EQ(point.m_y, 5);
    }

    TEST(Utils_test, returns_point_when_proper_size2)
    {
        using namespace watermark;

        auto point = position_by_layout(Layout::Center, Size(10, 10), Size(10, 10));
        ASSERT_EQ(point.m_x, 0);
        ASSERT_EQ(point.m_y, 0);
    }

}
