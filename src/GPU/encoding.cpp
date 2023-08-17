#include "encoding.h"

Encoder::Encoder()
{
    status = NvEncodeAPICreateInstance(&list);
    encodeSessionParams = {};
    encoderSession = nullptr;
    context = NULL;
    device = 0;
    
    if (status != NV_ENC_SUCCESS)
    {
        Logger::getInstance().log_e("FAILED TO CREATE NVENCODE INSTANCE");
    }

    if (!createCudaContext(context))
    {
        // TODO: handle error here
    }

    encodeSessionParams.version = NV_ENC_OPEN_ENCODE_SESSION_EX_PARAMS_VER;
    encodeSessionParams.device = context;
    encodeSessionParams.deviceType = NV_ENC_DEVICE_TYPE_CUDA;

    // Open the NVENC encode session
    NVENCSTATUS nvEncStatus = NvEncOpenEncodeSessionEx(&encodeSessionParams, &encoderSession);
    if (nvEncStatus != NV_ENC_SUCCESS)
    {
        // TODO: handle NVENC session opening error
        Logger::getInstance().log_e("ERROR OPENING A NVENC SESSION");
    }

}

Encoder::~Encoder()
{
    //Release();
    cudaDeviceReset();
    NvEncDestroyEncoder(&encoderSession);
}

bool Encoder::createCudaContext(CUcontext cuContext)
{
   result = cuInit(0);
   if (result != cudaSuccess)
   {
        // Handle error here
        return false;
   }

   int deviceCount = 0;
   result = cuDeviceGetCount(&deviceCount);
   if (result != cudaSuccess)
   {
        // Handle error here
        return false;
   }

   if (deviceCount == 0)
   {
        // Handle error here
        Logger::getInstance().log_e("NO CUDA DEVICES FOUND");
        return false;
   }

   result = cuDeviceGet(&device, 0);
   if (result != cudaSuccess)
   {
        // Handle error here
        return false;
   }

    result = cuCtxCreate(&context, 0, device);
    if (result != cudaSuccess)
    {
        // Handle error here
        return false;
    }
}

