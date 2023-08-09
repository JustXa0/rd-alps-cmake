#include "enumerateDisplayDevices.h"

enumerateDisplayDevices::enumerateDisplayDevices()
{  
    DISPLAY_DEVICE displayDevice;
    Devices devices;
    devices.cb = sizeof(DISPLAY_DEVICE);
    displayDevice.cb = sizeof(DISPLAY_DEVICE);
    DWORD deviceIndex = 0;

    while (EnumDisplayDevices(NULL, deviceIndex++, &displayDevice, 0))
    {
        DEVMODE devMode;
        devMode.dmSize = sizeof(DEVMODE);


        //Not sure if needed, will be checked later        
        if (EnumDisplaySettings(displayDevice.DeviceName, ENUM_CURRENT_SETTINGS, &devMode))
        {

        }

        IDXGIFactory* pDXGIFactory = nullptr;
        if (SUCCEEDED(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&pDXGIFactory)))
        {
            IDXGIAdapter* pDXGIAdapter = nullptr;
            if (SUCCEEDED(pDXGIFactory->EnumAdapters(deviceIndex - 1, &pDXGIAdapter))) {
                DXGI_ADAPTER_DESC adapterDesc;
                if (SUCCEEDED(pDXGIAdapter->GetDesc(&adapterDesc))) {
                    std::wcout << "Adapter Description: " << adapterDesc.Description << std::endl;
                    std::wcout << "Dedicated Video Memory: " << adapterDesc.DedicatedVideoMemory / (1024 * 1024) << " MB" << std::endl;
                }
                else
                {
                    // TODO: handle error here and log at highest level
                }
                pDXGIAdapter->Release();
            }
            else
            {
                // TODO: handle error here and log at highest level
            }
            pDXGIFactory->Release();
        }
        else
        {
            // TODO: handle error here and log at highest level
        }

    }
    
}

enumerateDisplayDevices::~enumerateDisplayDevices()
{
    
}