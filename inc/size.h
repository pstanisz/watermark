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
        explicit Size(int width, int height);

        int width() const noexcept;
        int height() const noexcept;

        bool operator==(const Size &) const = default;
        bool operator!=(const Size &) const = default;

        Size operator+(const Point &point);
        Size operator-(const Point &point);

        bool is_empty() const noexcept;
        bool fits_in(const Size &size) const noexcept;

    private:
        int m_width;
        int m_height;
    };
}
