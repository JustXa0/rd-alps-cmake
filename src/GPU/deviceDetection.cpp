#include "deviceDetection.h"

Monitor::Monitor()
{
    RetrieveDisplayArea();
    RetrieveFriendlyName();
    RetrieveWorkArea();
    mInfo.size = mInfo.friendlyName.size();

    for (int i = 0; i < mInfo.size; i++)
    {
        Logger::getInstance().log_i(mInfo.friendlyName.at(i));
        Logger::getInstance().log_i(mInfo.displayArea.at(i).right - mInfo.displayArea.at(i).left);
        Logger::getInstance().log_i(mInfo.displayArea.at(i).bottom - mInfo.displayArea.at(i).top);
        Logger::getInstance().log_i(mInfo.workArea.at(i).right - mInfo.displayArea.at(i).left);
        Logger::getInstance().log_i(mInfo.workArea.at(i).bottom - mInfo.displayArea.at(i).top);
    }
    
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

bool Monitor::RetrieveDisplayArea()
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
        info.displayArea.push_back(monitorInfo.rcMonitor);
    }, reinterpret_cast<LPARAM>(&mInfo));

    if (!enumResult)
    {
        Logger::getInstance().log_e("ERROR OCCURRED DURING MONITOR ENUMERATION");
        return false;
    }
    
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

// TODO: implement error handling in the following methods:
// GetIndex, GetFriendlyName, GetDisplayArea, GetWorkArea

bool Monitor::GetIndex(uint16_t& index)
{
    index = mInfo.size;
    return true;
}

bool Monitor::GetFriendlyName(uint16_t index, std::wstring& nameOut)
{
    nameOut = mInfo.friendlyName.at(index);
    return true;
}

bool Monitor::GetDisplayArea(uint16_t index, RECT& displayOut)
{
    displayOut = mInfo.displayArea.at(index);
    return true;
}

bool Monitor::GetWorkArea(uint16_t index, RECT& workOut)
{
    workOut = mInfo.workArea.at(index);
    return true;
}
