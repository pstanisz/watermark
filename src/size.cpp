// Copyright (c) 2023, Piotr Staniszewski

#include <size.h>
#include <exception.h>

#include <limits>

namespace watermark
{

    Size::Size(unsigned int width, unsigned int height) : m_width{width}, m_height{height}
    {
    }

    unsigned int Size::width() const noexcept
    {
        return m_width;
    }

    unsigned int Size::height() const noexcept
    {
        return m_height;
    }

    Size Size::operator+(const Point &point) const
    {
        if ((std::numeric_limits<unsigned int>::max() - m_width < point.m_x) ||
            (std::numeric_limits<unsigned int>::max() - m_height < point.m_y))
        {
            throw Size_exception("Cannot add point to size as it will result in overflow.");
        }
        return Size{m_width + point.m_x, m_height + point.m_y};
    }

    Size Size::operator-(const Point &point) const
    {
        if ((m_width < point.m_x) || (m_height < point.m_y))
        {
            throw Size_exception("Cannot subtract point from size as it will result in negative dimenstion(s).");
        }
        return Size{m_width - point.m_x, m_height - point.m_y};
    }

    bool Size::is_empty() const noexcept
    {
        return (m_height == 0U || m_width == 0U);
    }

    bool Size::fits_in(const Size &size) const noexcept
    {
        return ((m_height <= size.m_height) && (m_width <= size.m_width));
    }
}
