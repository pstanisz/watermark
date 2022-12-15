// Copyright (c) 2022, Piotr Staniszewski

#include "core.hpp"

namespace cv
{

    bool Mat::empty() const noexcept { return true; }

    Mat imread([[maybe_unused]] const std::string &filename, [[maybe_unused]] int flags)
    {
        return Mat();
    }
}