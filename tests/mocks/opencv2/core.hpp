// Copyright (c) 2022, Piotr Staniszewski
#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

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
        bool empty() const noexcept { return m_empty; }
        Size size() const { return m_size; }

        bool m_empty;
        Size m_size;
    };

    Mat imread(const std::string &filename, int flags);
}
