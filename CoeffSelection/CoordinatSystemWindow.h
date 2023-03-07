#pragma once           
#include <Window.cpp>

struct CoordinatSystemWindow : Window
{
    Vector cCells = {};
    Vector cCellsLines = { 10, 10 };
    Vector cellNull = {};
    Vector pixNullPercantage = { 0.1, 0.1 };
    COLORREF axisColor = RGB(150, 150, 150);
    COLORREF pointsColor = C_LIGHTBLUE;
    int pointsR = 2;

    vector<Vector> points;

    CoordinatSystemWindow(AbstractAppData* _app) :
        Window(_app)
    {
    };

    double humanRound(double delta);

    void drawOneXLine(int stepNum, const Vector& cellStep, char* textBuf);
    void drawOneYLine(int stepNum, const Vector& cellStep, char* textBuf);
    virtual void drawPoints();

    void setCCells(Vector _cScreenCells);
    void setAxisColor(COLORREF _color) { axisColor = _color; app->updateScreen(this); };
    void setPointsColor(COLORREF _color) { pointsColor = _color; app->updateScreen(this); };
    void setPointsR(int _r) { pointsR = _r; app->updateScreen(this); };

    //-pix per cell
    Vector getDensity();
    Vector getPixNullCoordinats();
    Vector getHumanCellStep();
    Vector getPixCellStep();
    Vector fromCellToPix(Vector cells);
    Vector fromPixToCell(Vector pixs);

    virtual Vector getXCellBound();
    virtual int addPoint(Vector point);
    virtual int clearSys();

    void draw() override;
    int onSize(Vector managerSize, Rect _newRect = {}) override;
};