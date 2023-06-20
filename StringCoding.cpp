#pragma once

#include "StringCoding.h"

#if defined(_WIN32)
#include "StringCodingWindows.cpp"
#elif defined(__APPLE__) || defined(__MACH__)
#include "StringCodingMac.cpp"
#endif


