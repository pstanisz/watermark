// Copyright (c) 2023, Piotr Staniszewski
#pragma once

#include <cstdint>

namespace watermark
{

    enum class Layout : uint8_t
    {
        Top_left = 0U,
        Top_middle,
        Top_right,
        Middle_left,
        Center,
        Middle_right,
        Bottom_left,
        Bottom_middle,
        Bottom_right
    };

}
