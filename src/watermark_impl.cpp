// Copyright (c) 2023, Piotr Staniszewski

#include "watermark_impl.h"

#include <cassert>

namespace watermark
{

    Watermark_impl::Watermark_impl(Image &&watermark_img) : m_image{std::move(watermark_img)}
    {
    }

    Image &Watermark_impl::image()
    {
        return m_image;
    }
}