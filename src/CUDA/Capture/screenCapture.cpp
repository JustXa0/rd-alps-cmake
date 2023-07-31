#include "screenCapture.h"

bool screenCapture::initialize(CUcontext cuContext, CUdevice cuDevice)
{
    cuInit(0);                                          // Initializes the CUDA driver API
    switch(cuDeviceGet(&cuDevice, 0))                   // Gets the first avaliable CUDA-capable device TODO: allow users to select which device to encode on
     {
        case CUDA_ERROR_INVALID_DEVICE:
            // TODO: create a logging system to log these errors
            return false;
        case CUDA_ERROR_DEINITIALIZED:
            return false;
        case CUDA_ERROR_NOT_INITIALIZED:
            return false;
        case CUDA_ERROR_INVALID_CONTEXT:
            return false;
        case CUDA_ERROR_INVALID_VALUE:
            return false;
     }
     
     
           
    switch(cuCtxCreate(&cuContext, 0, cuDevice))    // Creates CUDA context
    {
        case CUDA_ERROR_DEINITIALIZED:
            return false;
        case CUDA_ERROR_NOT_INITIALIZED:
            return false;
        case CUDA_ERROR_INVALID_CONTEXT:
            return false;
        case CUDA_ERROR_INVALID_VALUE:
            return false;
        case CUDA_ERROR_OUT_OF_MEMORY:
            return false;
        case CUDA_ERROR_UNKNOWN:
            return false;
    }  
    return true; 
}

bool screenCapture::deInitialize(CUcontext cuContext, CUdevice cuDevice)
{
    cuCtxDestroy(cuContext);                           // Destroys the CUDA context
    return true;               
}

