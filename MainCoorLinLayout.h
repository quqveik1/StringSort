#pragma once
#include <LinearLayout.cpp>
#include <MultiLayCoordinatSystemWindow.cpp>

struct MainCoorLinLayout : LinearLayout
{
    const int maxArrLen = 5000;
    MultiLayCoordinatSystemWindow topWnd;
    MultiLayCoordinatSystemWindow bottomWnd;
    size_t sortDataIndex = 0;
    size_t logIndex = 1;
    size_t suggestedOddsIndex = 2;
    COLORREF sortDataColor = C_BLUE;
    COLORREF logColor = C_LIGHTRED;
    COLORREF gradientLogColor = C_LIGHTGREEN;
    
    Vector gradientOdds = { 1, 2 };// k = x, b = y


    bool isActiveComputingPart = true;
    const int updateFrequency = 5000;
    UINT_PTR activeTimer = 0;

    MainCoorLinLayout(AbstractAppData* _app);

    void startComputations();
    void randomArrFill(int* arr, int len);

    void gradientDescent();
    void drawGradientOdds();
    double countQuadraticDelta(double k, double b);
    double logfnc(double k, double b, double x);//k * log(bx)

    virtual int onSize(Vector _managerSize, Rect _newRect) override;
    virtual int onTimer(UINT_PTR timerName) override;
};