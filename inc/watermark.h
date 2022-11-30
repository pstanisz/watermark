// Copyright (c) 2022, Piotr Staniszewski
#pragma once

#include <common.h>
#include <image.h>

#include <string>

namespace watermark
{
    Image add_watermark(
        const Image &input_img,
        const Image &watermark_img,
        const Position &position,
        const Size &size);

}
