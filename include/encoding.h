#pragma once

#include <Windows.h>
#include <cuda.h>
#include <cuda_runtime.h>
#include <nvapi.h>
#include <nvEncodeAPI.h>
#include <dxgi.h>
#include <mutex>
#include <stdint.h>

#include "logger.h"
#include "deviceDetection.h"
#include "loadLibrary.h"

class Encoder
{

public:
    Encoder();
    ~Encoder();

private:
    CUdevice device;
    CUcontext context;
    HMODULE hLibrary;
    NV_ENCODE_API_FUNCTION_LIST functionList;
    NV_ENC_OPEN_ENCODE_SESSION_EX_PARAMS encodeParams;
    Loader loader;
    void* encodePointer;

    bool InitializeNVEncoder(CUcontext context);
    bool InitializeNVEncoder();
};

