// Copyright (c) 2022, Piotr Staniszewski

#include <iostream>

#include <watermark.h>

int main()
{
    std::cout << "Watermark demo application\n";

    using namespace watermark;

    add_watermark("input", "watermark", "output", Position(0, 0), Size(10, 10));

    return EXIT_SUCCESS;
}
