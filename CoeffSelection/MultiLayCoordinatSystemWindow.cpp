#pragma once
#include "MultiLayCoordinatSystemWindow.h"


MultiLayCoordinatSystemWindow::MultiLayCoordinatSystemWindow(AbstractAppData* _app) :
    CustomRCoordinatSystemWindow(_app)
{
    scoped_lock lock1(laysMutex);
};


size_t MultiLayCoordinatSystemWindow::addLay()
{
    scoped_lock lock1(laysMutex);
    lays.push_back(CoordinatLay());
    size_t newElementPos = lays.size() - 1;

    return newElementPos;
}

size_t MultiLayCoordinatSystemWindow::getActiveLayIndex()
{
    return 0;
}

size_t MultiLayCoordinatSystemWindow::setActiveLayIndex(size_t index)
{
    return 0;
}


size_t MultiLayCoordinatSystemWindow::addPoint(Vector point, size_t layIndex/* = 0*/, COLORREF _pointColor/* = NULL*/, int _r/* = 0*/)
{
    scoped_lock locklay(laysMutex);
    size_t _size = lays.size();
    if (layIndex < _size)
    {

    }
    return 0;
}

size_t MultiLayCoordinatSystemWindow::CoordinatLay::addPoint(Vector pos, COLORREF color, int r)
{
    pointsLay.push_back(pos);
    colorLay.push_back(color);
    rLay.push_back(r);
    return pointsLay.size();
}