// Copyright (c) 2023, Piotr Staniszewski

#include <watermark.h>
#include <exception.h>

#include <iostream>
#include <string>
#include <getopt.h>

static struct option long_options[] = {
    {"mark", required_argument, nullptr, 0},
    {"source", required_argument, nullptr, 0},
    {"output", required_argument, nullptr, 0},
    {"help", no_argument, nullptr, 0},
    {0, 0, 0, 0}};

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
    }

    std::cout << "Mark file: " << mark_file << std::endl;
    std::cout << "Source file: " << source_file << std::endl;
    std::cout << "Output file: " << output_file << std::endl;

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
