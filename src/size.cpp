// Copyright (c) 2023, Piotr Staniszewski

#include <size.h>

#include <cassert>

namespace watermark
{

    Size::Size(int width, int height) : m_size{Area{width, height}}
    {
    }

    Size::Size(const Area &area) : m_size{area}
    {
    }

    Size::Size(Fit fit) : m_size{fit}
    {
    }

    bool Size::has_area() const noexcept
    {
        return std::holds_alternative<Area>(m_size);
    }

    Size::Area Size::area() const
    {
        assert(has_area());

        return std::get<Area>(m_size);
    }

    bool Size::has_fit() const noexcept
    {
        return std::holds_alternative<Fit>(m_size);
    }

    Size::Fit Size::fit() const
    {
        assert(has_fit());

        return std::get<Fit>(m_size);
    }

    int Size::width() const
    {
        assert(has_area());

        return std::get<Area>(m_size).m_width;
    }

    int Size::height() const
    {
        assert(has_area());

        return std::get<Area>(m_size).m_height;
    }
}
