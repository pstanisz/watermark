// Copyright (c) 2022, Piotr Staniszewski
#pragma once

#include <cstdlib>
#include <cstdint>

namespace watermark
{
    struct Position1
    {
        int m_x;
        int m_y;

        bool operator==(const Position1 &) const = default;
        bool operator!=(const Position1 &) const = default;
    };

    struct Position2
    {
        enum class A : uint8_t
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

        union
        {
            A pos1;
            Position1 pos2;
        };

        enum class Type : uint8_t {
            Pos1 = 0,
            Pos2
        };

        Position2(int x, int y) : pos2{x, y}, m_type{Type::Pos2}
        {
        }

        Position2(Position2::A pos) : pos1(pos), m_type{Type::Pos1}
        {
        }

        bool operator==(const Position2 &) const = default;
        bool operator!=(const Position2 &) const = default;

        Type m_type;
    };

    // Experimental
    using Position = Position2;

    struct Size
    {
        int m_width;
        int m_height;

        bool operator==(const Size &) const = default;
        bool operator!=(const Size &) const = default;
    };

    using Opacity = float;
}
