#include "monitorInfoManager.h"

bool monitorInfoManager::RetrieveMonitorFriendlyName(std::vector<std::wstring>& friendlyName)
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
		return false;
	}

	paths.resize(pathCount);
	modes.resize(modeCount);

	isError = QueryDisplayConfig(flags, &pathCount, paths.data(), &modeCount, modes.data(), nullptr);

	paths.resize(pathCount);
	modes.resize(modeCount);

	if (isError)
	{
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
			return false;
		}

		friendlyName.push_back(targetName.monitorFriendlyDeviceName);
	}

	return true;
}

bool monitorInfoManager::RetrieveMonitorWorkArea(std::vector<RECT>& workArea)
{
	HMONITOR hMonitor = MonitorFromPoint(POINT{ 0, 0 }, MONITOR_DEFAULTTOPRIMARY);
	MONITORINFOEX monitorInfo;
	monitorInfo.cbSize = sizeof(MONITORINFOEX);

	if (!GetMonitorInfo(hMonitor, &monitorInfo))
	{
		std::cout << "ERROR OCCURED FINDING PRIMARY HARDWARE HANDLE" << std::endl;
		return false;
	}

	BOOL enumResult = EnumDisplayMonitors(nullptr, nullptr, [](HMONITOR hMonitor, HDC, LPRECT, LPARAM lParam) -> BOOL
		{
			MONITORINFOEX monitorInfo;
			monitorInfo.cbSize = sizeof(MONITORINFOEX);
			if (!GetMonitorInfo(hMonitor, &monitorInfo))
			{
				std::cout << "No additional monitors found" << std::endl;
				return FALSE;
			}

			std::vector<RECT>& workArea = *reinterpret_cast<std::vector<RECT>*>(lParam);
			workArea.push_back(monitorInfo.rcWork);
			return TRUE;
		}, reinterpret_cast<LPARAM>(&workArea));

	if (!enumResult)
	{
		std::cout << "ERROR OCCURRED DURING MONITOR ENUMERATION" << std::endl;
		return false;
	}

	return true;
}

bool monitorInfoManager::RetrieveMonitorDisplayArea(std::vector<RECT>& displayArea)
{
	HMONITOR hMonitor = MonitorFromPoint(POINT{ 0, 0 }, MONITOR_DEFAULTTOPRIMARY);
	MONITORINFOEX monitorInfo;
	monitorInfo.cbSize = sizeof(MONITORINFOEX);

	if (!GetMonitorInfo(hMonitor, &monitorInfo))
	{
		std::cout << "ERROR OCCURED FINDING PRIMARY HARDWARE HANDLE" << std::endl;
		return false;
	}

	BOOL enumResult = EnumDisplayMonitors(nullptr, nullptr, [](HMONITOR hMonitor, HDC, LPRECT, LPARAM lParam) -> BOOL
		{
			MONITORINFOEX monitorInfo;
			monitorInfo.cbSize = sizeof(MONITORINFOEX);
			if (!GetMonitorInfo(hMonitor, &monitorInfo))
			{
				std::cout << "No additional monitors found" << std::endl;
				return FALSE;
			}

			std::vector<RECT>& displayArea = *reinterpret_cast<std::vector<RECT>*>(lParam);
			//	displayArea.push_back(monitorInfo.);
			return TRUE;
		}, reinterpret_cast<LPARAM>(&displayArea));

	if (!enumResult)
	{
		std::cout << "ERROR OCCURRED DURING MONITOR ENUMERATION" << std::endl;
		return false;
	}

	return true;


}