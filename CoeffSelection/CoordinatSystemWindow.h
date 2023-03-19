#pragma once           
#include <Window.cpp>
#include <mutex>

struct CoordinatSystemWindow : Window
{
    Vector cCells = {};
    Vector cCellsLines = { 10, 10 };
    Vector cellNull = {};
    Vector pixNullPercantage = { 0.1, 0.1 };
    COLORREF axisColor = RGB(150, 150, 150);
    COLORREF pointsColor = C_LIGHTBLUE;
    int pointsR = 2;
    string axisXName;
    string axisYName;

    mutex pointsMutex;
    vector<Vector> points;

    Window* onClickListener = NULL;

    CoordinatSystemWindow(AbstractAppData* _app) :
        Window(_app)
    {
    };

    double humanRound(double delta);

    void drawOneXLine(int stepNum, const Vector& cellStep, char* textBuf);
    void drawOneYLine(int stepNum, const Vector& cellStep, char* textBuf);
    virtual void drawPoints();
    void drawAxisName();

    void setCCells(Vector _cScreenCells);
    void setCellNull(Vector _cellNull)   { cellNull = _cellNull;           invalidateButton(); };
    void setAxisColor(COLORREF _color)   { axisColor = _color;             invalidateButton(); };
    void setAxisXName(string _axisXName)   { axisXName = _axisXName;      invalidateButton(); };
    void setAxisYName(string _axisYName)   { axisYName = _axisYName;      invalidateButton(); };
    void setPointsColor(COLORREF _color) { pointsColor = _color;           invalidateButton(); };
    void setPointsR(int _r)              { pointsR = _r;                   invalidateButton(); };
    void setOnClickListener(Window* _wnd) { onClickListener = _wnd;        invalidateButton(); };

    //-pix per cell
    Vector getDensity();
    Vector getPixNullCoordinats();
    Vector getHumanCellStep();
    Vector getPixCellStep();
    Vector fromCellToPix(Vector cells);
    Vector fromPixToCell(Vector pixs);

    virtual Vector getXCellBound();
    virtual Vector getYCellBound();
    virtual int addPoint(Vector point);
    virtual int clearSys();

    void draw() override;
    virtual void onClick(Vector mp) override;
    int onSize(Vector managerSize, Rect _newRect = {}) override;
};