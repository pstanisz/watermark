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
        auto result = mark.apply_to(img, Point{10, 10}, Size{100, 100}, 0.5f);

        result.preview();
        result.save("test_img_1_mark.png");
    }
    catch (const Exception &ex)
    {
        std::cerr << "Exception caught: " << ex.what() << std::endl;

        return EXIT_FAILURE;
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Std exception caught: " << ex.what() << std::endl;

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
