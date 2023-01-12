// Copyright (c) 2022, Piotr Staniszewski
#pragma once

#include <common.h>

#include <string>

namespace watermark
{
    class Image_impl;

    /**
     * Represents the Image of any supported type.
     */
    class Image
    {
    public:
        explicit Image(const std::string &img_path);
        ~Image() noexcept;

        Image(const Image &) noexcept = delete;
        Image &operator=(const Image &) = delete;

        Image(Image &&) = delete;
        Image &operator=(Image &&) noexcept = delete;

        Size size() const noexcept;
        void resize(const Size& new_size);

        void save(const std::string &img_path);

    private:
        Image_impl *m_impl;
    };
}
