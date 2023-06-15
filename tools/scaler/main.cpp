// Copyright (c) 2023, Piotr Staniszewski

#include <image.h>
#include <watermark.h>
#include <exception.h>

#include <logger.h>

#include <iostream>
#include <string>
#include <getopt.h>
#include <filesystem>
#include <vector>
#include <regex>
#include <sstream>

namespace
{
    // Version
    const uint8_t MAJOR_VERSION{1U};
    const uint8_t MINOR_VERSION{0U};

    std::string app_version()
    {
        std::stringstream ss;
        ss << static_cast<int>(MAJOR_VERSION) << "." << static_cast<int>(MINOR_VERSION);
        return ss.str();
    }

    // App name
    const char APP_NAME[] = "scaler";

    // Arguments
    const char SIZE_ARG[] = "size";
    const char SRC_ARG[] = "src";
    const char SRC_DIR_ARG[] = "src_dir";
    const char OUT_ARG[] = "out";
    const char OUT_DIR_ARG[] = "out_dir";
    const char HELP_ARG[] = "help";

    // Options
    static const char *short_options = "h";
    static struct option long_options[] = {
        {SIZE_ARG, required_argument, nullptr, 0},
        {SRC_ARG, required_argument, nullptr, 0},
        {SRC_DIR_ARG, required_argument, nullptr, 0},
        {OUT_ARG, required_argument, nullptr, 0},
        {OUT_DIR_ARG, required_argument, nullptr, 0},
        {HELP_ARG, no_argument, nullptr, 0},
        {0, 0, 0, 0}};

    // Consts
    const double NO_SCALE = 1.0;

    void print_help()
    {
        std::cout << APP_NAME << ", " << app_version() << "\n";
        std::cout << "\nApplication takes an input image or images and scales it so that it fits to the size specified.\n";

        std::cout << "\nUsage:\n";
        std::cout << "\t" << APP_NAME << " --" << SIZE_ARG << " <size> --" << SRC_ARG << " <image> --"
                  << OUT_ARG << " <output_image>\n";

        std::cout << "\nArguments:\n";
        std::cout << "\t" << SIZE_ARG << "\tsize to fit to (mandatory)\n";
        std::cout << "\t" << SRC_ARG << "\tsource image to be scaled (mandatory if " << SRC_DIR_ARG << " is not specified)\n";
        std::cout << "\t" << SRC_DIR_ARG << "\tdirectory with images to be scaled (mandatory if " << SRC_ARG << " is not specified)\n";
        std::cout << "\t" << OUT_ARG << "\toutput file, where scaled image will be saved (default: same as source with _scaled postfix)\n";
        std::cout << "\t" << OUT_DIR_ARG << "\toutput directory, where scaled images will be saved\n";
        std::cout << "\t" << HELP_ARG << "\tshows help\n";

        std::cout << "\nSamples:\n";
        std::cout << "\t" << APP_NAME << " --" << SIZE_ARG << "  100,100 --" << SRC_ARG << " /home/guest/mountains.png --"
                  << OUT_ARG << " /home/guest/mountains_marked.png\n";
    }

    std::filesystem::path get_fs_path(const std::string &file_path)
    {
        if (file_path.empty())
        {
            throw std::invalid_argument(std::string("Empty file path"));
        }

        std::filesystem::path fs_path{file_path};
        if (!std::filesystem::exists(fs_path))
        {
            throw std::invalid_argument(std::string("File/directory does not exist: ").append(file_path));
        }

        return fs_path;
    }

    std::filesystem::path get_dir_path(const std::string &dir_path)
    {
        auto fs_path = get_fs_path(dir_path);
        if (!std::filesystem::is_directory(fs_path))
        {
            throw std::invalid_argument(std::string("Not a directory: ").append(dir_path));
        }

        return fs_path;
    }

    void validate_dir(const std::string &dir_path)
    {
        get_dir_path(dir_path);
    }

    void validate_image_file(const std::string &file_path)
    {
        auto fs_path = get_fs_path(file_path);
        if (!std::filesystem::is_regular_file(fs_path))
        {
            throw std::invalid_argument(std::string("File is not regular ").append(file_path));
        }
        if (!watermark::Image::is_image(fs_path))
        {
            throw std::invalid_argument(std::string("File is not an image: ").append(file_path));
        }
    }

