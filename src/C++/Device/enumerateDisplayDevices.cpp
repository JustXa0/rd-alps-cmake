#include "enumerateDisplayDevices.h"

enumerateDisplayDevices::enumerateDisplayDevices()
{
    DISPLAY_DEVICE displayDevice;
    Devices devices;
    devices.cb = sizeof(DISPLAY_DEVICE);
    displayDevice.cb = sizeof(DISPLAY_DEVICE);
    DWORD deviceIndex = 0;


}

enumerateDisplayDevices::~enumerateDisplayDevices()
{
    
}