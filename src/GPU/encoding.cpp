#include "encoding.h"

// Start of Encoder class defining

Encoder::Encoder()
{
    device = 0;
    context = NULL;

    GPU::CreateCudaContext(device, context);
    Encoder::InitializeNVEncoder(context);
}

Encoder:: ~Encoder()
{
}

bool Encoder::InitializeNVEncoder(CUcontext contextIn)
{
    NV_ENCODE_API_FUNCTION_LIST functionList;
    if (NvEncodeAPICreateInstance(&functionList) != NV_ENC_SUCCESS)
    {
        Logger::getInstance().log_e("ERROR CREATING NVENCODEAPI INSTANCE");
        return false;
    }

    NV_ENC_OPEN_ENCODE_SESSION_EX_PARAMS encodeParams = {};  // Initialize with required configuration
    encodeParams.version = NV_ENC_OPEN_ENCODE_SESSION_EX_PARAMS_VER;
    encodeParams.deviceType = NV_ENC_DEVICE_TYPE_CUDA;
    encodeParams.device = contextIn;
    encodeParams.reserved = nullptr;
    encodeParams.apiVersion = NVENCAPI_VERSION;

    NV_ENC_INITIALIZE_PARAMS initializeParams = {};  // Initialize with required configuration

    NV_ENC_CONFIG encodeConfig = {};  // Initialize with required configuration

    NVENCSTATUS openStatus = NvEncOpenEncodeSessionEx(&encodeParams, &encodePointer);
    if (openStatus != NV_ENC_SUCCESS)
    {
        Logger::getInstance().log_e("ERROR GATHERING ENCODE SESSION POINTER");
        return false;
    }

    return true;
}

    
    