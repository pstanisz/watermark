// Copyright (c) 2022, Piotr Staniszewski

#include "cv_wrapper_impl.h"

namespace watermark
{

    Mat Cv_wrapper_impl::imread(const std::string &filename, int flags)
    {
        return cv::imread(img_path, cv::IMREAD_COLOR);
    }

}
