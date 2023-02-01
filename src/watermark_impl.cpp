// Copyright (c) 2023, Piotr Staniszewski

#include <image.h>

#include "watermark_impl.h"
#include "image_impl.h"

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

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

    Image_impl *Watermark_impl::apply(Image_impl *source_img,
                                      Image_impl *mark_img,
                                      const Size &mark_size,
                                      const Position &mark_pos,
                                      Opacity opacity)
    {
        auto &img_mat = source_img->internal();
        auto &mark_mat = mark_img->internal();

        cv::Mat resized_mark;

        if (mark_size != Size{0U, 0U})
        {
            cv::resize(mark_mat, resized_mark, {mark_size.m_width, mark_size.m_height}, cv::INTER_AREA);
        }
        else
        {
            resized_mark = mark_mat;
        }

        // Dummy implementation without checking any sizes
        // Assumes that mark is smaller than image
        cv::Mat mark_fit_to_img = cv::Mat::zeros(img_mat.rows, img_mat.cols, CV_8UC3);
        resized_mark.copyTo(mark_fit_to_img(cv::Rect(mark_pos.m_x, mark_pos.m_y, resized_mark.cols, resized_mark.rows)));

        std::cout << "img_mat.rows = " << img_mat.rows << std::endl;
        std::cout << "img_mat.cols = " << img_mat.cols << std::endl;
        std::cout << "resized_mark.rows = " << resized_mark.rows << std::endl;
        std::cout << "resized_mark.cols = " << resized_mark.cols << std::endl;
        std::cout << "mark_fit_to_img.rows = " << mark_fit_to_img.rows << std::endl;
        std::cout << "mark_fit_to_img.cols = " << mark_fit_to_img.cols << std::endl;

        cv::Mat out;
        addWeighted(mark_fit_to_img, opacity, img_mat, 1.0, 0.0, out); // blends 2 images

        return new Image_impl{out};
    }
}