#pragma once

#include <windows.h>
#include <nvEncodeAPI.h>
#include <cuda.h>
#include <cuda_runtime.h>

#include "logger.h"
#include "deviceDetection.h"

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
    void* encodePointer;

    bool InitializeNVEncoder(CUcontext context);

};
