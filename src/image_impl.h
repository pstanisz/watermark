// Copyright (c) 2022, Piotr Staniszewski
#pragma once

#include <common.h>
#include <exception.h>

#include <opencv2/core.hpp>

#include <string>

namespace watermark
{
    class Image_impl
    {
    public:
        explicit Image_impl(const std::string &img_path);
        ~Image_impl() noexcept = default;

        Size size() const noexcept;

    private:
        cv::Mat m_matrix;
    };
}
