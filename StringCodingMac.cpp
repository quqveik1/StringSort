#pragma once

#include "StringCoding.h"

#include <exception>

wchar_t* readStr(std::string& str)
{
    size_t len = mbstowcs(nullptr, str.c_str(), 0);
    wchar_t* buffer = new wchar_t[len];
    mbstowcs(buffer, str.c_str(), len);

    return buffer;
}

template <typename TSTR>
void _saveString(const TSTR& str, std::ofstream& stream)
{
    if(str.size() == 0) return;

    size_t required_size = wcstombs(nullptr, str.data(), str.size());

    if (required_size > 0)
    {
        std::vector<char> buffer(required_size);

        wcstombs(buffer.data(), str.data(), required_size);

        for (size_t i = 0; i < required_size; ++i)
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
    std::wstring nullStr = (std::wstring)str;
    _saveString(nullStr, stream);
}

