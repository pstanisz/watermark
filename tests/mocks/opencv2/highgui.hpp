// Copyright (c) 2023, Piotr Staniszewski

#pragma once

#include "core/mat.hpp"

#include <string>

namespace cv
{
    void imshow([[maybe_unused]] const std::string &,
                [[maybe_unused]] Mat) {}

    int waitKey([[maybe_unused]] int delay = 0) { return 1; }

    void destroyAllWindows() {}

}