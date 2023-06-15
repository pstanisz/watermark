// Copyright (c) 2023, Piotr Staniszewski

#pragma once

#include <iostream>

namespace utils
{

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

        static void set_verbose(bool verbose)
        {
            Logger::instance().m_verbose = verbose;
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

}
