#pragma once

#include <windows.h>
#include <nvEncodeAPI.h>

namespace loadLibrary
{
    class Nvidia
    {
        public:
            Nvidia(LPCWSTR libraryName);
            ~Nvidia();
    };
}