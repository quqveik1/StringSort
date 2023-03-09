#pragma once
#include "CoordinatSystemWindow.h"
#include <vector>


struct ColorfullCoordinatSystemWindow : CoordinatSystemWindow
{
    mutex pointsColorArrMutex;
    vector<COLORREF> pointsColorArr;

    ColorfullCoordinatSystemWindow(AbstractAppData* _app) :
        CoordinatSystemWindow(_app)
    {
    };

    virtual int addPoint(Vector point, COLORREF _pointColor = NULL);
    virtual void drawPoints() override;
};