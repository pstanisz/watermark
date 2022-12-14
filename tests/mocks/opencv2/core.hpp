// Copyright (c) 2022, Piotr Staniszewski
#pragma once

#include <gtest/gtest.h>

namespace cv
{
    enum ImreadModes
    {
        IMREAD_COLOR = 1,
    };

    struct Mat
    {
        bool empty() const noexcept { return true; }
    };

    Mat imread([[maybe_unused]] const std::string &filename, [[maybe_unused]] int flags)
    {
        return Mat();
    }
}