// Copyright (c) 2023, Piotr Staniszewski
#pragma once

#include <point.h>
#include <size.h>
#include <layout.h>

namespace watermark
{

    Point position_by_layout(Layout layout, const Size &source_size, const Size &mark_size);

}
