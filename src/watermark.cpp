// Copyright (c) 2022, Piotr Staniszewski

#include <watermark.h>

#include <iostream>

#include <opencv2/core/mat.hpp>

namespace watermark
{

    Watermark::Watermark(Image &&watermark_img) : m_image{std::move(watermark_img)}
    {
    }

    Watermark::~Watermark() noexcept
    {
    }

    Image add_watermark(
        [[maybe_unused]] const Image &input_img,
        [[maybe_unused]] const Image &watermark_img,
        [[maybe_unused]] const Position &position,
        [[maybe_unused]] const Size &size)
    {
        Image working{input_img.size()};

        // TODO

        return Image("");
    }

}
