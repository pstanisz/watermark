// Copyright(c) 2023, Piotr Staniszewski
#pragma once

#include <cstdlib>
#include <cstdint>

#include <variant>

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

        bool is_empty() const noexcept;

    private:
        int m_width;
        int m_height;
    };
}
