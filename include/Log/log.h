#pragma once

#include <spdlog/spdlog.h>
#include "spdlog/sinks/basic_file_sink.h"


class Logger
{
    public:
        static Logger& getInstance();

        template <typename T>
        void log(T message)
        {
            logger->info(message);
            logger->flush();
        }

    private:
        Logger();

        
        std::shared_ptr<spdlog::logger> logger;
};