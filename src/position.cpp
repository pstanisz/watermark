// Copyright (c) 2023, Piotr Staniszewski

#include <position.h>

#include <cassert>

namespace watermark
{

    Position::Position(int x, int y) : m_position{Point{x, y}}
    {
    }

    Position::Position(const Point &point) : m_position{point}
    {
    }

    Position::Position(Alignment alignment, Margin margin) : m_position{std::make_pair(alignment, margin)}
    {
    }

    bool Position::has_point() const noexcept
    {
        return std::holds_alternative<Point>(m_position);
    }

    Position::Point Position::point() const
    {
        assert(has_point());

        return std::get<Point>(m_position);
    }

    bool Position::has_layout() const noexcept
    {
        return std::holds_alternative<Layout>(m_position);
    }

    Position::Layout Position::layout() const
    {
        assert(has_layout());
        
        return std::get<Layout>(m_position);
    }

}
