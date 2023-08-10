#include "enumerateDisplayDevices.h"

enumerateDisplayDevices::enumerateDisplayDevices()
{
    // TODO: rewrite for error handling and multiple devices.
    // I can't stand DirectX

    Logger::getInstance().log_e("CREATING ENUMERATION CLASS");

    IDXGIFactory* pDXGIFactory = nullptr;
    HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&pDXGIFactory);

    IDXGIAdapter* pDXGIAdapter = nullptr;
    pDXGIFactory->EnumAdapters(0, &pDXGIAdapter);
    
    DXGI_ADAPTER_DESC adapterDesc;
    pDXGIAdapter->GetDesc(&adapterDesc);
    
    Logger::getInstance().log_e(adapterDesc.VendorId);

}

enumerateDisplayDevices::~enumerateDisplayDevices()
{
    
}