#include "logger.h"

Logger& Logger::getInstance()
{
    static Logger instance;
    return instance;
}

Logger::Logger()
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::string utf8_str = converter.to_bytes(Logger::GetRoamingFolder());
    utf8_str += "/alps/log.txt";
    logger = spdlog::basic_logger_mt("my_logger", utf8_str, true);
    spdlog::set_default_logger(logger);
    spdlog::set_level(spdlog::level::debug);
}

std::wstring Logger::GetRoamingFolder()
{
    PWSTR path = nullptr;
    std::wstring backup = L"./alps";
    HRESULT result = SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, nullptr, &path);

    if (SUCCEEDED(result))
    {
        std::wstring roamingPath = path;
        CoTaskMemFree(path);
        return roamingPath;
    }

    else
    {
        Logger::getInstance().log_e("ERROR FINDNG ROAMING FOLDER, DEFAULTING TO ./ FOLDER");
        return backup;
    }
}