#pragma once
#include <Window.cpp>

struct CoordinatSystemWindow : Window
{
    Vector cCells = {};
    Vector cCellsLines = { 10, 10 };
    Vector cellNull = {};
    Vector pixNullPercantage = { 0.1, 0.1 };

    CoordinatSystemWindow(AbstractAppData* _app) :
        Window(_app)
    {
    };

    double humanRound(double delta);

    void setCCells(Vector _cScreenCells);
    //-pix per cell
    Vector getDensity();
    Vector getPixNullCoordinats();
    Vector getHumanCellStep();
    Vector getPixCellStep();
    Vector fromCellToPix(Vector cells);
    Vector fromPixToCell(Vector pixs);

    void draw() override;
    int onSize(Vector managerSize, Rect _newRect = {}) override;
};