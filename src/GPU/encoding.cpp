#include "encoding.h"

// Start of Encoder class defining

Encoder::Encoder()
{
    device = 0;
    context = NULL;

    loader.loadLibrary(L"nvEncodeAPI64.dll");
    loader.GetLibrary(&hLibrary);

    encodeParams = {};

    encodeParams.version = NV_ENCODE_API_FUNCTION_LIST_VER;
    encodeParams.reserved = 0;
    encodeParams.apiVersion = NVENCAPI_VERSION;

    if(GPU::CreateCudaContext(device, context))
    {
        encodeParams.device = context;
        encodeParams.deviceType = NV_ENC_DEVICE_TYPE_CUDA;
        Encoder::InitializeNVEncoder(context);
    }
    
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
    typedef NVENCSTATUS(NVENCAPI *PFN_NVENC_CREATE_INSTANCE)(NV_ENCODE_API_FUNCTION_LIST*);  // Function pointer type
    typedef NVENCSTATUS(NVENCAPI *PFN_NVENC_OPEN_ENCODE_SESSION_EX)(NV_ENC_OPEN_ENCODE_SESSION_EX_PARAMS*, void**);
    typedef NVENCSTATUS(NVENCAPI *PFN_NVENCDESTROYENCODER)(void*);
   
    PFN_NVENC_CREATE_INSTANCE NvEncodeAPICreateInstance = (PFN_NVENC_CREATE_INSTANCE)GetProcAddress(hLibrary, "NvEncodeAPICreateInstance");
    PFN_NVENC_OPEN_ENCODE_SESSION_EX NvEncOpenEncodeSessionEx = (PFN_NVENC_OPEN_ENCODE_SESSION_EX)GetProcAddress(hLibrary, "NvEncOpenEncodeSessionEx");
    PFN_NVENCDESTROYENCODER NvEncDestroyEncoder = (PFN_NVENCDESTROYENCODER)GetProcAddress(hLibrary, "NvEncDestroyEncoder");

    if (NvEncodeAPICreateInstance == NULL) {
        Logger::getInstance().log_e("ERROR GETTING NvEncodeAPICreateInstance FUNCTION");
        FreeLibrary(hLibrary);
        return false;
    }

   if (NvEncodeAPICreateInstance(&functionList) != NV_ENC_SUCCESS) {
       Logger::getInstance().log_e("ERROR CREATING NVENCODEAPI INSTANCE");
       loader.~Loader();
       return false;
   }

    if (functionList.nvEncOpenEncodeSessionEx(&encodeParams, &encodePointer) != NV_ENC_SUCCESS)
    {
        Logger::getInstance().log_e("ERROR OPENING ENCODE SESSION");
        functionList.nvEncDestroyEncoder(encodePointer);
        loader.~Loader();
        return false;
    }
   
    // Initialization was successful, ending the function
    Logger::getInstance().log_i("NVEncoder initialized, starting tuning selection");
    
    uint32_t encodeProfileGUIDCount;
    if (functionList.nvEncGetEncodeGUIDCount(encodePointer, &encodeProfileGUIDCount) != NV_ENC_SUCCESS)
    {
        Logger::getInstance().log_e("ERROR GETTING ENCODE GUID COUNT");
        functionList.nvEncDestroyEncoder(encodePointer);
        loader.~Loader();
        return false;
    }

    GUID* guidArray = new GUID[encodeProfileGUIDCount];
    if (functionList.nvEncGetEncodeGUIDs(encodePointer, guidArray, encodeProfileGUIDCount, NULL) != NV_ENC_SUCCESS)
    {
        Logger::getInstance().log_e("ERROR GETTING ENCODE GUIDS");
        functionList.nvEncDestroyEncoder(encodePointer);
        loader.~Loader();
        return false;
    }
}