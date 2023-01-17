// Copyright (c) 2023, Piotr Staniszewski
#pragma once

#include "types.hpp"
#include "hal/interface.h"

namespace cv
{
    struct Mat
    {
        bool empty() const noexcept { return m_empty; }
        Size size() const { return m_size; }
        static Mat zeros(int rows, int cols, [[maybe_unused]]int type) { return Mat{false, Size{rows, cols}}; }

        bool m_empty;
        Size m_size;
    };
}
