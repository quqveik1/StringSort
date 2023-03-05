#pragma once
#include "CoordinatSystemWindow.h"

void CoordinatSystemWindow::setCCells(Vector _cScreenCells)
{
    cCells = _cScreenCells;
}

Vector CoordinatSystemWindow::getDensity()
{
    Vector _currSize = getSize();

    Vector density = _currSize / cCells;
    return density;
}

Vector CoordinatSystemWindow::getPixNullCoordinats()
{
    Vector ans = {};
    Vector currSize = getSize();
    ans.x = currSize.x * pixNullPercantage.x;
    ans.y = currSize.y * (1 - pixNullPercantage.y);
    return ans;
}

Vector CoordinatSystemWindow::getHumanCellStep()
{
    Vector cellStep = {};
    cellStep.x = humanRound(cCells.x / cCellsLines.x);
    cellStep.y = humanRound(cCells.y / cCellsLines.y);
    return cellStep;
}

Vector CoordinatSystemWindow::getPixCellStep()
{
    Vector pixCellStep = getHumanCellStep() * getDensity();

    return pixCellStep;
}


Vector CoordinatSystemWindow::fromCellToPix(Vector cells)
{
    Vector density = getDensity();
    Vector pixCells = {};
    pixCells.x = cells.x * density.x;
    pixCells.y = - (cells.y * density.y);
    pixCells += getPixNullCoordinats();

    return pixCells;
}

Vector CoordinatSystemWindow::fromPixToCell(Vector pixs)
{
    Vector density = getDensity();
    pixs -= getPixNullCoordinats();
    Vector cells = {};
    cells.x = pixs.x / density.x;
    cells.y = - (pixs.y / density.y);

    return cells;
}

void CoordinatSystemWindow::draw()
{
    Vector pixStep = getPixCellStep();
    Vector cellStep = getHumanCellStep();

    char textNum[MAX_PATH] = {};
    for (int x = 1; x <= lround(cCells.x); x++)
    {
        double pixX = x * pixStep.x;
        double outputNum = cellNull.x + x * cellStep.x;
        sprintf(textNum, "%lf", outputNum);

        Rect drawRect = {};
        drawRect.pos = fromCellToPix({ outputNum, 0 });
        drawRect.finishPos = drawRect.pos + 100;

        app->drawText(drawRect, textNum, *getOutputDC(), DT_LEFT);
    }
}

int CoordinatSystemWindow::onSize(Vector managerSize, Rect _newRect/* = {}*/)
{
    Window::onSize(managerSize, _newRect);
    return 0;
}



double CoordinatSystemWindow::humanRound(double delta)
{
    /*
    * 0.1 -> 0.1
    * 0.12 -> 0.1
    * 0.2  -> ??
    * 0.23 -> 0.25
    * 0.25 -> 0.25
    * 0.28 -> 0.25
    * 0.3  -> 0.25
    * 0.35 - >0.5
    * 0.4  0.5
    * 0.5  0.5
    * 0.6  0.5
    * 0.7  1
    * 0.8  1
    * 0.9  1
    * 3.14 exp:1
    *
    */

    //printf ("\n::%d::\n", delta);
    delta = fabs(delta);
    double exp = log10(delta);
    double mantissa = delta / (pow(10, ceil(exp)));

    //double mantissa = frexp (delta, &order);

    //printf ("Delta: %lf\tExp: %lf \tMantissa: %lf\n", delta, exp, mantissa);

    if (mantissa < 0.15) mantissa = 0.1;
    if (0.15 <= mantissa && mantissa < 0.23) mantissa = 0.2;
    if (0.23 <= mantissa && mantissa < 0.35) mantissa = 0.25;
    if (0.35 <= mantissa && mantissa < 0.65) mantissa = 0.5;
    if (0.65 <= mantissa && mantissa <= 1)   mantissa = 1;

    //printf ("delta: %lf, fDelta: %lf\n", delta, mantissa * pow (10, ceil(exp)));


    return mantissa * pow(10, ceil(exp));
}