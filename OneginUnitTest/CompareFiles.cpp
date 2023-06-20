﻿#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <string_view>

#include "../WStringFnc.cpp"

void compareFiles(std::wstring fileName1, std::wstring fileName2)
{
    std::wstring_view view1;
    std::wstring_view view2;
    readText(fileName1, &view1);
    readText(fileName2, &view2);

    int compRes = view1.compare(view2);

    if (compRes == 0)
    {
        std::wcout << L"Новый и старый файл совпали\n";
    }
    else
    {
        std::wcout << L"Новый и старый файл не совпали\n";
    }

    delete view1.data();
    delete view2.data();
}