#pragma once
#include "CoorEngine.h"
#include <AbstractApp.cpp>
#include <MainWindow.cpp>
#include <LinearLayout.cpp>
#include "CoordinatSystemWindow.cpp"

void CoorEngine::onCreate(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
    MainWindow* mainWnd = new MainWindow(this);
    setMainManager(mainWnd);

    LinearLayout* mainLayout = new LinearLayout(this, {}, LinearLayout::FLAG_VERTICAL);
    mainLayout->setMatchParent(true);
    mainWnd->addWindow(mainLayout);
    

    CoordinatSystemWindow* coordinatSystemWindow = new CoordinatSystemWindow(this);
    coordinatSystemWindow->setCCells({ 20, 20 });
    coordinatSystemWindow->onSize({}, {0, 0, 50, 500});
    coordinatSystemWindow->setMatchParentX(true); 
    
    mainLayout->addWindow(coordinatSystemWindow);
}


void CoorEngine::setWindowParameters(HINSTANCE hInstance)
{
    AbstractAppData::setWindowParameters(hInstance);
}