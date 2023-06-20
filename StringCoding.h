#pragma once

#pragma once

#include <string>
#include <fstream>

wchar_t* readStr(std::string& str);

template <typename TSTR>
void _saveString(const TSTR& str, std::ofstream& stream);

void saveString(const std::wstring& str, std::ofstream& stream);
void saveString(const std::wstring_view str, std::ofstream& stream);

void useNormalWideLocale();
