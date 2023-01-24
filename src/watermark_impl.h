// Copyright (c) 2023, Piotr Staniszewski
#pragma once

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

        Image_impl* foo(Image_impl& img, Image_impl& mark);

    private:
        Image m_image;
    };
}
