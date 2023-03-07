#pragma once 
#include "ColorfullCoordinatSystemWindow.h"


int ColorfullCoordinatSystemWindow::addPoint(Vector point, COLORREF pointColor/* = NULL*/)
{
    int res = CoordinatSystemWindow::addPoint(point);

    if (pointColor == 0) pointColor = pointsColor;
    pointsColorArr.push_back(pointColor);
    return res;
}


void ColorfullCoordinatSystemWindow::drawPoints()
{
    int vectorSize = points.size();
    M_HDC& _outDC = *getOutputDC();
    
    COLORREF currColor = NULL;
    app->setColor(currColor, _outDC);

    Vector halfSize = { pointsR, pointsR };

    for (int i = 0; i < vectorSize; i++)
    {
        COLORREF newColor = pointsColorArr[i];
        if (newColor != currColor)
        {
            app->setColor(newColor, _outDC);
        }
        Vector pixPos = fromCellToPix(points[i]);
        app->ellipse(pixPos, halfSize, _outDC);
    }
}