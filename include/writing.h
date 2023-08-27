#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#include "logger.h"

// Find the list of error codes thrown by FreeType functions in fterrdef.h

namespace Writing
{ 
        bool IntializeFT(FT_Library library);
        bool RetrieveFont(FT_Library library, FT_Face face~);
        bool TestFTAlive(FT_Library library);
}
