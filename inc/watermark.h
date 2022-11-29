// Copyright (c) 2022, Piotr Staniszewski

#include <cstdlib>
#include <string>

namespace watermark
{
    class Image
    {
    };

    struct Position
    {
        size_t m_x;
        size_t m_y;
    };

    struct Size
    {
        size_t m_width;
        size_t m_height;
    };

    void add_watermark(
        const std::string &input_path,
        const std::string &watermark_path,
        const std::string &output_path,
        const Position &position,
        const Size &size);

}
