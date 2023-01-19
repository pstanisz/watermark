// Copyright (c) 2022, Piotr Staniszewski

#include <watermark.h>

#include "watermark_impl.h"

#include <cassert>

namespace watermark
{

    Watermark::Watermark(Image &&watermark_img) : m_impl{new Watermark_impl(std::move(watermark_img))}
    {
    }

    Watermark::~Watermark() noexcept
    {
    }

    Image &Watermark::image()
    {
        assert(m_impl != nullptr);

        return m_impl->image();
    }

    bool Watermark::foo([[maybe_unused]]Image_impl& img, [[maybe_unused]]Image_impl& mark)
    {
        assert(m_impl != nullptr);

        //TODO: whatever needed with img internals

        return true;
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
