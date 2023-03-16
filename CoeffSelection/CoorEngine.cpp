#pragma once
#include "CoorEngine.h"
#include <AbstractApp.cpp>
#include <MainWindow.cpp>
#include <LinearLayout.cpp>
#include "CoordinatSystemWindow.cpp"
#include "MainLinLayout.cpp"
#include "ColorfullCoordinatSystemWindow.cpp"

void CoorEngine::onCreate(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
    MainWindow* mainWnd = new MainWindow(this);
    setMainManager(mainWnd);
                                                                                  
    MainLinLayout* mainLayout = new MainLinLayout(this, {});
    mainLayout->setMatchParent(true);
    mainWnd->addWindow(mainLayout);
}


void CoorEngine::setWindowParameters(HINSTANCE hInstance)
{
    AbstractAppData::setWindowParameters(hInstance);
}