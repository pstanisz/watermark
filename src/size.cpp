// Copyright (c) 2023, Piotr Staniszewski

#include <size.h>

namespace watermark
{

    Size::Size(int width, int height) : m_width{width}, m_height{height}
    {
    }

    int Size::width() const noexcept
    {
        return m_width;
    }

    int Size::height() const noexcept
    {
        return m_height;
    }

    bool Size::is_empty() const noexcept
    {
        return (m_height <= 0 || m_width <= 0);
    }

    bool Size::fits_in(const Size &size) const noexcept
    {
        return ((m_height <= size.m_height) && (m_width <= size.m_width));
    }
}
