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
        if (m_impl)
        {
            delete m_impl;
            m_impl = nullptr;
        }
    }

    Watermark::Watermark(Watermark &&other) noexcept : m_impl{std::move(other.m_impl)}
    {
        other.m_impl = nullptr;
    }

    Watermark &Watermark::operator=(Watermark &&other) noexcept
    {
        m_impl = std::move(other.m_impl);
        other.m_impl = nullptr;

        return *this;
    }

    Image Watermark::apply_to(Image &source_img,
                              const Point &mark_pos,
                              const Size &mark_size,
                              Opacity opacity)
    {
        assert(m_impl != nullptr);
        assert(source_img.m_impl != nullptr);

        return Image(m_impl->apply(source_img.m_impl, m_impl->image().m_impl, mark_pos, mark_size, opacity));
    }

    Image Watermark::apply_to(Image &source_img,
                              Layout layout,
                              const Size &mark_size,
                              Opacity opacity)
    {
        assert(m_impl != nullptr);
        assert(source_img.m_impl != nullptr);

        return Image(m_impl->apply(source_img.m_impl, m_impl->image().m_impl, layout, mark_size, opacity));
    }

}
