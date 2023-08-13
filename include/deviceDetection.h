#pragma once
#include <Windows.h>        // Win32 API header
#include <dxgi.h>           // DirectX API header
#include <vector>           // Standard C header
#include <string>           // Standard C Header
#include <iostream>         // Standard C Header
#include <comdef.h>         // TODO: figure out what this header is
#include <Wbemidl.h>        // TODO: figure out what this header is

#include "logger.h"         // Logging header

typedef struct MonitorInfo
{
    uint16_t                    size;
    std::vector<std::wstring>   friendlyName;
    std::vector<RECT>           displayArea;
    std::vector<RECT>           workArea;
};

typedef struct GPUInfo
{
    uint16_t                    size;

}

class Monitor
{

    public:
        Monitor();
        
        bool GetIndex();
        bool GetFriendlyName(uint16_t index, std::wstring& nameOut);
        bool GetDisplayArea(uint16_t index, RECT& displayOut);
        bool GetWorkArea(uint16_t index, RECT& workOut);

    private:
        MonitorInfo info;


};

class GPU
{

    public:

    private:
        GPUInfo info;

}
