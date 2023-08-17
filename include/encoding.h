#pragma once

#include <nvEncodeAPI.h>
#include <cuda.h>
#include <cuda_runtime_api.h>

#include "logger.h"

class Encoder
{
public:
    Encoder();
    ~Encoder();

private:
    NVENCSTATUS status;
    NV_ENCODE_API_FUNCTION_LIST list;
    NV_ENC_OPEN_ENCODE_SESSION_EX_PARAMS encodeSessionParams;
    void* encoderSession;
    CUresult result;
    CUcontext context;
    CUdevice device;

    bool createCudaContext(CUcontext context);
};
