#pragma once
#include "MainLinLayout.h"
#include <thread>
#include <LinearLayout.cpp>


double MainLinLayout::currOriginalK = 5;
double MainLinLayout::currOriginalB = 7;

MainLinLayout::MainLinLayout(AbstractAppData* _app, Vector _startPos) :
    LinearLayout(_app, _startPos, LinearLayout::FLAG_VERTICAL)
{
    currOriginalK = 5;
    currOriginalK = 7;
}

int MainLinLayout::onSize(Vector managerSize, Rect _newRect)
{
    int res = LinearLayout::onSize(managerSize, _newRect);
    Vector _size = getSize();
    if (topSystem)
    {
        topSystem->onSize(_size, { 0, 0, topSystem->getSize().x, _size.y * 0.5 });
    }

    if (bottomSystem)
    {
        bottomSystem->onSize(_size, { 0, 0, bottomSystem->getSize().x, _size.y * 0.5 });
    }

    return LinearLayout::onSize(managerSize, _newRect);
}

double MainLinLayout::originalSinFnc(double x)
{
    return sinFnc(currOriginalK, currOriginalB, x);
}

double MainLinLayout::sinFnc(double k, double b, double x)
{
    /// k - A, B - f(частота)
    return k * sin(b * x);
}

void MainLinLayout::threadCoeffFinder(double* k, double* b, Vector& kBound, Vector& bBound, double(*fnc)(double k, double b, double x), double (*originalFnc)(double x))
{
    if (bottomSystem) bottomSystem->clearSys();
    if (topSystem) topSystem->clearSys();

    double minQuadraticDelta = DBL_MAX;
    int detalisationK = 1000;
    int kDelta = abs(kBound.delta()) * detalisationK;
    double kStart = kBound.x * detalisationK;

    int bDelta = abs(bBound.delta()) * detalisationK;
    double bStart = bBound.x * detalisationK;

    Vector topCellXBound = topSystem->getXCellBound();
    double topCellXBoundLen = topCellXBound.delta();

    for (int i = 0; i < 100000; i++)
    {
        double currQuadraticDelta = 0;
        double _k = ((rand() % kDelta) + kStart) / detalisationK;
        double _b = ((rand() % bDelta) + bStart) / detalisationK;
        double xDelta = abs(topCellXBoundLen / 100);

        for (double x = topCellXBound.x; x < topCellXBound.y; x += xDelta)
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

        //printf("currQuadraticDelta: %lf | k: %lf, b: %lf\n", currQuadraticDelta, _k, _b);
        COLORREF quadraticDeltaColor = getQuadraticDeltaColor(currQuadraticDelta);
        Vector point = { _k, _b };
        bottomSystem->addPoint(point, quadraticDeltaColor);
    }
}

COLORREF MainLinLayout::getQuadraticDeltaColor(double quadraticDelta)
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

    int r2 = r0 + (double)(r1 - r0) * t;
    int g2 = 0;
    int b2 = b0 + (double)(b1 - b0) * t;


    COLORREF answer = RGB(r2, g2, b2);
    return answer;
}

double MainLinLayout::calcQuadratic(double k, double b, double x, double(*fnc)(double k, double b, double x), double (*originalFnc)(double x))
{
    double dy = fnc(k, b, x) - originalFnc(x);
    return (dy * dy);
}


void MainLinLayout::countGradientMap()
{
    double k = 0, b = 0;
    Vector kBound = { 0, 10 }; //k = A - амплитуда идеальное A = 5
    Vector bBound = { 6.8, 7.2 }; // b = f - фаза  идеальное f = 7
    //thread findKoefficents(&MainLinLayout::threadCoeffFinder, this, );
    threadCoeffFinder(&answerK, &answerB, kBound, bBound, &MainLinLayout::sinFnc, &MainLinLayout::originalSinFnc);
}
