#pragma once

#include <Windows.h>
#include <iostream>
#include <string>
#include <cstdint>
#include <cassert>
#include <ctime>

#include <nvEncodeAPI.h>
#include <cuda.h>

class screenCapture
{
    private:
        

    public:

        bool initialize(CUcontext cuContext, CUdevice cuDevice);
        bool deInitialize(CUcontext cuContext, CUdevice cuDevice);
};


