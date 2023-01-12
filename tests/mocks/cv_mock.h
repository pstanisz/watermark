// Copyright (c) 2022, Piotr Staniszewski
#pragma once

#include "opencv2/imgcodecs.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace watermark
{
    namespace mock
    {
        struct Imread
        {
            virtual cv::Mat imread(const std::string &filename, int flags) = 0;
            virtual ~Imread() noexcept = default;
        };

        struct Imread_mock : public Imread
        {
            Imread_mock() = default;
            ~Imread_mock() noexcept = default;

            MOCK_METHOD2(imread, cv::Mat(const std::string &, int));
        };

        extern Imread_mock *g_imread_mock;
    }
}