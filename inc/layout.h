// Copyright (c) 2023, Piotr Staniszewski
#pragma once

#include <cstdint>

namespace watermark
{

    enum class Layoyut : uint8_t
    {
        Top_left = 0U,
        Top_middle,
        Top_right,
        Middle_left,
        Middle_middle,
        Middle_right,
        Bottom_left,
        Bottom_middle,
        Botton_right
    };

}
