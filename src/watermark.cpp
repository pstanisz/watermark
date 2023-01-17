// Copyright (c) 2022, Piotr Staniszewski

#include <watermark.h>

#include <iostream>

#include <opencv2/core/mat.hpp>

namespace watermark
{

    Image add_watermark(
        [[maybe_unused]] const Image &input_img,
        [[maybe_unused]] const Image &watermark_img,
        [[maybe_unused]] const Position &position,
        [[maybe_unused]] const Size &size)
    {
        [[maybe_unused]]cv::Mat watermark = cv::Mat::zeros(input_img.size().m_height, input_img.size().m_width, CV_8UC3);

        //TODO

        return Image("");
    }

}
