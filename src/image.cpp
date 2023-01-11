// Copyright (c) 2022, Piotr Staniszewski

#include <image.h>
#include <exception.h>

#include <cassert>

#include "image_impl.h"

namespace watermark
{

    Image::Image(const std::string &img_path) : m_impl{new Image_impl(img_path)}
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

    Size Image::size() const noexcept
    {
        assert(m_impl != nullptr);

        return m_impl->size();
    }

    void Image::resize(const Size& new_size)
    {
        assert(m_impl != nullptr);

        return m_impl->resize(new_size);
    }
}