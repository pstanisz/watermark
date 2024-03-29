// Copyright (c) 2023, Piotr Staniszewski

#include <image.h>

#include "watermark_impl.h"
#include "image_impl.h"
#include "utils.h"

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
                                      const Point &mark_pos,
                                      const Size &mark_size,
                                      Opacity opacity)
    {
        auto &img_mat = source_img->internal();
        auto &mark_mat = mark_img->internal();

        cv::Mat resized_mark;

        if (mark_size.is_empty())
        {
            throw Size_exception("Cannot use empty mark size");
        }

        auto available_size = source_img->size() - mark_pos;
        if (!mark_size.fits_in(available_size))
        {
            throw Size_exception("Requested mark size won't fit into source image");
        }

        if (mark_size == mark_img->size())
        {
            resized_mark = mark_mat;
        }
        else
        {
            cv::resize(mark_mat, resized_mark, {mark_size.width(), mark_size.height()}, cv::INTER_AREA);
        }

        cv::Mat mark_fit_to_img = cv::Mat::zeros(img_mat.rows, img_mat.cols, CV_8UC3);
        const auto rect = cv::Rect(mark_pos.m_x, mark_pos.m_y, resized_mark.cols, resized_mark.rows);
        resized_mark.copyTo(mark_fit_to_img(rect));

        cv::Mat out;
        addWeighted(mark_fit_to_img, opacity, img_mat, 1.0, 0.0, out); // blends 2 images

        return new Image_impl{out};
    }

    Image_impl *Watermark_impl::apply(Image_impl *source_img,
                                      Image_impl *mark_img,
                                      Layout layout,
                                      const Size &mark_size,
                                      Opacity opacity)
    {
        if (mark_size.is_empty())
        {
            throw Size_exception("Cannot use empty mark size");
        }

        auto mark_pos = position_by_layout(layout, source_img->size(), mark_size);
        return apply(source_img, mark_img, mark_pos, mark_size, opacity);
    }
}