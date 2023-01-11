// Copyright (c) 2022, Piotr Staniszewski

#include "core.hpp"
#include "imgproc.hpp"

#include "../cv_mock.h"

namespace cv
{
    Mat imread(const std::string &filename, int flags)
    {
        return watermark::mock::g_imread_mock->imread(filename, flags);
    }

    void resize(const Mat &src,
                Mat &dst,
                Size dsize,
                double fx,
                double fy,
                int interpolation)
    {
        dst.m_size = dsize;
    }
}