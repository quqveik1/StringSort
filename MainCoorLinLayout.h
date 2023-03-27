#pragma once
#include <LinearLayout.cpp>
#include <CoordinatSystemWindow.cpp>

struct MainCoorLinLayout : LinearLayout
{
    const int maxArrLen = 10000;
    CoordinatSystemWindow topWnd;
    CoordinatSystemWindow bottomWnd;
    const int updateFrequency = 1000;
    UINT_PTR activeTimer = 0;

    MainCoorLinLayout(AbstractAppData* _app);

    void startComputations();
    void randomArrFill(int* arr, int len);

    virtual int onSize(Vector _managerSize, Rect _newRect) override;
    virtual int onTimer(UINT_PTR timerName) override;
};