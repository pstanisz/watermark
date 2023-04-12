// Copyright(c) 2023, Piotr Staniszewski
#pragma once

#include "point.h"

#include <cstdlib>
#include <cstdint>

namespace watermark
{
    class Size
    {
    public:
        Size() = default;
        explicit Size(unsigned int width, unsigned int height);

        unsigned int width() const noexcept;
        unsigned int height() const noexcept;

        bool operator==(const Size &) const = default;
        bool operator!=(const Size &) const = default;

        Size operator+(const Point &point) const;
        Size operator-(const Point &point) const;

        bool is_empty() const noexcept;
        bool fits_in(const Size &size) const noexcept;

    private:
        unsigned int m_width{0U};
        unsigned int m_height{0U};
    };
}
