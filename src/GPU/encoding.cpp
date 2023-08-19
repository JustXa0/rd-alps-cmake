#include "encoding.h"

Encoder::Encoder()
{
// Define the function pointer type based on the function signature
typedef NVENCSTATUS(NVENCAPI *NvEncDestroyEncoderPtr)(NV_ENCODE_API_FUNCTION_LIST*);

// Load the nvEncodeAPI.dll library and retrieve function pointers
HMODULE hLibrary = LoadLibrary("nvEncodeAPI.dll");
if (hLibrary != nullptr) {
    // Retrieve the function pointer using the correct name (mangled)
    NvEncDestroyEncoderPtr nvEncDestroyEncoder = reinterpret_cast<NvEncDestroyEncoderPtr>(
        GetProcAddress(hLibrary, "NvEncodeAPIDestroyInstance"));  // Correct mangled name
    
    if (nvEncDestroyEncoder != nullptr) {
        // Successfully loaded function pointer, you can use it now
        NV_ENCODE_API_FUNCTION_LIST functionList;  // Create an instance of the struct
        NVENCSTATUS destroyStatus = nvEncDestroyEncoder(&functionList);
        // Handle destroyStatus here
    } else {
        // Error handling
    }
    
    // Don't forget to free the library when you're done
    FreeLibrary(hLibrary);
} else {
    // Error handling
}


}

Encoder::~Encoder()
{
    //Release();
    cudaDeviceReset();
}

bool Encoder::createCudaContext()
{
   result = cuInit(0);
   if (result != CUDA_SUCCESS)
   {
        // TODO: Handle error here
        return false;
   }

   int deviceCount = 0;
   result = cuDeviceGetCount(&deviceCount);
   if (result != CUDA_SUCCESS)
   {
        // TODO: Handle error here
        return false;
   }

   if (deviceCount == 0)
   {
        // no devices found
        return false;
   }

   device = 0;
   result = cuDeviceGet(&device, 0);
   if (result != CUDA_SUCCESS)
   {
        // TODO: Handle error here
        return false;
   }

   context = NULL;
   result = cuCtxCreate(&context, 0, device);
   if (result != CUDA_SUCCESS)
   {
        // TODO: Handle error here
        return false;
   }
   
   return true;
}

