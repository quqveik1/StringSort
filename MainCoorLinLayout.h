#pragma once
#include <LinearLayout.cpp>
#include <MultiLayCoordinatSystemWindow.cpp>
#include <TextView.cpp>

struct MainCoorLinLayout : LinearLayout
{
    const int maxArrLen = 500;
    MultiLayCoordinatSystemWindow topWnd;
    MultiLayCoordinatSystemWindow bottomWnd;
    size_t sortDataIndex = 0;
    size_t logIndex = 1;
    size_t suggestedOddsIndex = 2;
    COLORREF sortDataColor = C_BLUE;
    COLORREF logColor = C_LIGHTRED;
    COLORREF gradientLogColor = C_LIGHTGREEN;
    
    Vector logLearningRate = {1e-10, 1e-10};
    Vector linLearningRate = {1e-8, 1e-8};

    Vector topGradientLogOdds = { 1, 2 };// k = x, b = y
    Vector topGradientLinOdds = { 1, 2 };// k = x, b = y
    Vector bottomGradientOdds = { 1, 2 };// k = x, b = y

    bool isActiveComputingPart = true;
    const int updateFrequency = 5000;
    UINT_PTR activeTimer = 0;

    LinearLayout topFncCmp;
    TextView topHandle;
    TextView topLogFnc;
    TextView topLinFnc;

    TextView bottomOdd;
    

    MainCoorLinLayout(AbstractAppData* _app);

    string oddsToString(Vector _odd);

    void startComputations();
    void randomArrFill(int* arr, int len);

    double gradientDescent(Vector& _odds, MultiLayCoordinatSystemWindow& _wnd, double (*fnc) (double k, double b, double x), Vector learningRate);
    void drawGradientOdds(Vector _odds, MultiLayCoordinatSystemWindow& wnd, double (*fnc) (double k, double b, double x));
    double countQuadraticDelta(double k, double b, MultiLayCoordinatSystemWindow& wnd, double (*fnc) (double k, double b, double x));
    static double logfnc(double k, double b, double x);//k * log(bx)
    static double linfnc(double k, double b, double x);//kx + b

    virtual int onSize(Vector _managerSize, Rect _newRect) override;
    virtual int onTimer(UINT_PTR timerName) override;
};