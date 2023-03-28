// Copyright (c) 2023, Piotr Staniszewski
#include <utils.h>
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

    TEST(Utils_test, first)
    {
        ASSERT_TRUE(true);
    }

}
