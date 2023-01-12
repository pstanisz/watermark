// Copyright (c) 2022, Piotr Staniszewski

#pragma once

#include "core.hpp"

#include <string>

namespace cv
{
    Mat imread(const std::string &filename, int flags);

    bool imwrite(const std::string &filename, const Mat &mat);
}