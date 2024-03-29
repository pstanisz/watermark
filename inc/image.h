// Copyright (c) 2022, Piotr Staniszewski
#pragma once

#include <common.h>
#include <size.h>

#include <string>

namespace watermark
{
    class Image_impl;
    class Watermark;

    /**
     * Represents the Image of any supported type.
     */
    class Image
    {
    public:
        static bool is_image(const std::string &file_path);
        
    public:
        explicit Image(const std::string &img_path);
        explicit Image(const Size &img_size);
        ~Image() noexcept;

        Image(const Image &) noexcept = delete;
        Image &operator=(const Image &) = delete;

        Image(Image &&other) noexcept;
        Image &operator=(Image &&other) noexcept;

        Size size() const noexcept;
        void resize(const Size &new_size);
        void scale(double scale);

        void save(const std::string &img_path);

        // Test purposes only
        void preview();

    private:
        explicit Image(Image_impl *impl);

        friend class Watermark;
        Image_impl *m_impl;
    };
}
