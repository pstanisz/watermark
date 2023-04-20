// Copyright (c) 2023, Piotr Staniszewski

#include <image.h>
#include <watermark.h>
#include <exception.h>

#include <iostream>
#include <string>
#include <getopt.h>
#include <filesystem>
#include <vector>
#include <regex>

namespace
{
    // Arguments
    const char MARK_ARG[] = "mark";
    const char MARK_SIZE_ARG[] = "mark_size";
    const char SRC_ARG[] = "src";
    const char SRC_DIR_ARG[] = "src_dir";
    const char OUT_ARG[] = "out";
    const char OUT_DIR_ARG[] = "out_dir";
    const char LAYOUT_ARG[] = "layout";
    const char OPACITY_ARG[] = "opacity";
    const char HELP_ARG[] = "help";

    const std::string TOP_LEFT = "top-left";
    const std::string TOP_MID = "top-mid";
    const std::string TOP_RIGHT = "top-right";
    const std::string MID_LEFT = "middle-left";
    const std::string CENTER = "center";
    const std::string MID_RIGHT = "middle-right";
    const std::string BOTTOM_LEFT = "bottom-left";
    const std::string BOTTOM_MID = "bottom-mid";
    const std::string BOTTOM_RIGHT = "bottom-right";

    static const char *short_options = "h";
    static struct option long_options[] = {
        {MARK_ARG, required_argument, nullptr, 0},
        {MARK_SIZE_ARG, required_argument, nullptr, 0},
        {SRC_ARG, required_argument, nullptr, 0},
        {SRC_DIR_ARG, required_argument, nullptr, 0},
        {OUT_ARG, required_argument, nullptr, 0},
        {OUT_DIR_ARG, required_argument, nullptr, 0},
        {LAYOUT_ARG, required_argument, nullptr, 0},
        {OPACITY_ARG, required_argument, nullptr, 0},
        {HELP_ARG, no_argument, nullptr, 0},
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

    std::string create_out_file(const std::string &src, const std::string& output_dir = "")
    {
        namespace fs = std::filesystem;

        fs::path src_path{src};
        auto filename = src_path.filename().replace_extension("");
        auto extension = src_path.extension();

        fs::path out_path{};
        if (output_dir.empty()) {
            out_path = src_path.remove_filename();
        }
        else {
            out_path = fs::path(output_dir);
        }

        out_path += filename;
        out_path += "_marked";
        out_path += extension;

        return out_path;
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
    watermark::Size mark_size{};
    watermark::Layout layout{watermark::Layout::Center};
    watermark::Opacity opacity{0.5f};

    while ((option_id = getopt_long(argc, argv, short_options,
                                    long_options, &option_index)) != -1)
    {
        if (option_id == '?')
        {
            throw std::invalid_argument(std::string("Unrecognized option: ") + argv[optind - 1]);
        }

        const std::string option_name{long_options[option_index].name};

        if (option_name == HELP_ARG || option_name == "h")
        {
            std::cout << "watermark_cli help\n";
            return EXIT_SUCCESS;
        }

        if (option_name == MARK_ARG)
        {
            mark_file = optarg;
            validate_image_file(mark_file);
        }

        if (option_name == MARK_SIZE_ARG)
        {
            std::smatch matches;
            const std::regex size_expr("^([0-9]+),([0-9]+)");
            std::string in(optarg);
            if (std::regex_search(in, matches, size_expr))
            {
                mark_size = watermark::Size{std::stoul(matches[1]), std::stoul(matches[2])};
            }
            else
            {
                throw std::invalid_argument(std::string("Cannot recognize mark size: ").append(in));
            }
        }

        if (option_name == SRC_ARG)
        {
            source_file = optarg;
            validate_image_file(source_file);
        }

        if (option_name == OUT_ARG)
        {
            output_file = optarg;
        }

        if (option_name == SRC_DIR_ARG)
        {
            source_dir = optarg;
        }

        if (option_name == OUT_DIR_ARG)
        {
            output_dir = optarg;
        }

        if (option_name == LAYOUT_ARG)
        {
            layout = to_layout(optarg);
        }

        if (option_name == OPACITY_ARG)
        {
            opacity = std::stof(optarg);
        }
    }

    if (mark_file.empty())
    {
        throw std::invalid_argument("Mark file is required");
    }

    if (source_file.empty() && source_dir.empty())
    {
        throw std::invalid_argument(std::string(SRC_ARG).append(" or ").append(SRC_DIR_ARG).append(" is required"));
    }

    if (!source_file.empty() && !source_dir.empty())
    {
        throw std::invalid_argument(std::string("Cannot use both: ").append(SRC_ARG).append(" and ").append(SRC_DIR_ARG));
    }

    if (!output_file.empty() && !output_dir.empty())
    {
        throw std::invalid_argument(std::string("Cannot use both: ").append(OUT_ARG).append(" and ").append(OUT_DIR_ARG));
    }

    if (!source_dir.empty())
    {
        // TODO:
        find_images_in_dir(source_dir);
    }

    watermark::Image logo{mark_file};
    watermark::Image img{source_file};

    // If the size of mark is not set explicitly - use original mark size
    if (mark_size.is_empty())
    {
        mark_size = logo.size();
    }

    if (output_file.empty())
    {
        output_file = create_out_file(source_file, output_dir);
    }

    std::cout << "Mark file: " << mark_file << std::endl;
    std::cout << "Source file: " << source_file << std::endl;
    std::cout << "Output file: " << output_file << std::endl;
    std::cout << "Source dir: " << source_dir << std::endl;
    std::cout << "Output dir: " << output_dir << std::endl;
    std::cout << "Layout: " << static_cast<int>(layout) << std::endl;
    std::cout << "Opacity: " << opacity << std::endl;
    std::cout << "Size: " << mark_size.width() << "x" << mark_size.height() << std::endl;

    watermark::Watermark mark{std::move(logo)};
    auto result = mark.apply_to(img, layout, mark_size, opacity);
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
