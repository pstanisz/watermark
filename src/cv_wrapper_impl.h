// Copyright (c) 2022, Piotr Staniszewski
#pragma once

#include "cv_wrapper.h"

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

namespace watermark
{
    class Cv_wrapper_impl : public Cv_wrapper_if
    {
    public:
        Mat imread(const std::string &filename, int flags) override;
    };
}
