// Copyright (c) 2022, Piotr Staniszewski

#include <opencv2/imgcodecs.hpp>

#include "image_impl.h"

#include <cassert>

namespace watermark
{

    Image_impl::Image_impl(const std::string &img_path) : m_matrix{cv::imread(img_path, cv::IMREAD_COLOR)}
    {
        if (m_matrix.empty())
        {
            throw Image_exception(std::string("Cannot load an image: ").append(img_path));
        }
    }

    Size Image_impl::size() const noexcept
    {
        assert(!m_matrix.empty());

        return Size{m_matrix.size().width, m_matrix.size().height};
    }
}