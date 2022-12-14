// Copyright (c) 2022, Piotr Staniszewski

#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

int main()
{
    using namespace cv;

    std::cout << "prototype\n";

    const std::string image_path = "../tools/proto/data/test_img_1.png";
    Mat img = imread(image_path, IMREAD_COLOR);

    if (img.empty())
    {
        std::cout << "Cannot read the image: " << image_path << "\n";
        return EXIT_FAILURE;
    }

    auto img_size = img.size();
    std::cout << "Loaded image size: " << img_size.width << " x " << img_size.height << "\n";

    const std::string logo_path = "../tools/proto/data/test_logo_1.png";
    Mat logo = imread(logo_path, IMREAD_COLOR);

    if (logo.empty())
    {
        std::cout << "Cannot read the logo: " << logo_path << "\n";
        return EXIT_FAILURE;
    }

    auto logo_size = logo.size();
    if (img_size != logo_size) {
        std::cout << "Sizes are different!\n";
    }

    auto new_height = static_cast<int>(img.rows * 0.2);
    //auto new_width = static_cast<int>(new_height * (static_cast<double>(img.cols)/static_cast<double>(img.rows)));
    auto new_width = static_cast<int>(logo.cols * (static_cast<double>(new_height)/static_cast<double>(logo.cols)));
    resize(logo, logo, {new_width, new_height}, INTER_AREA);        // best for shrink
    //resize(logo, logo, {new_width, new_height}, INTER_CUBIC);
    //resize(logo, logo, {new_width, new_height}, INTER_LINEAR);
    //resize(logo, logo, {new_width, new_height}, INTER_NEAREST);   // better for zooming

    Mat watermark = Mat::zeros(img.rows, img.cols, CV_8UC3);    // 8-bit unsigned integer matris with 3 channels
    logo.copyTo(watermark(Rect(watermark.cols - logo.cols, watermark.rows - logo.rows, logo.cols, logo.rows)));

    Mat out;
    addWeighted(watermark, 0.9, img, 1.0, 0.0, out);    // blends 2 images

    imshow("Display window", out);
    waitKey(0);

    destroyAllWindows();
    imwrite("test_watermarked_1.png", out);

    return EXIT_SUCCESS;
}
