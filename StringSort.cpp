// StringSort.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "WStringFnc.cpp"
#include "OneginUnitTest/CompareFiles.cpp"

int main()
{
    useNormalLocale();

    workWithText(L"ONEGIN.txt", L"3Text.txt");

    compareFiles(L"3Text.txt", L"OriginalResult.txt");
}
