// Copyright (c) 2023, Piotr Staniszewski

#include <image.h>
#include <watermark.h>
#include <exception.h>

#include <iostream>
#include <string>
#include <getopt.h>
#include <filesystem>

namespace
{

    static struct option long_options[] = {
        {"mark", required_argument, nullptr, 0},
        {"source", required_argument, nullptr, 0},
        {"source_dir", required_argument, nullptr, 0},
        {"output", required_argument, nullptr, 0},
        {"output_dir", required_argument, nullptr, 0},
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
            throw std::invalid_argument(std::string("Not existing file: ").append(file_path));
        }
        if (!std::filesystem::is_regular_file(mark_path))
        {
            throw std::invalid_argument(std::string("Non-regular file: ").append(file_path));
        }
        if (!watermark::Image::is_image(file_path))
        {
            throw std::invalid_argument(std::string("Unsupported file: ").append(file_path));
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

    validate_image_file(mark_file);
    validate_image_file(source_file);

    watermark::Image logo{mark_file};
    watermark::Image img{source_file};

    watermark::Watermark mark{std::move(logo)};
    auto result = mark.apply_to(img, watermark::Layout::Center, 0.4f);
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
