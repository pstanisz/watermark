// Copyright (c) 2022, Piotr Staniszewski

#include <iostream>

#include <watermark.h>
#include <exception.h>

int main()
{
    std::cout << "Watermark demo application\n";

    using namespace watermark;

    try
    {
        Image input{""};
        Image watermark{""};

        auto output = add_watermark(input, watermark, Position{0U, 0U}, Size{10U, 10U});
    }
    catch (const Exception &ex)
    {
        std::cerr << "Exception caught: " << ex.what() << std::endl;

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
