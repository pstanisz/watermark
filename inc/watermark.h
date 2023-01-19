// Copyright (c) 2022, Piotr Staniszewski
#pragma once

#include <common.h>
#include <image.h>

#include <string>

namespace watermark
{
    class Watermark
    {
    public:
        explicit Watermark(Image &&watermark_img);
        ~Watermark() noexcept;

    private:
        Image m_image;
    };

    Image add_watermark(
        const Image &input_img,
        const Image &watermark_img,
        const Position &position,
        const Size &size);

}
