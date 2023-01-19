// Copyright (c) 2022, Piotr Staniszewski
#pragma once

#include <common.h>
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

        Image& image();

        bool foo(Image_impl& img, Image_impl& mark);

    private:
        Watermark_impl *m_impl;
    };

    Image add_watermark(
        const Image &input_img,
        const Image &watermark_img,
        const Position &position,
        const Size &size);

}
