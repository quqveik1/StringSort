#pragma once

#if defined(_WIN32)
#include "StringCodingWindows.h"
#elif defined(__APPLE__) || defined(__MACH__)
#include "StringCodingMac.h"
#endif
