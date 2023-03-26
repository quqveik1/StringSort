#pragma once
#include <LinearLayout.h>
#include "CoordinatSystemWindow.h"
#include "ColorfullCoordinatSystemWindow.h"
#include <TextView.cpp>
#include "GraphicInfoButton.cpp"
#include "CustomRCoordinatSystemWindow.h"


struct MainLinLayout : LinearLayout
{
    ColorfullCoordinatSystemWindow topSystem = NULL;
    CustomRCoordinatSystemWindow bottomSystem = NULL;
    COLORREF suggestedFncColor = C_LIGHTRED;
    COLORREF userSelectedFncColor = C_GREEN;
    Vector downLineSize = {};
    int maxMinDeltaR = 10;
    COLORREF minDeltaColor = C_LIGHTRED;
    COLORREF maxDeltaColor = C_BLUE;

    LinearLayout topDescribtions;
    TextView topDescribtion1;
    TextView topDescribtion2;
    TextView topDescribtion3;
    LinearLayout bottomDescribtions;
    TextView bottomDescribtion1;
    TextView bottomDescribtion2;

    LinearLayout downLinLayout;
    TextView backGroundComputation;
    TextView suggestedCoeff;
    TextView answerCoeff;
    GraphicInfoButton graphicInfoButton;

    static double currOriginalK;
    static double currOriginalB;

    int cCountingCoef = 100000;
    int cQuadraticDeltaCountingPoints = 100;

    double answerK = 0;
    double answerB = 0;
    bool wasAnswerFinded = false;

    mutex  maxQuadraticDeltaMutex;
    double maxQuadraticDelta = DBL_MIN;
    int    maxQuadraticDeltaIndex = -1;

    mutex  minQuadraticDeltaMutex;
    double minQuadraticDelta = DBL_MAX;
    int    minQuadraticDeltaIndex = -1;

    M_HDC onWindowMovingCopyDC;

    MainLinLayout(AbstractAppData* _app, Vector _startPos);

    //void setTopSystem(ColorfullCoordinatSystemWindow* _wnd) { topSystem = _wnd; };
    //void setBottomSystem(ColorfullCoordinatSystemWindow* _wnd) { bottomSystem = _wnd; };

    void initCoordinats();
    void initDescribtions();
    void initDownLinLayout();

    static double originalSinFnc(double x);
    static double sinFnc(double k, double b, double x);

    double calcQuadratic(double k, double b, double x, double(*fnc)(double k, double b, double x), double (*originalFnc)(double x));
    double calcTotalQuadratic(double k, double b, double(*fnc)(double k, double b, double x), double (*originalFnc)(double x), double start, double finish, double step);
    double calcAndPrintTotalQuadratic(double k, double b, double(*fnc)(double k, double b, double x), double (*originalFnc)(double x), double start, double finish, double step);

    COLORREF getQuadraticDeltaColor(double quadraticDelta);

    void threadCoeffFinder(double* k, double* b, Vector& kBound, Vector& bBound, double(*fnc)(double k, double b, double x), double (*originalFnc)(double x));
    void changeAndPrintNewMaxOrMinDelta(double* curminMaxDelta, double currDelta, int* currIndex, COLORREF color);
    void startGradientComputation();
    void countGradientMap();
    void countOriginalFnc();
    void countFncOnTopSystem(double k, double b, COLORREF _color = NULL);
    void onCertainPointSelection(Vector clickedCellP);

    virtual void onMessageRecieve(const char* name, void* data) override;

    virtual void draw() override;
    virtual int onEnterWindowSizeMove() override;
    virtual int onExitWindowSizeMove() override;
    virtual int onSize(Vector managerSize, Rect _newRect) override;
};