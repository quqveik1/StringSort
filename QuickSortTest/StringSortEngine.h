#pragma once
#include <AbstractApp.cpp>

struct StringSortEngine : AbstractAppData
{
    StringSortEngine();

    virtual void onCreate(HWND window, UINT message, WPARAM wParam, LPARAM lParam) override;
};