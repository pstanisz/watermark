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

        auto source_size = source_img->size();
        auto middle_height = static_cast<int>(source_size.height() / 2);
        auto middle_width = static_cast<int>(source_size.width() / 2);
        auto half_mark_height = static_cast<int>(mark_size.height() / 2);
        auto half_mark_width = static_cast<int>(mark_size.width() / 2);

        std::cout << "source_size = (" << source_size.width() << ", " << source_size.height() << ")\n";
        std::cout << "mark_size = (" << mark_size.width() << ", " << mark_size.height() << ")\n";
        std::cout << "middle_height = " << middle_height << "\n";
        std::cout << "middle_width = " << middle_width << "\n";
        std::cout << "half_mark_height = " << half_mark_height << "\n";
        std::cout << "half_mark_width = " << half_mark_width << "\n";
        std::cout << "layout = " << static_cast<int>(layout) << "\n";

        Point mark_pos{0, 0};
        switch (layout)
        {
        case Layout::Top_left:
        {
            mark_pos = Point{0, 0};
            break;
        }
        case Layout::Top_middle:
        {
            mark_pos = Point{middle_width - half_mark_width, 0};
            break;
        }
        case Layout::Top_right:
        {
            mark_pos = Point{source_size.width() - mark_size.width(), 0};
            break;
        }
        case Layout::Middle_left:
        {
            mark_pos = Point{0, middle_height - half_mark_height};
            break;
        }
        case Layout::Center:
        {
            mark_pos = Point{middle_width - half_mark_width, middle_height - half_mark_height};
            break;
        }
        case Layout::Middle_right:
        {
            mark_pos = Point{source_size.width() - mark_size.width(), middle_height - half_mark_height};
            break;
        }
        case Layout::Bottom_left:
        {
            mark_pos = Point{0, source_size.height() - mark_size.height()};
            break;
        }
        case Layout::Bottom_middle:
        {
            mark_pos = Point{middle_width - half_mark_width, source_size.height() - mark_size.height()};
            break;
        }
        case Layout::Bottom_right:
        {
            mark_pos = {source_size.width() - mark_size.width(), source_size.height() - mark_size.height()};
            break;
        }
        default:
            break;
        }

        std::cout << "mark_pos = (" << mark_pos.m_x << ", " << mark_pos.m_y << ")\n";

        return apply(source_img, mark_img, mark_pos, mark_size, opacity);
    }
}