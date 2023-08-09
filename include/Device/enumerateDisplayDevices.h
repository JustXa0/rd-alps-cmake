#include <Windows.h>    // Win32 API header
#include <dxgi.h>       // DirectX API header
#include <iostream>     // Standard C header
#include <vector>       // Standard C header

#include "log.h"        // Logging system


class enumerateDisplayDevices
{
    private:

        struct Devices
        {
            DWORD cb;
            std::vector<CHAR> DeviceName [32];
            std::vector<CHAR> DeviceString [128];
            std::vector<CHAR> DeviceID [128];
            std::vector<CHAR> DeviceKey [128];
        };

    public:

        enumerateDisplayDevices();
        ~enumerateDisplayDevices();

        CHAR getDeviceName(int index);
        CHAR getDisplayString(int index);
        CHAR getDeviceID(int index);
        CHAR getDeviceKey(int index);


};