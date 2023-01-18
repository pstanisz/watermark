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

    Image::Image(const Size &img_size) : m_impl{new Image_impl(img_size)}
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
}