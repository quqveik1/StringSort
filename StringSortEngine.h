#pragma once
#include <AbstractApp.cpp>

struct StringSortEngine : AbstractAppData
{
    StringSortEngine() : AbstractAppData(NULL, "..\\TESTWIN32_GRAPHICAPP\\x64\\Debug") {};

    virtual void onCreate(HWND window, UINT message, WPARAM wParam, LPARAM lParam) override;
};