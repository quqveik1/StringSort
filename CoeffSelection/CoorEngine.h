#pragma once
#include <AbstractApp.h>


struct CoorEngine : AbstractAppData
{
    CoorEngine() : AbstractAppData(NULL, "..\\..\\TESTWIN32_GRAPHICAPP\\x64\\Debug") {};

    virtual void onCreate(HWND window, UINT message, WPARAM wParam, LPARAM lParam) override;
    virtual void setWindowParameters(HINSTANCE hInstance)  override;
};
