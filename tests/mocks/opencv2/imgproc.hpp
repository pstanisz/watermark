// Copyright (c) 2022, Piotr Staniszewski

#pragma once

#include "core.hpp"

namespace cv
{
    enum InterpolationFlags
    {
        INTER_LINEAR = 1,
        INTER_AREA = 3
    };

    void resize(const Mat& src,
                Mat& dst,
                Size dsize,
                double fx = 0,
                double fy = 0,
                int interpolation = INTER_LINEAR);
}
