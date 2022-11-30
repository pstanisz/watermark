// Copyright (c) 2022, Piotr Staniszewski

#include <iostream>

#include <watermark.h>

int main()
{
    std::cout << "Watermark demo application\n";

    using namespace watermark;

    Image input{""};
    Image watermark{""};

    auto output = add_watermark(input, watermark, Position{0U, 0U}, Size{10U, 10U});

    return EXIT_SUCCESS;
}
