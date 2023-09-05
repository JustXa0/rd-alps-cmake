#pragma once

#include <iostream>

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN
// Windows Header Files
#include <Windows.h>
// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <io.h>
#include <fcntl.h>

#include <nvEncodeAPI.h>
#include "logger.h"
#include "deviceDetection.h"
#include "encoding.h"