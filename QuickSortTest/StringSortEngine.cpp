#pragma once
#include "StringSortEngine.h"
#include <MainWindow.cpp>
#include "MainCoorLinLayout.cpp"
#include "resource.h"

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

void StringSortEngine::setWindowParameters(HINSTANCE hInstance)
{
    AbstractAppData::setWindowParameters(hInstance);
    loadAndSetIcon(IDI_ICON1);
}