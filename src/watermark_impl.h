// Copyright (c) 2023, Piotr Staniszewski
#pragma once

#include "image.h"

#include <string>

namespace watermark
{
    class Watermark_impl
    {
    public:
        explicit Watermark_impl(Image &&watermark_img);
        ~Watermark_impl() noexcept = default;

        Image &image();

    private:
        Image m_image;
    };
}
