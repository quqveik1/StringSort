#pragma once
#include "CustomRCoordinatSystemWindow.h"

struct MultiLayCoordinatSystemWindow : CustomRCoordinatSystemWindow
{
    
    struct CoordinatLay
    {
        vector<Vector> pointsLay{};
        vector<COLORREF> colorLay{};
        vector<int> rLay{};
        size_t addPoint(Vector pos, COLORREF color, int r);
    };
    vector<CoordinatLay> lays;
    mutex laysMutex;
    size_t standartLayIndex = 0;
    size_t activeLayIndex = 0;

    MultiLayCoordinatSystemWindow(AbstractAppData* _app);

    size_t addLay();
    size_t getActiveLayIndex();
    size_t setActiveLayIndex(size_t index);

    virtual size_t addPoint(Vector point, size_t layIndex = 0, COLORREF _pointColor = NULL, int _r = 0);

};