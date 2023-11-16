#pragma once
#include <LinearLayout.cpp>
#include <MultiLayCoordinatSystemWindow.cpp>
#include <TextView.cpp>


struct MainCoorLinLayout : LinearLayout
{
    const int maxArrLen = 150;
    const int topWndScale = 150;
    const int bottomWndScale = 50;
    MultiLayCoordinatSystemWindow topWnd;
    MultiLayCoordinatSystemWindow bottomWnd;
    size_t sortDataIndex = 0;
    size_t linOddsLayIndex = 1;
    size_t logOddsLayIndex = 2;
    COLORREF sortDataColor = C_LIGHTCYAN;
    COLORREF gradientLogColor = C_YELLOW;
    COLORREF gradientLinColor = C_LIGHTRED;
    
    Vector logLearningRate = {1e-11, 1e-11};
    Vector linLearningRate = {1e-9, 1e-9};

    Vector topGradientLogOdds = { 1, 2 };// k = x, b = y
    Vector topGradientLinOdds = { 1, 2 };// k = x, b = y
    Vector bottomGradientLogOdds = { 1, 2 };// k = x, b = y
    Vector bottomGradientLinOdds = { 1, 2 };// k = x, b = y

    bool isActiveComputingPart = true;
    const int updateFrequency = 5000;
    UINT_PTR activeTimer = 0;

    LinearLayout topFncCmpLayout;
    TextView topHandle;
    TextView topLogFnc;
    TextView topLinFnc;

    LinearLayout bottomFncCmpLayout;
    TextView bottomHandle;
    TextView bottomLogFnc;
    TextView bottomLinFnc;

    LinearLayout graficInfoLayout;
    TextView sortDataText;
    TextView logDataText;
    TextView linDataText;

    TextView computionStatusText;

    MainCoorLinLayout(AbstractAppData* _app);

    string logOddsToString(Vector _odd);
    string linOddsToString(Vector _odd);

    void initCoorSys();
    void initDescribtions();
    void initColorDescribtions();
    void onPartDescribtion(LinearLayout& _layout, TextView& handle, TextView& _logFnc, TextView& _linFnc);
    void gradientDescentOddsComputation();

    void startComputations();
    void makeSortDataPoints();
    void monteCarlo(Vector& _odds, MultiLayCoordinatSystemWindow& _wnd, double (*fnc) (double k, double b, double x));
    void randomArrFill(int* arr, int len);

    double gradientDescent(Vector& _odds, MultiLayCoordinatSystemWindow& _wnd, double (*fnc) (double k, double b, double x), Vector learningRate);
    void drawGradientOdds(Vector _odds, MultiLayCoordinatSystemWindow& wnd, double (*fnc) (double k, double b, double x), COLORREF graficColor, size_t layIndex);
    double computeQuadraticDelta(double k, double b, MultiLayCoordinatSystemWindow& wnd, double (*fnc) (double k, double b, double x));
    static double logfnc(double k, double b, double x);//k * log(bx)
    static double linfnc(double k, double b, double x);//kx + b

    virtual int onSize(Vector _managerSize, Rect _newRect) override;
    virtual int onTimer(UINT_PTR timerName) override;
};
