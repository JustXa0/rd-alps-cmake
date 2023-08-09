#include "enumerateDisplayDevices.h"

enumerateDisplayDevices::enumerateDisplayDevices()
{  
    Logger::getInstance().log_i("CREATING ENUMERATE DEVICES CLASS");

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
                Logger::getInstance().log_i(adapterDesc.VendorId);
                Logger::getInstance().log_i(adapterDesc.DeviceId);
                //Logger::getInstance().log_i(adapterDesc.Description);
                }
                else
                {
                    // TODO: handle error here and log at highest level
                    Logger::getInstance().log_c("FAILED TO FIND DESCRIPTION OF ADAPTER");
                }
                pDXGIAdapter->Release();
            }
            else
            {
                // TODO: handle error here and log at highest level
                Logger::getInstance().log_c("FAILED TO ENUMERATE ADAPTERS");
            }
            pDXGIFactory->Release();
        }
        else
        {
            // TODO: handle error here and log at highest level
            Logger::getInstance().log_c("FAILED TO CREATE FACTORY");
        }

    }
    
}

enumerateDisplayDevices::~enumerateDisplayDevices()
{
    
}