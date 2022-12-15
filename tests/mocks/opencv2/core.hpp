// Copyright (c) 2022, Piotr Staniszewski
#pragma once

#include <gtest/gtest.h>

namespace cv
{
    enum ImreadModes
    {
        IMREAD_COLOR = 1,
    };

    struct Size
    {
        int width;
        int height;
    };

    struct Mat
    {
        bool empty() const noexcept;
        Size size() const;
    };

    Mat imread([[maybe_unused]] const std::string &filename, [[maybe_unused]] int flags);
}