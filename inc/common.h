// Copyright (c) 2022, Piotr Staniszewski
#pragma once

#include <cstdlib>
#include <cstdint>

namespace watermark
{
    struct Size
    {
        int m_width;
        int m_height;

        bool operator==(const Size &) const = default;
        bool operator!=(const Size &) const = default;
    };

    using Opacity = float;
}
