#pragma once
#include <LinearLayout.h>
#include "CoordinatSystemWindow.h"
#include "ColorfullCoordinatSystemWindow.h"
#include <TextView.cpp>


struct MainLinLayout : LinearLayout
{
    ColorfullCoordinatSystemWindow* topSystem = NULL;
    ColorfullCoordinatSystemWindow* bottomSystem = NULL;
    COLORREF suggestedFncColor = C_LIGHTRED;
    COLORREF userSelectedFncColor = C_GREEN;
    Vector downLineSize = {};

    LinearLayout downLinLayout;
    TextView backGroundComputation;
    TextView suggestedCoeff;
    TextView answerCoeff;
    
    

    static double currOriginalK;
    static double currOriginalB;

    int cCountingCoef = 100000;
    int cQuadraticDeltaCountingPoints = 100;

    double answerK = 0;
    double answerB = 0;
    bool wasAnswerFinded = false;

    M_HDC onWindowMovingCopyDC;

    MainLinLayout(AbstractAppData* _app, Vector _startPos);

    void setTopSystem(ColorfullCoordinatSystemWindow* _wnd) { topSystem = _wnd; };
    void setBottomSystem(ColorfullCoordinatSystemWindow* _wnd) { bottomSystem = _wnd; };

    static double originalSinFnc(double x);
    static double sinFnc(double k, double b, double x);

    double calcQuadratic(double k, double b, double x, double(*fnc)(double k, double b, double x), double (*originalFnc)(double x));
    COLORREF getQuadraticDeltaColor(double quadraticDelta);

    void threadCoeffFinder(double* k, double* b, Vector& kBound, Vector& bBound, double(*fnc)(double k, double b, double x), double (*originalFnc)(double x));
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