#pragma once
#include "FindCoeff.h"
#include <float.h>
#include <Q_Vector.h>
#include <TXLib.h>


void findBestCoeff(double* k, double* b, Vector& kBound, Vector& bBound, Vector& xBound, double(*fnc)(double k, double b, double x), double (*originalFnc)(double x))
{
    double minQuadraticDelta = DBL_MAX;
    int detalisationK = 10;
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

    }

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

void findAndDrawBestCoeff(coordinatSys& sys, double(*fnc)(double k, double b, double x), double (*originalFnc)(double x), double* findedK, double* findedB, Vector& kBound, Vector& bBound, Vector& xBound, COLORREF color)
{
    findBestCoeff(findedK, findedB, kBound, bBound, xBound, fnc, originalFnc);
    drawBestCoeff(sys, *findedK, *findedB, xBound, fnc, color);
}