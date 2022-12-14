// Copyright (c) 2022, Piotr Staniszewski

#include <image.h>
#include <exception.h>

#include <cassert>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

namespace watermark
{
    class Image::Image_impl
    {
    public:
        explicit Image_impl(const std::string &img_path);

        inline Size size() const noexcept
        {
            return Size{10U, 10U};
        }

    private:
        cv::Mat m_matrix;
    };

    Image::Image_impl::Image_impl(const std::string &img_path) : m_matrix{cv::imread(img_path, cv::IMREAD_COLOR)}
    {
        if (m_matrix.empty())
        {
            throw Image_exception(std::string("Cannot load an image: ").append(img_path));
        }
    }

    Image::Image(const std::string &img_path) : m_impl{new Image_impl(img_path)}
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