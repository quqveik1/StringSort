#pragma once
#include <AbstractApp.h>


struct CoorEngine : AbstractAppData
{
    CoorEngine() : AbstractAppData(NULL) {};

    virtual void onCreate(HWND window, UINT message, WPARAM wParam, LPARAM lParam) override;
    virtual void setWindowParameters(HINSTANCE hInstance)  override;
};
