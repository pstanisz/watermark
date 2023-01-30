// Copyright (c) 2022, Piotr Staniszewski

#include <watermark.h>

#include "watermark_impl.h"
#include "image_impl.h"

#include <cassert>

namespace watermark
{

    Watermark::Watermark(Image &&watermark_img) : m_impl{new Watermark_impl(std::move(watermark_img))}
    {
    }

    Watermark::~Watermark() noexcept
    {
    }

    Image Watermark::apply_to(Image &source_img)
    {
        assert(m_impl != nullptr);
        assert(source_img.m_impl != nullptr);

        return Image(m_impl->apply(source_img.m_impl, m_impl->image().m_impl));
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
