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
#include <sstream>

namespace
{
    // Version
    const uint8_t MAJOR_VERSION{0U};
    const uint8_t MINOR_VERSION{1U};

    std::string app_version()
    {
        std::stringstream ss;
        ss << static_cast<int>(MAJOR_VERSION) << "." << static_cast<int>(MINOR_VERSION);
        return ss.str();
    }

    // Arguments
    const char MARK_ARG[] = "mark";
    const char MARK_SIZE_ARG[] = "size";
    const char SRC_ARG[] = "src";
    const char SRC_DIR_ARG[] = "src_dir";
    const char OUT_ARG[] = "out";
    const char OUT_DIR_ARG[] = "out_dir";
    const char LAYOUT_ARG[] = "layout";
    const char OPACITY_ARG[] = "opacity";
    const char HELP_ARG[] = "help";
    const char VERBOSE_ARG[] = "verbose";

    // Layout arguments
    const std::string TOP_LEFT = "top-left";
    const std::string TOP_MID = "top-mid";
    const std::string TOP_RIGHT = "top-right";
    const std::string MID_LEFT = "middle-left";
    const std::string CENTER = "center";
    const std::string MID_RIGHT = "middle-right";
    const std::string BOTTOM_LEFT = "bottom-left";
    const std::string BOTTOM_MID = "bottom-mid";
    const std::string BOTTOM_RIGHT = "bottom-right";

