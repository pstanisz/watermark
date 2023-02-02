// Copyright (c) 2023, Piotr Staniszewski
#pragma once

#include <cstdlib>
#include <cstdint>

#include <variant>

namespace watermark
{
    class Position
    {
    public:
        enum class Alignment : uint8_t
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

        using Margin = int;
        using Layout = std::pair<Alignment, Margin>;

        struct Point
        {
            int m_x;
            int m_y;

            bool operator==(const Point &) const = default;
            bool operator!=(const Point &) const = default;
        };

    public:
        explicit Position(int x, int y);
        explicit Position(const Point &point);
        explicit Position(Alignment alignment, Margin margin = 0);

        bool has_point() const noexcept;
        Point point() const;

        bool has_layout() const noexcept;
        Layout layout() const;

    private:
        std::variant<Point, Layout> m_position;
    };
}
