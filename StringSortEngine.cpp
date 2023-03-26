#pragma once
#include "StringSortEngine.h"
#include <MainWindow.cpp>

void StringSortEngine::onCreate(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
    MainWindow* mainWnd = new MainWindow(this);
    setMainManager(mainWnd);
}