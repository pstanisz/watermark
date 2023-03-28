// Copyright (c) 2023, Piotr Staniszewski

#pragma once

#include "core/mat.hpp"

namespace cv
{

    void addWeighted([[maybe_unused]] Mat src1,
                     [[maybe_unused]] double alpha,
                     [[maybe_unused]] Mat src2,
                     [[maybe_unused]] double beta,
                     [[maybe_unused]] double gamma,
                     [[maybe_unused]] Mat dst,
                     [[maybe_unused]] int dtype = -1) {}

}
