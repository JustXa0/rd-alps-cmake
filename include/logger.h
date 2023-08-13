#pragma once

#include <spdlog/spdlog.h>
#include "spdlog/sinks/basic_file_sink.h"
#include <locale>           // TODO: figure out what this header is
#include <codecvt>          // TODO: figure out what this header is
#include <iostream>


class Logger
{
public:
    static Logger& getInstance();

    template <typename T>
    void log_w(T message)
    {
        logger->warn(message);
        logger->flush();
    }

    template <typename T>
    void log_e(T message)
    {
        logger->error(message);
        logger->flush();
    }

    template <typename T>
    void log_c(T message)
    {
        logger->critical(message);
        logger->flush();
    }

    template <typename T>
    void log_t(T message)
    {
        logger->trace(message);
        logger->flush();
    }

    template <typename T>
    void log_d(T message)
    {
        logger->debug(message);
        logger->flush();
    }

    template <typename T>
    void log_i(T message)
    {
        logger->info(message);
        logger->flush();
    }

    // Template methods for wstring messages for debugging
    template <>
    void log_w<std::wstring>(std::wstring message)
    {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        std::string utf8_str = converter.to_bytes(message);

        logger->warn(utf8_str);
        logger->flush();
    }

    template <>
    void log_e<std::wstring>(std::wstring message)
    {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        std::string utf8_str = converter.to_bytes(message);

        logger->error(utf8_str);
        logger->flush();
    }

    template <>
    void log_c<std::wstring>(std::wstring message)
    {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        std::string utf8_str = converter.to_bytes(message);

        logger->critical(utf8_str);
        logger->flush();
    }

    template <>
    void log_t<std::wstring>(std::wstring message)
    {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        std::string utf8_str = converter.to_bytes(message);

        logger->trace(utf8_str);
        logger->flush();
    }

    template <>
    void log_d<std::wstring>(std::wstring message)
    {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        std::string utf8_str = converter.to_bytes(message);

        logger->debug(utf8_str);
        logger->flush();
    }

    template <>
    void log_i<std::wstring>(std::wstring message)
    {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        std::string utf8_str = converter.to_bytes(message);

        logger->info(utf8_str);
        logger->flush();
    }

private:
    Logger();

    std::shared_ptr<spdlog::logger> logger;
};