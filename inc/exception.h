// Copyright (c) 2022, Piotr Staniszewski
#pragma once

#include <exception>
#include <string>

namespace watermark
{
    /**
     * Base exception type of watermark.
     */
    class Exception : public std::exception
    {
    public:
        explicit Exception(const std::string &msg);

        virtual const char *what() const noexcept;

    private:
        std::string m_msg;
    };

    /**
     * Represents any exception related to Image loading and processing.
     */
    class Image_exception : public Exception
    {
    public:
        explicit Image_exception(std::string &msg);
    };
}
