#pragma once 
#include "ColorfullCoordinatSystemWindow.h"


int ColorfullCoordinatSystemWindow::addPoint(Vector point, COLORREF pointColor/* = NULL*/)
{
    int res = CoordinatSystemWindow::addPoint(point);

    pointsColorArrMutex.lock();
    if (pointColor == 0) pointColor = pointsColor;
    pointsColorArr.push_back(pointColor);
    pointsColorArrMutex.unlock();
    return res;
}


int ColorfullCoordinatSystemWindow::clearSys()
{
    try
    {
        int _size = CoordinatSystemWindow::clearSys();
        pointsColorArrMutex.lock();
        if (pointsColorArr.size() > 0) pointsColorArr.clear();
        pointsColorArrMutex.unlock();
        return _size;
    }
    catch (...)
    {
        cout << "Программа упала";
    }
    return 0;
}


void ColorfullCoordinatSystemWindow::drawPoints()
{
    int vectorSize = points.size();
    M_HDC& _outDC = *getOutputDC();
    
    COLORREF currColor = NULL;
    app->setColor(currColor, _outDC);

    Vector halfSize = { pointsR, pointsR };

    pointsMutex.lock();
    pointsColorArrMutex.lock();
    for (int i = 0; i < vectorSize; i++)
    {
        COLORREF newColor = pointsColorArr[i];
        if (newColor != currColor)
        {
            app->setColor(newColor, _outDC);
            currColor = newColor;
        }
        Vector pixPos = fromCellToPix(points[i]);
        app->ellipse(pixPos, halfSize, _outDC);
    }
    pointsMutex.unlock();
    pointsColorArrMutex.unlock();
}
