// Copyright (c) 2022, Piotr Staniszewski
#pragma once

#include <common.h>
#include <exception.h>

#include <opencv2/core/mat.hpp>

#include <string>

namespace watermark
{
    class Image_impl
    {
    public:
        explicit Image_impl(const std::string &img_path);
        explicit Image_impl(const Size &img_size);
        ~Image_impl() noexcept = default;

        Size size() const noexcept;
        void resize(const Size &new_size);

        void save(const std::string &img_path);

    private:
        cv::Mat m_matrix;
    };
}
