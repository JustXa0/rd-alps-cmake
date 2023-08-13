#include "deviceDetection.h"

Monitor::Monitor()
{

    RetrieveFriendlyName();
    RetrieveWorkArea();

    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::string utf8_str = converter.to_bytes(mInfo.friendlyName.at(0));

    Logger::getInstance().log_i(utf8_str);

}

bool Monitor::RetrieveFriendlyName()
{
    std::vector<DISPLAYCONFIG_PATH_INFO> paths;
    std::vector<DISPLAYCONFIG_MODE_INFO> modes;
    UINT32 flags = QDC_ONLY_ACTIVE_PATHS;
    LONG isError = ERROR_INSUFFICIENT_BUFFER;

    UINT32 pathCount;
    UINT32 modeCount;
    isError = GetDisplayConfigBufferSizes(flags, &pathCount, &modeCount);

    if (isError)
    {
        Logger::getInstance().log_e("ERROR FINDING CONFIG BUFFER SIZES");
        return false;
    }

    paths.resize(pathCount);
    modes.resize(modeCount);

    isError = QueryDisplayConfig(flags, &pathCount, paths.data(), &modeCount, modes.data(), nullptr);

    paths.resize(pathCount);
    modes.resize(modeCount);

    if (isError)
    {
        Logger::getInstance().log_e("ERROR QUERING DISPLAY CONFIG");
        return false;
    }

    int len = paths.size();

    for (int i = 0; i < len; i++)
    {
        DISPLAYCONFIG_TARGET_DEVICE_NAME targetName = {};
        targetName.header.adapterId = paths[i].targetInfo.adapterId;
        targetName.header.id = paths[i].targetInfo.id;
        targetName.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_TARGET_NAME;
        targetName.header.size = sizeof(targetName);
        isError = DisplayConfigGetDeviceInfo(&targetName.header);

        if (isError)
        {
            Logger::getInstance().log_e("ERROR FINDING DEVICE INFO");
            return false;
        }

        mInfo.friendlyName.push_back(targetName.monitorFriendlyDeviceName);
    }

    Logger::getInstance().log_i("Successfully found friendly names of all monitors");
    return true;
}

bool Monitor::RetrieveWorkArea()
{
    HMONITOR hMonitor = MonitorFromPoint(POINT{0, 0}, MONITOR_DEFAULTTOPRIMARY);
    MONITORINFOEX monitorInfo;
    monitorInfo.cbSize = sizeof(MONITORINFOEX);

    if (!GetMonitorInfo(hMonitor, &monitorInfo))
    {
        Logger::getInstance().log_e("ERROR OCCURED FINDING PRIMARY HARDWARE HANDLE");
        return false;
    }

    BOOL enumResult = EnumDisplayMonitors(nullptr, nullptr, [](HMONITOR hMonitor, HDC, LPRECT, LPARAM lParam) -> BOOL
    {
        MONITORINFOEX monitorInfo;
        monitorInfo.cbSize = sizeof(MONITORINFOEX);
        if (!GetMonitorInfo(hMonitor, &monitorInfo))
        {
            Logger::getInstance().log_i("No additional monitors found");
            return FALSE;
        }

        MonitorInfo& info = *reinterpret_cast<MonitorInfo*>(lParam);
        info.workArea.push_back(monitorInfo.rcWork);
        return TRUE;
    }, reinterpret_cast<LPARAM>(&mInfo));

    if (!enumResult)
    {
        Logger::getInstance().log_e("ERROR OCCURRED DURING MONITOR ENUMERATION");
        return false;
    }

    return true;
}