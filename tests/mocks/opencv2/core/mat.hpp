// Copyright (c) 2023, Piotr Staniszewski
#pragma once

#include "types.hpp"
#include "hal/interface.h"

namespace cv
{
    struct Mat
    {
        Mat() : m_empty{true} {}
        Mat(bool empty, int r, int c) : m_empty{empty}, rows{r}, cols{c} {}
        bool empty() const noexcept { return m_empty; }
        Size size() const { return Size{rows, cols}; }
        static Mat zeros(int rows, int cols, [[maybe_unused]] int type) { return Mat{false, rows, cols}; }
        void copyTo([[maybe_unused]] Mat m) const {}
        Mat operator()([[maybe_unused]] const Rect &roi) const { return Mat(); }

        bool m_empty;

        int rows;
        int cols;
    };
}
