// Copyright (c) 2022, Piotr Staniszewski

#include <image.h>

#include <cassert>

namespace watermark
{
    class Image::Image_impl
    {
    public:
        Image_impl() = default;

        Size size() const noexcept
        {
            return Size{10U, 10U};
        }
    };

    Image::Image(const std::string & /*img_path*/) : m_impl{new Image_impl()}
    {
    }

    Image::~Image()
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
}