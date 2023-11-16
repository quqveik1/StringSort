#pragma once
#include "StringSortEngine.h"
#include <MainWindow.cpp>
#include "MainCoorLinLayout.cpp"
#include "resource.h"

StringSortEngine::StringSortEngine() :
    AbstractAppData(NULL, "..\\TESTWIN32_GRAPHICAPP\\x64\\Release") 
{
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

    getStringResources().addResource(StringResources::Russian, "name", "Точные коэффициенты быстрой сортировки");
    getStringResources().addResource(StringResources::English, "name", "The accurate coefficients for quicksort.");
    std::string title = setAppInfoToString(getStringResources().getResource("name"));
    setAppName(title);
}
