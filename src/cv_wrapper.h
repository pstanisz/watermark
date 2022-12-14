// Copyright (c) 2022, Piotr Staniszewski
#pragma once

#include <string>

namespace watermark
{
    struct Mat;
    
    class Cv_wrapper_if
    {
        public:
            virtual Mat imread(const std::string &filename, int flags) = 0;
    };
}
