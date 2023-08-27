#pragma once

#include <Windows.h>            // Win32 API header
#include <cuda.h>               // CUDA header
#include <cuda_runtime.h>   // CUDA runtime API header
#include <nvapi.h>              // NVAPI header
#include <dxgi.h>               // DirectX API header
#include <vector>               // Standard C header
#include <string>               // Standard C Header
#include <iostream>             // Standard C Header
#include <comdef.h>             // TODO: figure out what this header is
#include <Wbemidl.h>            // TODO: figure out what this header is
#include <locale>               // TODO: figure out what this header is
#include <codecvt>              // TODO: figure out what this header is

#include "logger.h"             // Logging header

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
    std::vector<UINT>           vendorId;
    std::vector<UINT>           hardwareId;
    std::vector<int>            cudaVersion;
    std::vector<int>            driverVersion;  
};

class Monitor
{

    public:
        Monitor();
        
        bool GetIndex(uint16_t& index);
        bool GetFriendlyName(uint16_t index, std::wstring& nameOut);
        bool GetDisplayArea(uint16_t index, RECT& displayOut);
        bool GetWorkArea(uint16_t index, RECT& workOut);

    private:
        MonitorInfo mInfo;

        bool RetrieveFriendlyName();
        bool RetrieveDisplayArea();
        bool RetrieveWorkArea();


};

class GPU
{

    public:
        GPU();
        ~GPU();

        bool GetIndex(uint16_t& index);
        bool GetVendorId(uint16_t index, UINT& vendorOut);
        bool GetHardwareId(uint16_t index, UINT& hardwareOut);
        bool GetCudaVersion(uint16_t index, int& cudaOut);
        bool GetDriverVersion(uint16_t index, int& driverOut);
        static bool CreateCudaContext(CUdevice device, CUcontext &context);
        static bool CreateDirectXInterface();

    private:
        GPUInfo gInfo;
        IDXGIFactory* pDXGIFactory;
        IDXGIAdapter* pDXGIAdapter;
        bool RetrieveVendorId();
        bool RetrieveHardwareId();
        bool RetrieveDriverVersion();

};
