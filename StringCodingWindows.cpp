#pragma once

#include "StringCoding.h"

#include <windows.h>
#undef min
#undef max

wchar_t* readStr(std::string& str)
{
    int required_size = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
    wchar_t* buffer = new wchar_t[required_size] {};
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &buffer[0], required_size);

    return buffer;
}


template <typename TSTR>
void _saveString(const TSTR& str, std::ofstream& stream)
{
    if (str.size() == 0) return;

    int required_size = WideCharToMultiByte(CP_UTF8, 0, str.data(), (int)str.size(), 0, 0, 0, 0);
    if (required_size > 0)
    {
        std::vector<char> buffer(required_size);
        WideCharToMultiByte(CP_UTF8, 0, str.data(), (int)str.size(), &buffer[0], required_size, 0, 0);

        for (int i = 0; i < required_size; i++)
        {
            stream.put(buffer[i]);
        }
    }
    else
    {
        throw std::runtime_error("Ошибка конвертации");
    }
}

void saveString(const std::wstring& str, std::ofstream& stream)
{
    _saveString(str, stream);
}

void saveString(const std::wstring_view str, std::ofstream& stream)
{
    _saveString(str, stream);
}

void useNormalWideLocale()
{
    std::setlocale(LC_ALL, "ru_RU.utf8");
}

void useNormalLocale()
{
    std::setlocale(LC_ALL, "russian");
}

