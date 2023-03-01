// CoeffSelection.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <TXLib.h>
#include "..\..\ALGORITHMICPROJECT\Q_CoordinatSystem.h"
#include <Q_Vector.h>
#include "FindCoeff.cpp"

void setAxis(coordinatSys* sys1, coordinatSys* deltaSys, coordinatSysConfig* conf, const Vector& screenSize);
void drawOriginalFunc(coordinatSys& sys, double (*originalFnc)(double x));
void testOneConf(double k, double b, coordinatSys& sys, coordinatSys& deltaSys, Vector& kBound, Vector& bBound, Vector& xBound, double(*fnc)(double k, double b, double x), double (*originalFnc)(double x));

double sinfnc(double k, double b, double x);
double originalSinFnc(double x);
void sinusSetup(coordinatSys& sys, coordinatSys& deltaSys);


double linearFnc(double k, double b, double x);
double originalLinearFnc(double x);
void linearStup(coordinatSys& sys, coordinatSys& deltaSys);


double kSinB(double k, double b, double x);
double originalKSinB(double x);

double currOriginalK = 0, currOriginalB = 0;

// sin(5x + 7)
int main()
{
    Vector screenSize = { 1000, 800 };
    txCreateWindow(screenSize.x, screenSize.y);
    txSetTextAlign(TA_RIGHT);
    coordinatSys sys{};
    coordinatSys deltaSys{};
    coordinatSysConfig conf;
    setAxis(&sys, &deltaSys, &conf, screenSize);
    
    sinusSetup(sys, deltaSys);
}


void linearStup(coordinatSys& sys, coordinatSys& deltaSys)
{
    double k = 0, b = 0;
    Vector kBound = { -10, 10 };
    Vector bBound = { -1, 1 };
    Vector xBound = sys.getXBound();

    testOneConf(5,    1,     sys, deltaSys, kBound, bBound, xBound, linearFnc, originalLinearFnc);
    testOneConf(9,    0.25,  sys, deltaSys, kBound, bBound, xBound, linearFnc, originalLinearFnc);
    testOneConf(3,    1.25,  sys, deltaSys, kBound, bBound, xBound, linearFnc, originalLinearFnc);
    testOneConf(2.5,  -0.57, sys, deltaSys, kBound, bBound, xBound, linearFnc, originalLinearFnc);
}

double originalLinearFnc(double x)
{
    return linearFnc(currOriginalK, currOriginalB, x);
}

double linearFnc(double k, double b, double x)
{
    return k * x + b;
}

double kSinB(double k, double b, double x)
{
    /// k - A, B - f(частота)
    return k * sin(b * x);
}

double originalKSinB(double x)
{
    return kSinB(currOriginalK, currOriginalB, x);
}

void sinusSetup(coordinatSys& sys, coordinatSys& deltaSys)
{

    double k = 0, b = 0;
    Vector kBound = { 0, 10 }; //k = A - амплитуда идеальное A = 5
    Vector bBound = { 6.8, 7.2 }; // b = f - фаза  идеальное f = 7
    Vector xBound = sys.getXBound();

    //          k       b
    testOneConf(5,      7,  sys, deltaSys, kBound, bBound, xBound, kSinB, originalKSinB);

    //testOneConf(5,      7,  sys, deltaSys, kBound, bBound, xBound, sinfnc, originalSinFnc);
    //testOneConf(9,      44, sys, deltaSys, kBound, bBound, xBound, sinfnc, originalSinFnc);
    //testOneConf(3,     35,  sys, deltaSys, kBound, bBound, xBound, sinfnc, originalSinFnc);
    //testOneConf(2.5,   29,  sys, deltaSys, kBound, bBound, xBound, sinfnc, originalSinFnc);

}

void testOneConf(double k, double b, coordinatSys& sys, coordinatSys& deltaSys, Vector& kBound, Vector& bBound, Vector& xBound, double(*fnc)(double k, double b, double x), double (*originalFnc)(double x))
{
    currOriginalK = k;
    currOriginalB = b;

    drawOriginalFunc(sys, originalFnc);

    findAndDrawBestCoeff(sys, deltaSys, fnc, originalFnc, &k, &b, kBound, bBound, xBound, TX_BLUE);
    printf("Original k: %lf, b: %lf | Suggested k: %lf, b: %lf\n", currOriginalK, currOriginalB, k, b);
    (void)_getch();

    sys.clean();
}

double sinfnc(double k, double b, double x)
{
    return sin(k * x + b);
}


double originalSinFnc(double x)
{
    return sinfnc(currOriginalK, currOriginalB, x);
}

void drawOriginalFunc(coordinatSys& sys, double (*originalFnc)(double x))
{
    Vector xBound = sys.getXBound();
    Vector point = {};
    txSetColor(TX_RED);
    txSetFillColor(TX_RED);
    for (double x = xBound.x; isSmaller(x, xBound.y); x += 0.001)
    {
        point.x = x;    
        point.y = originalFnc(x);
        sys.drawCircle(point, 1);
    }

}

void setAxis(coordinatSys* sys1, coordinatSys* deltaSys, coordinatSysConfig* conf, const Vector& screenSize)
{
    
    sys1->startPosPix_ = { 0, 0 };
    sys1->finishPosPix_ = { screenSize.x, screenSize.y / 2 };
    sys1->nullCoor_ = { 40, screenSize.y / 4 };
    deltaSys->xName = "X";
    deltaSys->yName = "Y";
    
    sys1->config_ = *conf;

    sys1->intepretK_.y = -20;
    sys1->intepretK_.x = 100;
    sys1->drawAxis({ 200, 1000 });
    
    deltaSys->startPosPix_ = { 0, screenSize.y / 2 };
    deltaSys->finishPosPix_ = { screenSize.x, screenSize.y};
    deltaSys->nullCoor_ = {40, screenSize.y - 20};
    deltaSys->nullPoint = {0, 6.8};
    deltaSys->xName = "A";
    deltaSys->yName = "f";
    
    deltaSys->config_ = *conf;

    deltaSys->intepretK_.y = -1000;
    deltaSys->intepretK_.x = 80;
    deltaSys->drawAxis({ 10000, 800 });
}