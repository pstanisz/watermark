// Copyright (c) 2022, Piotr Staniszewski
#pragma once

#include <common.h>

#include <string>

namespace watermark
{
    class Image
    {
    public:
        explicit Image(const std::string &img_path);
        ~Image();

        Size size() const noexcept;

    private:
        class Image_impl;
        Image_impl *m_impl;
    };
}
