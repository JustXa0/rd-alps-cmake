#include "log.h"

std::string log::time_stamp()
{
    auto now = std::time(nullptr);
    char cstr [256] {};
    return std::strftime( cstr, sizeof(cstr), "%Y%m%d_%H%M%S", std::localtime(&now) ) ? cstr : "" ;
}

std::string log::path()
{
    std::string log_dir = "/tmp/log/";
    std::string log_file_name = "log.txt";
    return log_dir + time_stamp() + '_' + log_file_name;
}

void log::flush()
{
    out.flush();
}