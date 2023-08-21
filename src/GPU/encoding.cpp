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

/**
 * Initializes the NVENC encoder.
 *
 * @param contextIn the CUDA context to be used by the encoder
 *
 * @return true if the encoder is successfully initialized, false otherwise
 *
 * @throws ErrorType if there is an error loading the nvEncodeAPI.dll, getting the NvEncodeAPICreateInstance function, creating the NVENCODEAPI instance, or during the rest of the initialization process
 */
bool Encoder::InitializeNVEncoder(CUcontext contextIn)
{
   HMODULE hLibrary = LoadLibrary("nvEncodeAPI.dll");
   
   if (hLibrary == NULL) {
       Logger::getInstance().log_e("ERROR LOADING nvEncodeAPI.dll");
       return false;
   }
   
   typedef NVENCSTATUS(__cdecl *PFN_NVENC_CREATE_INSTANCE)(NV_ENCODE_API_FUNCTION_LIST*);  // Function pointer type
   
   PFN_NVENC_CREATE_INSTANCE NvEncodeAPICreateInstance = (PFN_NVENC_CREATE_INSTANCE)GetProcAddress(hLibrary, "NvEncodeAPICreateInstance");
   
   if (NvEncodeAPICreateInstance == NULL) {
       Logger::getInstance().log_e("ERROR GETTING NvEncodeAPICreateInstance FUNCTION");
       FreeLibrary(hLibrary);
       return false;
   }
   
   NV_ENCODE_API_FUNCTION_LIST functionList;
   if (NvEncodeAPICreateInstance(&functionList) != NV_ENC_SUCCESS) {
       Logger::getInstance().log_e("ERROR CREATING NVENCODEAPI INSTANCE");
       FreeLibrary(hLibrary);
       return false;
   }
   
   // ... Continue with the rest of the code using the functionList and other variables
   
   // Cleanup
   FreeLibrary(hLibrary);
   
   return true;
   
}
   