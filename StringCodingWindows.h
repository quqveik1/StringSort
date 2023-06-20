#pragma once

#include <string>
#include <fstream>

void saveString(const std::wstring_view& str, std::ofstream& stream);
void saveString(const std::wstring& str, std::ofstream& stream);
