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
        explicit Image_exception(const std::string &msg);
    };

    /**
     * Represents any exception related to position.
     */
    class Position_exception : public Exception
    {
    public:
        explicit Position_exception(const std::string &msg);
    };

    /**
     * Represents any exception related to size.
     */
    class Size_exception : public Exception
    {
    public:
        explicit Size_exception(const std::string &msg);
    };
}
