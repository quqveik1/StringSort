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
    

    CoordinatSystemWindow* topCoordinatSystemWindow = new CoordinatSystemWindow(this);
    topCoordinatSystemWindow->setCCells({ 20, 20 });
    topCoordinatSystemWindow->onSize({}, {0, 0, 50, 500});

    mainLayout->setTopSystem(topCoordinatSystemWindow);
    LinearLayoutInfo* topInfo = new LinearLayoutInfo();
    topInfo->margin = Rect{ 0, 0, 0, 10 };
    topCoordinatSystemWindow->setLayoutInfo(topInfo);

    topCoordinatSystemWindow->setMatchParentX(true); 
    mainLayout->addWindow(topCoordinatSystemWindow);

    ColorfullCoordinatSystemWindow* bottomCoordinatSystemWindow = new ColorfullCoordinatSystemWindow(this);
    bottomCoordinatSystemWindow->setCCells({ 20, 20 });
    bottomCoordinatSystemWindow->onSize({}, {0, 0, 50, 500});
    bottomCoordinatSystemWindow->setMatchParentX(true);
    mainLayout->setBottomSystem(bottomCoordinatSystemWindow);
    mainLayout->addWindow(bottomCoordinatSystemWindow);


    mainLayout->countGradientMap();


}


void CoorEngine::setWindowParameters(HINSTANCE hInstance)
{
    AbstractAppData::setWindowParameters(hInstance);
}