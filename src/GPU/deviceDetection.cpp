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

bool Monitor::GetIndex(uint16_t& index)
{
    if (mInfo.size == NULL || mInfo.size == 0)
    {
        Logger::getInstance().log_e("MONITOR INFO STRUCTURE UNINITIALIZED");
        return false;
    }

    index = mInfo.size;
    return true;
}

bool Monitor::GetFriendlyName(uint16_t index, std::wstring& nameOut)
{
    if (mInfo.size < index)
    {
        Logger::getInstance().log_e("INDEX OUT OF REACH");
        return false;
    }

    nameOut = mInfo.friendlyName.at(index);
    return true;
}

bool Monitor::GetDisplayArea(uint16_t index, RECT& displayOut)
{
    if (mInfo.size < index)
    {
        Logger::getInstance().log_e("INDEX OUT OF REACH");
        return false;
    }

    displayOut = mInfo.displayArea.at(index);
    return true;
}

bool Monitor::GetWorkArea(uint16_t index, RECT& workOut)
{
    if (mInfo.size < index)
    {
        Logger::getInstance().log_e("INDEX OUT OF REACH");
        return false;
    }

    workOut = mInfo.workArea.at(index);
    return true;
}

// Begin GPU class defining

GPU::GPU()
{
    pDXGIFactory = nullptr;
    HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&pDXGIFactory);

    pDXGIAdapter = nullptr;

    RetrieveHardwareId();
    RetrieveVendorId();
    RetrieveDriverVersion();

    Logger::getInstance().log_i(gInfo.vendorId.at(0));
    Logger::getInstance().log_i(gInfo.hardwareId.at(0));
    Logger::getInstance().log_i(gInfo.cudaVersion.at(0));
    Logger::getInstance().log_i(gInfo.driverVersion.at(0));
    //Logger::getInstance().log_i(gInfo.driverVersion.at(1));
}

GPU::~GPU()
{
    pDXGIFactory->Release();

    pDXGIAdapter->Release();

    NvAPI_Unload();
}

bool GPU::RetrieveVendorId()
{
    pDXGIFactory->EnumAdapters(0, &pDXGIAdapter);

    DXGI_ADAPTER_DESC adapterDesc;
    pDXGIAdapter->GetDesc(&adapterDesc);

    gInfo.vendorId.push_back(adapterDesc.VendorId);
    
    return true;
}

bool GPU::RetrieveHardwareId()
{
    pDXGIFactory->EnumAdapters(0, &pDXGIAdapter);

    DXGI_ADAPTER_DESC adapterDesc;
    pDXGIAdapter->GetDesc(&adapterDesc);

    gInfo.hardwareId.push_back(adapterDesc.DeviceId);

    return true;
}

bool GPU::RetrieveDriverVersion()
{
    // Getting cuda version to be targeted later
    int cudaVersion;

    cudaError_t cudaStatus = cudaDriverGetVersion(&cudaVersion);

    if (cudaStatus != cudaSuccess)
    {
        std::string error = cudaGetErrorString(cudaStatus);
        Logger::getInstance().log_e("CUDA DRIVER QUERY FAILED: " + error);
        return false;
    }

    gInfo.cudaVersion.push_back(cudaVersion);

    // TODO: Handle error for when no NvAPI is found
    NvAPI_Initialize();

    NvU32 driverVersion = 0;
    NvAPI_ShortString buildBranchVersion;

    NvAPI_Status status = NvAPI_SYS_GetDriverAndBranchVersion(&driverVersion, buildBranchVersion);

    if (status == NVAPI_OK)
    {
        Logger::getInstance().log_i("Successfuly gathered driver and branch version");
        gInfo.driverVersion.push_back(driverVersion);
        return true;
    }

    Logger::getInstance().log_e("ERROR GATHERING DRIVER AND BRANCH VERSION");
    return false;

    // Getting Nvidia driver version to be checked later

    //if (nvapiModule)
    //{
        //typedef int(*NvAPI_QueryInterface_t)(unsigned int offset);
       // NvAPI_QueryInterface_t NvAPI_QueryInterface = (NvAPI_QueryInterface_t)GetProcAddress(nvapiModule, "nvapi_QueryInterface");

        //if (NvAPI_QueryInterface)
        //{
            //typedef int(*NvAPI_SYS_GetDriverAndBranchVersion_t)(NvU32* driverVersion, NvAPI_ShortString buildBranchVersion);
            //NvAPI_SYS_GetDriverAndBranchVersion_t NvAPI_SYS_GetDriverAndBranchVersion = (NvAPI_SYS_GetDriverAndBranchVersion_t)(*NvAPI_QueryInterface)(0x0150E828);

            //if (NvAPI_SYS_GetDriverAndBranchVersion)
            //{
               // NvU32 driverVersion = 0;
                //NvAPI_ShortString buildBranchString;

               // if (NvAPI_SYS_GetDriverAndBranchVersion(&driverVersion, buildBranchString) == 0)
               // {
                 //   gInfo.driverVersion.push_back(HIWORD(driverVersion));
                 //   gInfo.driverVersion.push_back(LOWORD(driverVersion));
                    //Logger::getInstance().log_i("Driver Version: " + HIWORD(driverVersion) + "." + LOWORD(driverVersion));
               // }

           // }

       // }

    //}
    //else
    //{
       // Logger::getInstance().log_e("FAILED TO LOAD nvapi64.dll");
    //}

    //FreeLibrary(nvapiModule);

    return true;
}

bool GPU::GetIndex(uint16_t& index)
{
    index = gInfo.size;
    return true;
}

bool GPU::GetVendorId(uint16_t index, UINT& vendorOut)
{
    if (index > gInfo.size)
    {
        Logger::getInstance().log_e("INDEX IS HIGHER THAN STRUCT");
        return false;
    }

    vendorOut = gInfo.vendorId.at(index);
    return true;
}

bool GPU::GetHardwareId(uint16_t index, UINT& hardwareOut)
{
    if (index > gInfo.size)
    {
        Logger::getInstance().log_e("INDEX IS HIGHER THAN STRUCT");
        return false;
    }

    hardwareOut = gInfo.hardwareId.at(index);
    return true;
}

bool GPU::GetCudaVersion(uint16_t index, int& cudaOut)
{
    if (index > gInfo.size)
    {
        Logger::getInstance().log_e("INDEX IS HIGHER THAN STRUCT");
        return false;
    }

    cudaOut = gInfo.cudaVersion.at(index);
    return true;
}

bool GPU::GetDriverVersion(uint16_t index, int& driverOut)
{
    if (index > gInfo.size)
    {
        Logger::getInstance().log_e("INDEX IS HIGHER THAN STRUCT");
        return false;
    }

    driverOut = gInfo.driverVersion.at(index);
    return true;
}