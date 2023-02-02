// Copyright (c) 2022, Piotr Staniszewski

#include <exception.h>
#include <string>

namespace watermark
{

    Exception::Exception(const std::string &msg) : m_msg{msg}
    {
    }

    const char *Exception::what() const noexcept
    {
        return m_msg.c_str();
    }

    Image_exception::Image_exception(const std::string &msg) : Exception(msg)
    {
    }

    Position_exception::Position_exception(const std::string &msg) : Exception(msg)
    {
    }
}
