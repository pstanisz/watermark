// Copyright (c) 2023, Piotr Staniszewski
#pragma once

namespace cv
{
    enum ImreadModes
    {
        IMREAD_COLOR = 1,
    };

    struct Size
    {
        int width;
        int height;
    };

    struct Rect
    {
        int x;
        int y;
        int width;
        int height;
    };
}