    // Options
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
        {VERBOSE_ARG, no_argument, nullptr, 0},
        {0, 0, 0, 0}};

    // Defaults
    const std::string DEFAULT_LAYOUT{BOTTOM_RIGHT};
    const watermark::Opacity DEFAULT_OPACITY{0.5f};

    class Log_stream
    {
    public:
        explicit Log_stream(std::ostream &stream, bool silent) : m_stream{stream}, m_silent{silent} {}

        Log_stream() = delete;
        Log_stream(const Log_stream &) = delete;
        Log_stream &operator=(const Log_stream &) = delete;
        Log_stream(Log_stream &&) = default;
        Log_stream &operator=(Log_stream &&) = default;

        template <typename T>
        const Log_stream &print(T &&value) const
        {
            if (!m_silent)
            {
                m_stream << std::forward<T>(value);
            }
            return *this;
        }

        ~Log_stream() noexcept
        {
            if (!m_silent)
            {
                m_stream << std::endl;
            }
        }

    private:
        std::ostream &m_stream;
        bool m_silent{false};
    };

    class Logger
    {
    public:
        static Logger &instance()
        {
            static Logger m_instance;

            return m_instance;
        }

        static Log_stream info()
        {
            return Logger::instance().info_stream();
        }

        static Log_stream error()
        {
            return Logger::instance().error_stream();
        }

    public:
        Log_stream info_stream() noexcept
        {
            Log_stream stream{std::cout, !m_verbose};
            stream.print("INFO\t");

            return stream;
        }

        Log_stream error_stream() noexcept
        {
            Log_stream stream{std::cerr, false};
            stream.print("ERROR\t");

            return stream;
        }

        void set_verbose(bool verbose)
        {
            m_verbose = verbose;
        }

    private:
        bool m_verbose{false};
    };

    template <typename T>
    const Log_stream &operator<<(const Log_stream &stream, T &&value)
    {
        stream.print(std::forward<T>(value));

        return stream;
    }

    template <typename T>
    void log_non_empty(const std::string &text, T &&value)
    {
        if (!value.empty())
        {
            Logger::info() << text << value;
        }
    }

    void print_help()
    {
        std::cout << "watermark cli, " << app_version() << "\n";
        std::cout << "\nApplication takes an input watermark image and applies the watermark for the source image or images which are found in the directory specified by the user.\n";

        std::cout << "\nUsage 1:\n";
        std::cout << "\twatermark_cli --" << MARK_ARG << " <mark> --" << SRC_ARG << " <image> --"
                  << OUT_ARG << " <output_image> --" << LAYOUT_ARG << " <layout> --" << MARK_SIZE_ARG << " <mark_size> --"
                  << OPACITY_ARG << " <opacity>\n";

        std::cout << "\nUsage 2:\n";
        std::cout << "\twatermark_cli --" << MARK_ARG << " <mark> --" << SRC_DIR_ARG << " <dir_with_images> --"
                  << OUT_DIR_ARG << " <output_dir> --" << LAYOUT_ARG << " <layout> --" << MARK_SIZE_ARG << " <mark_size> --"
                  << OPACITY_ARG << " <opacity>\n";

        std::cout << "\nArguments:\n";
        std::cout << "\t" << MARK_ARG << "\twatermark image to be applied (mandatory)\n";
        std::cout << "\t" << SRC_ARG << "\tsource image to be watermarked (mandatory if " << SRC_DIR_ARG << " is not specified)\n";
        std::cout << "\t" << SRC_DIR_ARG << "\tdirectory with images to be watermarked (mandatory if " << SRC_ARG << " is not specified)\n";
        std::cout << "\t" << OUT_ARG << "\toutput file, where watermarked image will be saved (default: same as source with _marked postfix)\n";
        std::cout << "\t" << OUT_DIR_ARG << "\toutput directory, where watermarked images will be saved\n";
        std::cout << "\t" << LAYOUT_ARG << "\tlayout of watermark (default: " << DEFAULT_LAYOUT << ". Available layouts:\n";
        std::cout << "\t\t" << TOP_LEFT << ", " << TOP_MID << ", " << TOP_RIGHT << ", "
                  << MID_LEFT << ", " << CENTER << ", " << MID_RIGHT << ", "
                  << BOTTOM_LEFT << ", " << BOTTOM_MID << ", " << BOTTOM_RIGHT << "\n";
        std::cout << "\t" << MARK_SIZE_ARG << "\twatermark size expressed in pixels (default: original watermark size). Format:\n";
        std::cout << "\t\t--" << MARK_SIZE_ARG << " width,height, i.e.: 100,100\n";
        std::cout << "\t" << OPACITY_ARG << "\topacity of watermark (default: " << DEFAULT_OPACITY << ")\n";
        std::cout << "\t" << VERBOSE_ARG << "\tenables logging\n";
        std::cout << "\t" << HELP_ARG << "\tshows help\n";

        std::cout << "\nSamples:\n";
        std::cout << "\twatermark_cli --" << MARK_ARG << " /home/guest/logo.png --" << SRC_ARG << " /home/guest/mountains.png --"
                  << OUT_ARG << " /home/guest/mountains_marked.png --" << LAYOUT_ARG << " center --" << MARK_SIZE_ARG << " 100,100 --"
                  << OPACITY_ARG << " 0.8\n";
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
        out_path += "_marked";
        out_path += extension;

        return out_path;
    }

    std::vector<std::string> find_images_in_dir(const std::string &dir)
    {
        std::vector<std::string> images;

        auto dir_path = get_dir_path(dir);

        for (const auto &entry : std::filesystem::directory_iterator(dir_path))
        {
            // TODO: how to print?
            // std::cout << entry << std::endl;
            const auto &path = entry.path();
            if (watermark::Image::is_image(path))
            {
                images.push_back(path);
            }
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
    Logger logger;

    int option_index = 0;
    int option_id = 0;
    opterr = 0;

    std::string mark_file{};
    std::string source_file{};
    std::string output_file{};
    std::string source_dir{};
    std::string output_dir{};
    watermark::Size mark_size{};
    watermark::Layout layout = to_layout(DEFAULT_LAYOUT);
    watermark::Opacity opacity{DEFAULT_OPACITY};

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
            validate_dir(source_dir);
        }

        if (option_name == OUT_DIR_ARG)
        {
            output_dir = optarg;
            validate_dir(output_dir);
        }

        if (option_name == LAYOUT_ARG)
        {
            layout = to_layout(optarg);
        }

        if (option_name == OPACITY_ARG)
        {
            opacity = std::stof(optarg);
        }

        if (option_name == VERBOSE_ARG)
        {
            logger.set_verbose(true);
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

    watermark::Image logo{mark_file};
    if (mark_size.is_empty())
    {
        mark_size = logo.size();
    }

    if (!source_dir.empty())
    {
        auto image_paths = find_images_in_dir(source_dir);
        watermark::Watermark mark{std::move(logo)};

        for (const auto &image : image_paths)
        {
            watermark::Image img{image};

            output_file = create_out_file(image, output_dir);

            log_non_empty("Mark file: ", mark_file);
            log_non_empty("Source file: ", image);
            log_non_empty("Output file: ", output_file);
            log_non_empty("Source dir: ", source_dir);
            log_non_empty("Output dir: ", output_dir);
            log_non_empty("Output file: ", output_file);

            logger.info() << "Layout: " << static_cast<int>(layout);
            logger.info() << "Size: " << mark_size.width() << "x" << mark_size.height();
            logger.info() << "Opacity: " << opacity;

            auto result = mark.apply_to(img, layout, mark_size, opacity);
            result.save(output_file);
        }
    }
    else
    {
        watermark::Image image{source_file};

        if (output_file.empty())
        {
            output_file = create_out_file(source_file, output_dir);
        }

        log_non_empty("Mark file: ", mark_file);
        log_non_empty("Source file: ", source_file);
        log_non_empty("Output file: ", output_file);
        log_non_empty("Source dir: ", source_dir);
        log_non_empty("Output dir: ", output_dir);
        log_non_empty("Output file: ", output_file);
        logger.info() << "Layout: " << static_cast<int>(layout);
        logger.info() << "Size: " << mark_size.width() << "x" << mark_size.height();
        logger.info() << "Opacity: " << opacity;

        watermark::Watermark mark{std::move(logo)};
        auto result = mark.apply_to(image, layout, mark_size, opacity);
        result.save(output_file);
    }

    return EXIT_SUCCESS;
}
catch (const watermark::Exception &e)
{
    Logger::error() << "Watermarking failed: " << e.what();
    return EXIT_FAILURE;
}
catch (const std::exception &e)
{
    Logger::error() << "Execution failed: " << e.what();
    return EXIT_FAILURE;
}
