#pragma once

#include <spdlog/spdlog.h>
#include "spdlog/sinks/basic_file_sink.h"

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

private:
    Logger();

    std::shared_ptr<spdlog::logger> logger;
};