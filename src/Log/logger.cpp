#include "logger.h"

Logger& Logger::getInstance()
{
    static Logger instance;
    return instance;
}

Logger::Logger()
{
    // TODO: fix so that path isn't hard-coded
    logger = spdlog::basic_logger_mt("my_logger", "C:/Users/Jamie/AppData/Roaming/alps/log.txt", true);
    spdlog::set_default_logger(logger);
    spdlog::set_level(spdlog::level::debug);
}