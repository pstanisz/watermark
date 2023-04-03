// Copyright (c) 2022, Piotr Staniszewski

#include "imgproc.hpp"
#include "imgcodecs.hpp"

#include "../cv_mock.h"

namespace cv
{
    Mat imread(const std::string &filename, int flags)
    {
        return watermark::mock::g_imread_mock->imread(filename, flags);
    }

    bool imwrite([[maybe_unused]]const std::string &filename, const Mat &)
    {
        return true;
    }

    void resize([[maybe_unused]] const Mat &src,
                Mat &dst,
                Size dsize,
                [[maybe_unused]] double fx,
                [[maybe_unused]] double fy,
                [[maybe_unused]] int interpolation)
    {
        dst.rows = dsize.height;
        dst.cols = dsize.width;
    }
}