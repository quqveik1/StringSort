#pragma once
#include <LinearLayout.h>
#include "CoordinatSystemWindow.h"
#include "ColorfullCoordinatSystemWindow.h"


struct MainLinLayout : LinearLayout
{
    ColorfullCoordinatSystemWindow* topSystem = NULL;
    ColorfullCoordinatSystemWindow* bottomSystem = NULL;
    COLORREF suggestedFncColor = C_LIGHTRED;

    static double currOriginalK;
    static double currOriginalB;

    double answerK = 0;
    double answerB = 0;

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

    virtual void draw() override;
    virtual int onEnterWindowSizeMove() override;
    virtual int onExitWindowSizeMove() override;
    virtual int onSize(Vector managerSize, Rect _newRect) override;
};