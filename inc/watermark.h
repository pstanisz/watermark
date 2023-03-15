// Copyright (c) 2022, Piotr Staniszewski
#pragma once

#include <common.h>
#include <point.h>
#include <size.h>
#include <layout.h>
#include <image.h>

#include <string>

namespace watermark
{
    class Watermark_impl;

    class Watermark
    {
    public:
        explicit Watermark(Image &&watermark_img);
        ~Watermark() noexcept;

        Watermark(const Watermark &) noexcept = delete;
        Watermark &operator=(const Watermark &) = delete;

        Watermark(Watermark &&other) noexcept;
        Watermark &operator=(Watermark &&other) noexcept;

        Image apply_to(Image &source_img,
                       const Point &mark_pos = Point{0U, 0U},
                       const Size &mark_size = Size{0U, 0U},
                       Opacity opacity = 1.0);

        Image apply_to(Image &source_img,
                       Layout layout,
                       const Size &mark_size = Size{0U, 0U},
                       Opacity opacity = 1.0);

    private:
        Watermark_impl *m_impl;
    };

}
