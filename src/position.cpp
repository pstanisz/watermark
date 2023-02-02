// Copyright (c) 2023, Piotr Staniszewski

#include <position.h>

#include <cassert>

namespace watermark
{

    PositionN::PositionN(int x, int y) : m_position{Point{x, y}} {}
    PositionN::PositionN(const Point &point) : m_position{point} {}
    PositionN::PositionN(Alignment alignment, Margin margin) : m_position{std::make_pair(alignment, margin)} {}

}