    std::string create_out_file(const std::string &src, const std::string &output_dir = "")
    {
        namespace fs = std::filesystem;

        fs::path src_path{src};
        auto filename = src_path.filename().replace_extension("");
        auto extension = src_path.extension();

        fs::path out_path{};
        if (output_dir.empty())
        {
            out_path = src_path.remove_filename();
        }
        else
        {
            out_path = fs::path(output_dir);
        }

        out_path += filename;
        out_path += "_scaled";
        out_path += extension;

        return out_path;
    }

    std::vector<std::string> find_images_in_dir(const std::string &dir)
    {
        std::vector<std::string> images;

        auto dir_path = get_dir_path(dir);

        for (const auto &entry : std::filesystem::directory_iterator(dir_path))
        {
            const auto &path = entry.path();
            if (watermark::Image::is_image(path))
            {
                images.push_back(path);
            }
        }

        return images;
    }

    double calculate_scaling_factor(const watermark::Size &input, const watermark::Size &max)
    {
        double width_scale = 1.0;
        double height_scale = 1.0;

        if (input.width() > max.width())
        {
            width_scale = static_cast<double>(max.width()) / static_cast<double>(input.width());
        }

        if (input.height() > max.height())
        {
            height_scale = static_cast<double>(max.height()) / static_cast<double>(input.height());
        }

        return (width_scale < height_scale ? width_scale : height_scale);
    }

}

int main(int argc, char *argv[])
try
{
    using utils::Logger;

    Logger::set_verbose(true);

    int option_index = 0;
    int option_id = 0;
    opterr = 0;

    std::string source_file{};
    std::string output_file{};
    std::string source_dir{};
    std::string output_dir{};
    watermark::Size max_size{};

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
            print_help();
            return EXIT_SUCCESS;
        }

        if (option_name == SIZE_ARG)
        {
            std::smatch matches;
            const std::regex size_expr("^([0-9]+),([0-9]+)");
            std::string in(optarg);
            if (std::regex_search(in, matches, size_expr))
            {
                max_size = watermark::Size{std::stoul(matches[1]), std::stoul(matches[2])};
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
            validate_dir(source_dir);
        }

        if (option_name == OUT_DIR_ARG)
        {
            output_dir = optarg;
            validate_dir(output_dir);
        }
    }

    if (max_size.is_empty())
    {
        throw std::invalid_argument("Maximum size is required");
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
    
    Logger::info() << "Requested size to fit: (" << max_size.width() << ", " << max_size.height() << ")";

    auto scale_fun = [&max_size](const std::string &img_path, const std::string& output_file) {
        watermark::Image img{img_path};
        Logger::info() << "Image to scale: " << img_path;
        Logger::info() << "Image size: " << img.size().width() << " x " << img.size().height();

        auto scaling_factor = calculate_scaling_factor(img.size(), max_size);
        Logger::info() << "Scaling factor: " << scaling_factor;

        if (scaling_factor != NO_SCALE) {
            img.scale(scaling_factor);
        }
        img.save(output_file);
        Logger::info() << "Scaled image: " << output_file;
        Logger::info() << "Scaled size: " << img.size().width() << " x " << img.size().height();
    };

    if (!source_dir.empty())
    {
        auto image_paths = find_images_in_dir(source_dir);

        for (const auto &image : image_paths)
        {
            output_file = create_out_file(image, output_dir);
            scale_fun(image, output_file);
        }
    }
    else
    {
        if (output_file.empty())
        {
            output_file = create_out_file(source_file, output_dir);
        }

        scale_fun(source_file, output_file);
    }

    return EXIT_SUCCESS;
}
catch (const watermark::Exception &e)
{
    utils::Logger::error() << "Scaling failed: " << e.what();
    return EXIT_FAILURE;
}
catch (const std::exception &e)
{
    utils::Logger::error() << "Execution failed: " << e.what();
    return EXIT_FAILURE;
}
