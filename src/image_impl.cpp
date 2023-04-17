// Copyright (c) 2022, Piotr Staniszewski

#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

// To be removed
#include <opencv2/highgui.hpp>

#include "image_impl.h"

#include <cassert>

namespace watermark
{
    bool Image_impl::is_image(const std::string &file_path)
    {
        auto mat = cv::imread(file_path, 0);
        
        return !mat.empty();
    }

    Image_impl::Image_impl(const std::string &img_path) : m_matrix{cv::imread(img_path, cv::IMREAD_COLOR)}
    {
        if (m_matrix.empty())
        {
            throw Image_exception(std::string("Cannot load an image: ").append(img_path));
        }
    }

    Image_impl::Image_impl(const Size &img_size) : m_matrix{cv::Mat::zeros(img_size.height(), img_size.width(), CV_8UC3)}
    {
    }

    Image_impl::Image_impl(const cv::Mat &mat) : m_matrix{mat}
    {
    }

    Size Image_impl::size() const noexcept
    {
        assert(!m_matrix.empty());

        return Size{m_matrix.size().width, m_matrix.size().height};
    }

    void Image_impl::resize(const Size &new_size)
    {
        assert(!m_matrix.empty());

        cv::resize(m_matrix, m_matrix, {new_size.width(), new_size.height()}, 0.0, 0.0, cv::INTER_AREA);
    }

    void Image_impl::save(const std::string &img_path)
    {
        assert(!m_matrix.empty());

        cv::imwrite(img_path, m_matrix);
    }

    cv::Mat &Image_impl::internal()
    {
        assert(!m_matrix.empty());

        return m_matrix;
    }

    void Image_impl::preview()
    {
        assert(!m_matrix.empty());

        cv::imshow("Display window", m_matrix);
        cv::waitKey(0);

        cv::destroyAllWindows();
    }
}