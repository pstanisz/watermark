// Copyright (c) 2023, Piotr Staniszewski
#pragma once

#include <cstdint>

namespace watermark
{

    struct Point
    {
        unsigned int m_x;
        unsigned int m_y;

        bool operator==(const Point &) const = default;
        bool operator!=(const Point &) const = default;
    };

}
