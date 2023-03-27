// Copyright (c) 2022, Piotr Staniszewski

#include <iostream>

#include <watermark.h>
#include <exception.h>
#include <vector>

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
        // auto result = mark.apply_to(img, Point{10, 10}, Size{300, 300}, 0.5f);

        std::vector<Layout> layouts = { Layout::Top_left,
                                        Layout::Top_middle,
                                        Layout::Top_right,
                                        Layout::Middle_left,
                                        Layout::Center,
                                        Layout::Middle_right,
                                        Layout::Bottom_left,
                                        Layout::Bottom_middle,
                                        Layout::Bottom_right };

        for (auto layout : layouts) {
            auto result = mark.apply_to(img, layout, 0.5f);

            result.preview();
        }

        //result.save("test_img_1_mark.png");
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
