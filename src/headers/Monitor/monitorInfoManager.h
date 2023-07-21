#pragma once
#include <Windows.h>
#include <vector>
#include <string>
#include <iostream>
#include <comdef.h>
#include <Wbemidl.h>

#pragma comment(lib, "wbemuuid.lib")

struct MonitorInfo
{
	std::vector<std::wstring> friendlyName;
	std::vector<RECT> displayArea;
	std::vector<RECT> workArea;
};

class monitorInfoManager
{
private:



public:
	bool RetrieveMonitorFriendlyName(std::vector<std::wstring>& friendlyName);
	bool RetrieveMonitorDisplayArea(std::vector<RECT>& displayArea);
	bool RetrieveMonitorWorkArea(std::vector<RECT>& workArea);



};