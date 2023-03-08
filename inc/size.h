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
        enum class Fit : uint8_t
        {
            None = 0U, // Leaves the original size of mark
            To_height,
            To_width,
            To_image
        };

        struct Area
        {
            int m_width;
            int m_height;

            bool operator==(const Area &) const = default;
            bool operator!=(const Area &) const = default;

            bool is_empty() const;
        };

    public:
        explicit Size(int width, int height);
        explicit Size(const Area &area);
        explicit Size(Fit fit);

        bool has_area() const noexcept;
        Area area() const;

        bool has_fit() const noexcept;
        Fit fit() const;

        int width() const;
        int height() const;

        bool operator==(const Size &) const = default;
        bool operator!=(const Size &) const = default;

    private:
        std::variant<Area, Fit> m_size;
    };
}
