// Copyright (c) 2023, Piotr Staniszewski

#include <image.h>

#include "watermark_impl.h"
#include "image_impl.h"

#include <opencv2/core.hpp>

#include <cassert>
#include <iostream>

namespace watermark
{

    Watermark_impl::Watermark_impl(Image &&watermark_img) : m_image{std::move(watermark_img)}
    {
    }

    Image &Watermark_impl::image()
    {
        return m_image;
    }

    Image_impl* Watermark_impl::foo(Image_impl &img, Image_impl &mark)
    {
        auto &img_mat = img.internal();
        auto &mark_mat = mark.internal();

        // Dummy implementation without checking any sizes
        // Assumes that mark is smaller than image
        cv::Mat mark_resized = cv::Mat::zeros(img_mat.rows, img_mat.cols, CV_8UC3);
        mark_mat.copyTo(mark_resized(cv::Rect(mark_resized.cols - mark_mat.cols, mark_resized.rows - mark_mat.rows, mark_mat.cols, mark_mat.rows)));

        std::cout << "img_mat.rows = " << img_mat.rows << std::endl;
        std::cout << "img_mat.cols = " << img_mat.cols << std::endl;
        std::cout << "mark_mat.rows = " << mark_mat.rows << std::endl;
        std::cout << "mark_mat.cols = " << mark_mat.cols << std::endl;
        std::cout << "mark_resized.rows = " << mark_resized.rows << std::endl;
        std::cout << "mark_resized.cols = " << mark_resized.cols << std::endl;

        cv::Mat out;
        addWeighted(mark_resized, 0.9, img_mat, 1.0, 0.0, out); // blends 2 images

        return new Image_impl{out};
    }
}