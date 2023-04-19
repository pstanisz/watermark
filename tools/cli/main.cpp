// Copyright (c) 2023, Piotr Staniszewski

#include <image.h>
#include <watermark.h>
#include <exception.h>

#include <iostream>
#include <string>
#include <getopt.h>
#include <filesystem>
#include <vector>

namespace
{
    const std::string TOP_LEFT = "top-left";
    const std::string TOP_MID = "top-mid";
    const std::string TOP_RIGHT = "top-right";
    const std::string MID_LEFT = "middle-left";
    const std::string CENTER = "center";
    const std::string MID_RIGHT = "middle-right";
    const std::string BOTTOM_LEFT = "bottom-left";
    const std::string BOTTOM_MID = "bottom-mid";
    const std::string BOTTOM_RIGHT = "bottom-right";

    static struct option long_options[] = {
        {"mark", required_argument, nullptr, 0},
        {"source", required_argument, nullptr, 0},
        {"source_dir", required_argument, nullptr, 0},
        {"output", required_argument, nullptr, 0},
        {"output_dir", required_argument, nullptr, 0},
        {"layout", required_argument, nullptr, 0},
        {"opacity", required_argument, nullptr, 0},
        {"help", no_argument, nullptr, 0},
        {0, 0, 0, 0}};

    void validate_image_file(const std::string &file_path)
    {
        if (file_path.empty())
        {
            throw std::invalid_argument(std::string("Empty file path"));
        }

        std::filesystem::path mark_path{file_path};
        if (!std::filesystem::exists(mark_path))
        {
            throw std::invalid_argument(std::string("File does not exist: ").append(file_path));
        }
        if (!std::filesystem::is_regular_file(mark_path))
        {
            throw std::invalid_argument(std::string("File is not regular ").append(file_path));
        }
        if (!watermark::Image::is_image(file_path))
        {
            throw std::invalid_argument(std::string("File is not an image: ").append(file_path));
        }
    }

    std::vector<std::string> find_images_in_dir(const std::string &dir)
    {
        std::vector<std::string> images;

        std::filesystem::path dir_path{dir};
        if (!std::filesystem::exists(dir_path))
        {
            throw std::invalid_argument(std::string("Directory does not exist: ").append(dir_path));
        }
        if (!std::filesystem::is_directory(dir_path))
        {
            throw std::invalid_argument(std::string("Not a directory: ").append(dir_path));
        }

        for (const auto &entry : std::filesystem::directory_iterator(dir_path))
        {
            std::cout << entry << std::endl;
        }

        return images;
    }

    watermark::Layout to_layout(const std::string &arg)
    {
        using watermark::Layout;

        if (arg == TOP_LEFT)
        {
            return Layout::Top_left;
        }
        else if (arg == TOP_MID)
        {
            return Layout::Top_middle;
        }
        else if (arg == TOP_RIGHT)
        {
            return Layout::Top_right;
        }
        else if (arg == MID_LEFT)
        {
            return Layout::Middle_left;
        }
        else if (arg == CENTER)
        {
            return Layout::Center;
        }
        else if (arg == MID_RIGHT)
        {
            return Layout::Middle_right;
        }
        else if (arg == BOTTOM_LEFT)
        {
            return Layout::Bottom_left;
        }
        else if (arg == BOTTOM_MID)
        {
            return Layout::Bottom_middle;
        }
        else if (arg == BOTTOM_RIGHT)
        {
            return Layout::Bottom_right;
        }
        else
        {
            throw std::invalid_argument(std::string("Unrecognized layout: ").append(arg));
        }
    }

}

int main(int argc, char *argv[])
try
{
    std::cout << "watermark_cli\n";

    int option_index = 0;
    int option_id = 0;
    opterr = 0;

    std::string mark_file{};
    std::string source_file{};
    std::string output_file{};
    std::string source_dir{};
    std::string output_dir{};
    watermark::Layout layout{watermark::Layout::Center};
    watermark::Opacity opacity{0.5f};

    while ((option_id = getopt_long(argc, argv, "",
                                    long_options, &option_index)) != -1)
    {
        if (option_id == '?')
        {
            throw std::invalid_argument(std::string("Unrecognized option: ") + argv[optind - 1]);
        }

        const std::string option_name{long_options[option_index].name};

        if (option_name == "help")
        {
            std::cout << "watermark_cli\n";
            return EXIT_SUCCESS;
        }

        if (option_name == "mark")
        {
            mark_file = optarg;
        }

        if (option_name == "source")
        {
            source_file = optarg;
        }

        if (option_name == "output")
        {
            output_file = optarg;
        }

        if (option_name == "source_dir")
        {
            source_dir = optarg;
        }

        if (option_name == "output_dir")
        {
            output_dir = optarg;
        }

        if (option_name == "layout")
        {
            layout = to_layout(optarg);
        }

        if (option_name == "opacity")
        {
            opacity = std::stof(optarg);
        }
    }

    std::cout << "Mark file: " << mark_file << std::endl;
    std::cout << "Source file: " << source_file << std::endl;
    std::cout << "Output file: " << output_file << std::endl;
    std::cout << "Source dir: " << source_dir << std::endl;
    std::cout << "Output dir: " << output_dir << std::endl;

    if (mark_file.empty())
    {
        throw std::invalid_argument("Mark file is required");
    }

    if (source_file.empty() && source_dir.empty())
    {
        throw std::invalid_argument("Source file or directory is required");
    }

    if (output_file.empty() && output_dir.empty())
    {
        throw std::invalid_argument("Output file or directory is required");
    }

    if (!source_dir.empty())
    {
        // TODO:
        find_images_in_dir(source_dir);
    }

    validate_image_file(mark_file);
    validate_image_file(source_file);

    watermark::Image logo{mark_file};
    watermark::Image img{source_file};

    watermark::Watermark mark{std::move(logo)};
    auto result = mark.apply_to(img, layout, opacity);
    result.save(output_file);

    return EXIT_SUCCESS;
}
catch (const watermark::Exception &e)
{
    std::cerr << "Watermarking failed: " << e.what() << std::endl;
    return EXIT_FAILURE;
}
catch (const std::exception &e)
{
    std::cerr << "Execution failed: " << e.what() << std::endl;
    return EXIT_FAILURE;
}
