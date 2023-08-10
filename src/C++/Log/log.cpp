#include "log.h"

Logger& Logger::getInstance() 
{
    static Logger instance;
    return instance;
}

Logger::Logger() 
{
    // TODO: fix so that path isn't hard-coded
    logger = spdlog::basic_logger_mt("my_logger", "%appdata%/rd-alps/log2.txt", true);
    spdlog::set_default_logger(logger);
    spdlog::set_level(spdlog::level::debug);
}

