#include "writing.h"

using namespace Writing;
// Start of Writing namespace defining

bool Intialize()
{
    if (FT_Init_FreeType(&library) != FT_Err_Ok)
    {
        Logger::getInstance().log_e("FAILED TO INTIIALIZE FREETYPE LIBRARY");
        return false;
    }

    return true;
}

