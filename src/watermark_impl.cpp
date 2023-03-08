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
    Size calculate_mark_size(const Size &source_size, const Size &mark_size, const Size &requested_size)
    {
        if (requested_size.has_fit())
        {
            auto fit = requested_size.fit();
            if (fit == Size::Fit::None)
            {
                return mark_size;
            }
            else
            {
                // TODO: calculate new size
                return mark_size;
            }
        }
        else
        {
            auto area = requested_size.area();
            if (area.is_empty())
            {
                // TODO: original size or exception?
                return mark_size;
            }
            else
            {
                return requested_size;
            }
        }
    }

    Watermark_impl::Watermark_impl(Image &&watermark_img) : m_image{std::move(watermark_img)}
    {
    }

    Image &Watermark_impl::image()
    {
        return m_image;
    }

    Image_impl *Watermark_impl::apply(Image_impl *source_img,
                                      Image_impl *mark_img,
                                      const Position &mark_pos,
                                      const Size &mark_size,
                                      Opacity opacity)
    {
        auto &img_mat = source_img->internal();
        auto &mark_mat = mark_img->internal();

        cv::Mat resized_mark;

        auto calculated_size = calculate_mark_size(source_img->size(), mark_img->size(), mark_size);
        cv::resize(mark_mat, resized_mark, {calculated_size.width(), calculated_size.height()}, cv::INTER_AREA);

        // Dummy implementation without checking any sizes
        // Assumes that mark is smaller than image
        cv::Mat mark_fit_to_img = cv::Mat::zeros(img_mat.rows, img_mat.cols, CV_8UC3);

        if (mark_pos.has_point())
        {
            auto point = mark_pos.point();
            resized_mark.copyTo(mark_fit_to_img(cv::Rect(point.m_x, point.m_y, resized_mark.cols, resized_mark.rows)));
        }
        else if (mark_pos.has_layout())
        {
            // auto layout = mark_pos.layout();
            //  TODO: implement calculation of Point based on layout and input image size
            throw std::runtime_error("Not implemented yet");
        }
        else
        {
            throw Position_exception(std::string("Position cannot be determined"));
        }

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