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
    

    ColorfullCoordinatSystemWindow* topCoordinatSystemWindow = new ColorfullCoordinatSystemWindow(this);
    topCoordinatSystemWindow->setCCells({ 20, 20 });
    topCoordinatSystemWindow->pixNullPercantage = { 0.5, 0.5 };
    topCoordinatSystemWindow->onSize({}, {0, 0, 50, 500});

    mainLayout->setTopSystem(topCoordinatSystemWindow);
    LinearLayoutInfo* topInfo = new LinearLayoutInfo();
    topInfo->margin = Rect{ 0, 0, 0, 10 };
    topCoordinatSystemWindow->setLayoutInfo(topInfo);

    topCoordinatSystemWindow->setMatchParentX(true); 
    mainLayout->addWindow(topCoordinatSystemWindow);

    ColorfullCoordinatSystemWindow* bottomCoordinatSystemWindow = new ColorfullCoordinatSystemWindow(this);
    bottomCoordinatSystemWindow->setCellNull({0, 6.8});
    bottomCoordinatSystemWindow->setCCells({ 12, 0.5 });
    bottomCoordinatSystemWindow->onSize({}, {0, 0, 50, 500});
    bottomCoordinatSystemWindow->setMatchParentX(true);
    bottomCoordinatSystemWindow->setOnClickListener(mainLayout);
    mainLayout->setBottomSystem(bottomCoordinatSystemWindow);
    mainLayout->addWindow(bottomCoordinatSystemWindow);
    mainLayout->startGradientComputation();


}


void CoorEngine::setWindowParameters(HINSTANCE hInstance)
{
    AbstractAppData::setWindowParameters(hInstance);
}