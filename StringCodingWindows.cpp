#pragma once

#include "StringCodingWindows.h"

#include <windows.h>


void saveString(const std::wstring_view& str, std::ofstream& stream)
{
    static std::string byteString;
    int required_size = WideCharToMultiByte(CP_UTF8, 0, str.data(), (int)str.size(), 0, 0, 0, 0);
    if (required_size > 0)
    {
        std::vector<char> buffer(required_size);
        WideCharToMultiByte(CP_UTF8, 0, str.data(), (int)str.size(), &buffer[0], required_size, 0, 0);
        byteString = std::string(buffer.begin(), buffer.end() - 1);

        stream << byteString;
    }
}

void saveString(const std::wstring& str, std::ofstream& stream)
{
    static std::string byteString;
    int required_size = WideCharToMultiByte(CP_UTF8, 0, str.data(), (int)str.size() + 1, 0, 0, 0, 0);
    if (required_size > 0)
    {
        std::vector<char> buffer(required_size);
        WideCharToMultiByte(CP_UTF8, 0, str.data(), (int)str.size() + 1, &buffer[0], required_size, 0, 0);
        byteString = std::string(buffer.begin(), buffer.end() - 1);

        stream << byteString;
    }
}
