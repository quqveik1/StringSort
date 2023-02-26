#pragma once
#include "..\..\ALGORITHMICPROJECT\Q_CoordinatSystem.h"

void findBestCoeff(coordinatSys& sys, double* k, double* b, Vector& kBound, Vector& bBound, Vector& xBound, double(*fnc)(double k, double b, double x), double (*originalFnc)(double x));
double calcQuadratic(double k, double b, double x, double(*fnc)(double k, double b, double x), double (*originalFnc)(double x));
void drawBestCoeff(coordinatSys& sys, double k, double b, Vector& xBound, double(*fnc)(double k, double b, double x), COLORREF color);
void findAndDrawBestCoeff(coordinatSys& sys, coordinatSys& deltaSys, double(*fnc)(double k, double b, double x), double (*originalFnc)(double x), double* findedK, double* findedB, Vector& kBound, Vector& bBound, Vector& xBound, COLORREF color);
COLORREF getQuadraticDeltaColor(double quadraticDelta);
