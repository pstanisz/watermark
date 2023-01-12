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
        Image input{"../tools/proto/data/test_img_1.png"};

        input.resize(watermark::Size(100, 100));
        input.save("test_img_1_small.png");
    }
    catch (const Exception &ex)
    {
        std::cerr << "Exception caught: " << ex.what() << std::endl;

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
