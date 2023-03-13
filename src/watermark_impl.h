// Copyright (c) 2023, Piotr Staniszewski
#pragma once

#include <point.h>

#include <string>

namespace watermark
{
    class Image;
    class Image_impl;

    class Watermark_impl
    {
    public:
        explicit Watermark_impl(Image &&watermark_img);
        ~Watermark_impl() noexcept = default;

        Image &image();

        Image_impl *apply(Image_impl *source_img,
                          Image_impl *mark_img,
                          const Point &mark_pos,
                          const Size &mark_size,
                          Opacity opacity);

        // TODO: new API using layout

    private:
        Image m_image;
    };
}
