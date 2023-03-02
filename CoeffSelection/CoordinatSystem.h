#pragma once
#pragma once

//#include "Q_Vector.h"
#include <TXLib.h>
#include "..\..\TESTWIN32_GRAPHICAPP\Q_Vector.h"
#include "..\..\TESTWIN32_GRAPHICAPP\Q_Rect.h"
#include <math.h>
#include <string.h>
#include ""
//#include "Config.h"
//#include "Q_Ball.h"

using namespace std;

double humanRound(double delta);
Vector makePerpendikularLine(const Vector& mainVector);
void drawArrows(const Vector& mainVector, const Vector& startArrowPoint);
void txSetAllColors(COLORREF color, HDC dc = txDC());

struct CoordinatSysConfig
{
    int font = 20;
    COLORREF backgroundColor = 0;
    COLORREF axisColor = 0;
    string xName = "";
    string yName = "";
};


class CoordinatSys
{

private:
    Rect pixRect = {};
    Vector nullCoor = {};
    Vector nullPointUnit = {}; // координата в нуле
    Vector cUnits = {}; // количество клеточек по х
    CoordinatSysConfig config;
    Vector lastNDelta = {};
    HDC dc;

    Vector intepretK_ = { 1, -1 }; //= scalePix / coorSize;

public: CoordinatSys(HDC outputDc = txDC());

      void setPixRect(Rect _pixRect);
      const Rect& getPixRect();
      void setNullCoor(Vector _pixRect);
      const Vector& getNullCoor();
      void setNullPointUnit(Vector _pixRect);
      const Vector& getNullPointUnit();                                 


      Vector drawFunc(const char* func);
      Vector drawCircle(const Vector& vector, double r = 10);
      void drawLine(Vector startLPos, Vector finishLPos, COLORREF color = 1);
      Vector interpret(Vector vector);
      Vector convertFromPixels(Vector vector);
      void drawAxis();
      void clean();
      Vector getXBound();
      Vector getYBound();

private:
    void drawAxisLines();

};
