#pragma once
#include "FindCoeff.h"
#include <float.h>
#include <Q_Vector.h>
#include <TXLib.h>

double maxQuadraticDelta = DBL_MIN;
void findBestCoeff(coordinatSys& deltaSys, double* k, double* b, Vector& kBound, Vector& bBound, Vector& xBound, double(*fnc)(double k, double b, double x), double (*originalFnc)(double x))
{
    deltaSys.clean();

    double minQuadraticDelta = DBL_MAX;
    int detalisationK = 1000;
    int kDelta = abs(kBound.delta()) * detalisationK;
    double kStart = kBound.x * detalisationK;

    int bDelta = abs(bBound.delta()) * detalisationK;
    double bStart = bBound.x * detalisationK;

    for (int i = 0; i < 100000; i++)
    {
        double currQuadraticDelta = 0;
        double _k = ((rand() % kDelta) + kStart) / detalisationK;
        double _b = ((rand() % bDelta) + bStart) / detalisationK;

        double xDelta = abs (xBound.delta() / 100);
        for (double x = xBound.x; x < xBound.y; x += xDelta)
        {
            double quadraticDelta = calcQuadratic(_k, _b, x, fnc, originalFnc);
            currQuadraticDelta += quadraticDelta;
        }

        if (isBigger(minQuadraticDelta, currQuadraticDelta))
        {
            minQuadraticDelta = currQuadraticDelta;
            *k = _k;
            *b = _b;
        }
        if (isBigger(currQuadraticDelta, maxQuadraticDelta))
        {
            maxQuadraticDelta = currQuadraticDelta;
        }

        //printf("currQuadraticDelta: %lf | k: %lf, b: %lf\n", currQuadraticDelta, _k, _b);
        COLORREF quadraticDeltaColor = getQuadraticDeltaColor(currQuadraticDelta);
        txSetColor(quadraticDeltaColor);
        txSetFillColor(quadraticDeltaColor);
        Vector point = { _k, _b};
        deltaSys.drawCircle(point, 2);
    }
    

}
//x0 + (x1 - x0) * t
COLORREF getQuadraticDeltaColor(double quadraticDelta)
{
    const double maxQuadraticDelta = 204;
    const double minQuadraticDelta = 0.03;
    const double rangeDelta = maxQuadraticDelta - minQuadraticDelta;
    const int r0 = 0;
    const int r1 = 255;

    const int g0 = 0;
    const int g1 = 0;

    const int b0 = 255;
    const int b1 = 0;

    double t = (quadraticDelta - minQuadraticDelta) / rangeDelta;

    int r2 = r0 + (r1 - r0) * t;
    int g2 = 0;
    int b2 = b0 + (b1 - b0) * t;

    
    COLORREF answer = RGB(r2, g2, b2);
    return answer;
}

double calcQuadratic(double k, double b, double x, double(*fnc)(double k, double b, double x), double (*originalFnc)(double x))
{
    double dy = fnc(k, b, x) - originalFnc(x);
    return (dy * dy);
}



void drawBestCoeff(coordinatSys& sys, double k, double b, Vector& xBound, double(*fnc)(double k, double b, double x), COLORREF color)
{
    double xDelta = abs(xBound.delta() / 1000);
    Vector point = {};
    txSetColor(color);
    txSetFillColor(color);
    for (double x = xBound.x; x < xBound.y; x += xDelta)
    {
        point.x = x;
        point.y = fnc(k, b, x);
        sys.drawCircle(point, 2);
    }

}

void findAndDrawBestCoeff(coordinatSys& sys, coordinatSys& deltaSys, double(*fnc)(double k, double b, double x), double (*originalFnc)(double x), double* findedK, double* findedB, Vector& kBound, Vector& bBound, Vector& xBound, COLORREF color)
{
    findBestCoeff(deltaSys, findedK, findedB, kBound, bBound, xBound, fnc, originalFnc);
    drawBestCoeff(sys, *findedK, *findedB, xBound, fnc, color);
}