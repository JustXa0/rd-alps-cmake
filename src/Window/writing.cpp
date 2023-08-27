#include "writing.h"

using namespace Writing;
// Start of Writing namespace defining

bool Writing::IntializeFT(FT_Library library)
{
    if (FT_Init_FreeType(&library) != FT_Err_Ok)
    {
        Logger::getInstance().log_e("FAILED TO INTIIALIZE FREETYPE LIBRARY");
        return false;
    }

    return true;
}

bool Writing::RetrieveFont(FT_Library library, FT_Face face)
{
    if (TestFTAlive(library))
    {
        FT_Error error = FT_New_Face(library, "C:/Windows/Fonts/Segoe UI Semilight.otf", 0, &face);
    }

    return false;
}

bool Writing::TestFTAlive(FT_Library library)
{
    if (library == NULL)
    {
        Logger::getInstance().log_e("FAILED TO FIND HANDLE OF FREETYPE LIBRARY");
        Logger::getInstance().log_e("TRY CALLING 'Writing::Initalize' BEFORE USING ANY OTHER FUNCTIONS");
        return false;
    }

    return true;
}

