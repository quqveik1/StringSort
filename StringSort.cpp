// StringSort.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "WStringFnc.cpp"
#include "OneginUnitTest/CompareFiles.cpp"

int main()
{
    std::locale::global(std::locale(""));
    setlocale(LC_ALL, "russian");

    workWithText(L"ONEGIN.txt", L"3Text.txt");

    compareFiles(L"3Text.txt", L"OriginalResult.txt");
}
