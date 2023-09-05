#pragma once

#include <windows.h>
#include <nvEncodeAPI.h>

#include "logger.h"

class Loader
{

    public:
        Loader();
        ~Loader();

        bool loadLibrary(LPCWSTR libraryName);
        bool GetLibrary(HMODULE* libraryOut);
    
    private:
        HMODULE hLibrary;
};