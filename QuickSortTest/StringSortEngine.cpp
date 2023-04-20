#pragma once
#include "StringSortEngine.h"
#include <MainWindow.cpp>
#include "MainCoorLinLayout.cpp"

StringSortEngine::StringSortEngine() :
    AbstractAppData(NULL, "..\\TESTWIN32_GRAPHICAPP\\x64\\Debug") 
{
    setAppName("Точные коэффициенты быстрой сортировки");
};

void StringSortEngine::onCreate(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
    MainWindow* mainWnd = new MainWindow(this);
    setMainManager(mainWnd);

    MainCoorLinLayout* mainLayout = new MainCoorLinLayout(this);
    mainWnd->addWindow(mainLayout);
    
}