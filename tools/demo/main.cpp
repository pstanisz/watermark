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
        Image img{"../tools/proto/data/test_img_1.png"};
        Image logo{"../tools/proto/data/test_logo_1.png"};

        // Check of resize & save
        // img.resize(watermark::Size(100, 100));
        // img.save("test_img_1_small.png");

        Watermark mark{std::move(logo)};
        auto result = img.apply(mark);

        result.preview();
        result.save("test_img_1_mark.png");
    }
    catch (const Exception &ex)
    {
        std::cerr << "Exception caught: " << ex.what() << std::endl;

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
