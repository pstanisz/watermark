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

        Watermark mark{std::move(logo)};

        // Resized and placed
        auto result = mark.apply_to(img, Size{300, 300}, Position{10, 10}, 0.5);

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
