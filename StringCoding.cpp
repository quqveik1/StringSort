#pragma once

#if defined(_WIN32)
#include "StringCodingWindows.cpp"
#if defined(__APPLE__) || defined(__MACH__)
#include "StringCodingMac.cpp"
#endif


