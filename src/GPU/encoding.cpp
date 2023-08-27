#include "encoding.h"

// Start of Encoder class defining

Encoder::Encoder()
{
    device = 0;
    context = NULL;
    encodePointer = nullptr;

    loader.loadLibrary(L"nvEncodeAPI64.dll");
    loader.GetLibrary(&hLibrary);

    if(GPU::CreateCudaContext(device, context))
    {
        Encoder::InitializeNVEncoder(context);
    }
    
}

Encoder:: ~Encoder()
{
    functionList.nvEncDestroyEncoder(encodePointer);
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

   if (contextIn != nullptr)
   {
        encodeParams.version = NV_ENC_OPEN_ENCODE_SESSION_EX_PARAMS_VER;
        encodeParams.deviceType = NV_ENC_DEVICE_TYPE_CUDA;
        encodeParams.device = contextIn;
        encodeParams.apiVersion = NVENCAPI_VERSION;
   }
   else 
   {
       Logger::getInstance().log_e("CUDA CONTEXT IS SET TO NULLPTR");
        return false;
   }

    if (functionList.nvEncOpenEncodeSessionEx(&encodeParams, &encodePointer) != NV_ENC_SUCCESS)
    {
        Logger::getInstance().log_e("ERROR OPENING ENCODE SESSION");
        Logger::getInstance().log_e(functionList.nvEncGetLastErrorString(encodePointer));
        functionList.nvEncDestroyEncoder(encodePointer);
        loader.~Loader();
        return false;
    }
   
    // Initialization was successful, starting tuning selection
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

    for (int i = 0; i < encodeProfileGUIDCount; i++)
{
    // Access the i-th element in the guidArray
    GUID currentGUID = guidArray[i];

    // Perform operations with the currentGUID
    // For example, you can compare it against known GUIDs or convert it to a string representation
    // to further process or display the information

    // Example: Convert the currentGUID to a string representation
    char guidString[39];
    sprintf_s(guidString, sizeof(guidString), "%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
        currentGUID.Data1, currentGUID.Data2, currentGUID.Data3,
        currentGUID.Data4[0], currentGUID.Data4[1], currentGUID.Data4[2], currentGUID.Data4[3],
        currentGUID.Data4[4], currentGUID.Data4[5], currentGUID.Data4[6], currentGUID.Data4[7]);

    // Do something with the guidString, such as printing it to the console
    printf("GUID %d: %s\n", i, guidString);
}

    return true;
}


// TODO: implement DirectX support 
bool Encoder::InitializeNVEncoder()
{
    typedef NVENCSTATUS(NVENCAPI *PFN_NVENC_CREATE_INSTANCE)(NV_ENCODE_API_FUNCTION_LIST*);  // Function pointer type

    PFN_NVENC_CREATE_INSTANCE NvEncodeAPICreateInstance = (PFN_NVENC_CREATE_INSTANCE)GetProcAddress(hLibrary, "NvEncodeAPICreateInstance");

    if (NvEncodeAPICreateInstance == NULL) 
    {
        Logger::getInstance().log_e("ERROR GETTING NvEncodeAPICreateInstance FUNCTION");
        loader.~Loader();
        return false;
    }

    if (NvEncodeAPICreateInstance(&functionList) != NV_ENC_SUCCESS) 
    {
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

    return true;
}