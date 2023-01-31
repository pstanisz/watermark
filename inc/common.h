// Copyright (c) 2022, Piotr Staniszewski
#pragma once

#include <cstdlib>

namespace watermark
{
    struct Position
    {
        int m_x;
        int m_y;

        bool operator==(const Position&) const = default;
        bool operator!=(const Position&) const = default;
    };

    struct Size
    {
        int m_width;
        int m_height;

        bool operator==(const Size&) const = default;
        bool operator!=(const Size&) const = default;
    };


}
