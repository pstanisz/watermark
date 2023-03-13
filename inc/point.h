// Copyright (c) 2023, Piotr Staniszewski
#pragma once

#include <cstdint>

namespace watermark
{

    struct Point
    {
        int m_x;
        int m_y;

        bool operator==(const Point &) const = default;
        bool operator!=(const Point &) const = default;
    };

}
