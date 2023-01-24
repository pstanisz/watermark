// Copyright (c) 2022, Piotr Staniszewski

#include <image.h>
#include <exception.h>

#include <cassert>

#include "image_impl.h"
#include "watermark.h"

namespace watermark
{

    Image::Image(const std::string &img_path) : m_impl{new Image_impl(img_path)}
    {
    }

    Image::Image(const Size &img_size) : m_impl{new Image_impl(img_size)}
    {
    }

    Image::Image(Image_impl *impl) : m_impl(impl)
    {
    }

    Image::~Image() noexcept
    {
        if (m_impl)
        {
            delete m_impl;
            m_impl = nullptr;
        }
    }

    Image::Image(Image &&other) noexcept : m_impl{std::move(other.m_impl)}
    {
        other.m_impl = nullptr;
    }

    Image &Image::operator=(Image &&other) noexcept
    {
        m_impl = std::move(other.m_impl);
        other.m_impl = nullptr;

        return *this;
    }

    Size Image::size() const noexcept
    {
        assert(m_impl != nullptr);

        return m_impl->size();
    }

    void Image::resize(const Size &new_size)
    {
        assert(m_impl != nullptr);

        return m_impl->resize(new_size);
    }

    void Image::save(const std::string &img_path)
    {
        assert(m_impl != nullptr);

        return m_impl->save(img_path);
    }

    // TODO
    Image Image::apply([[maybe_unused]] Watermark &mark)
    {
        assert(m_impl != nullptr);
        assert(mark.image().m_impl != nullptr);

        // TODO
        return mark.foo(*m_impl, *mark.image().m_impl);
    }

    void Image::preview()
    {
        assert(m_impl != nullptr);

        m_impl->preview();
    }
}