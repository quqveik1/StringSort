#pragma once
#include "CoordinatSystemWindow.h"

void CoordinatSystemWindow::setCCells(Vector _cScreenCells)
{
    cCells = _cScreenCells;
    invalidateButton();
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
    cells -= cellNull;
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
    Vector _nullPixCoor = getPixNullCoordinats();
    pixs.x -= _nullPixCoor.x;
    pixs.y = _nullPixCoor.y - pixs.y;
    Vector cells = {};
    cells.x = pixs.x / density.x;
    cells.y = (pixs.y / density.y);
    cells += cellNull;

    return cells;
}


Vector CoordinatSystemWindow::getXCellBound()
{
    Vector answer = {};
    answer.x = fromPixToCell({ 0, 0}).x;
    answer.y = fromPixToCell({ getSize().x, 0}).x;
    answer.sort();
    return answer;
}

Vector CoordinatSystemWindow::getYCellBound()
{
    Vector answer = {};
    answer.x = fromPixToCell({ 0, 0}).y;
    answer.y = fromPixToCell({ 0, getSize().y}).y;
    answer.sort();
    return answer;
}


int CoordinatSystemWindow::addPoint(Vector point)
{
    pointsMutex.lock();
    int _size = points.size();

    points.push_back(point);
    invalidateButton();
    pointsMutex.unlock();
    return _size;
}

int CoordinatSystemWindow::clearSys()
{
    try
    {
        pointsMutex.lock();
        int _size = points.size();
        if (points.size() > 0) points.clear();
        invalidateButton();
        pointsMutex.unlock();
        return _size;
    }
    catch(const char* msg)
    {
        cout << msg;
    }
    return 0;
    
}

void CoordinatSystemWindow::invalidateSysConfig()
{
    onSize({}, {});
    invalidateButton();
}

int CoordinatSystemWindow::onSize(Vector managerSize, Rect _newRect/* = {}*/)
{
    Window::onSize(managerSize, _newRect);
    axisSystemDC.setSize(getOutputDC()->getSize(), app);
    app->setColor(color, axisSystemDC);
    app->rectangle({}, axisSystemDC.getSize(), axisSystemDC);

    Vector pixStep = getPixCellStep();
    Vector cellStep = getHumanCellStep();

    app->setColor(axisColor, axisSystemDC);
    char textNum[MAX_PATH] = {};
    for (int x = 0; x <= lround(cCellsLines.x); x++)
    {
        drawOneXLine(x, cellStep, textNum, axisSystemDC);
    }
    for (int x = -1; x >= -lround(cCellsLines.x); x--)
    {
        drawOneXLine(x, cellStep, textNum, axisSystemDC);
    }

    for (int y = 0; y <= lround(cCellsLines.y); y++)
    {
        drawOneYLine(y, cellStep, textNum, axisSystemDC);
    }
    for (int y = -1; y >= -lround(cCellsLines.y); y--)
    {
        drawOneYLine(y, cellStep, textNum, axisSystemDC);
    }

    drawAxisName(axisSystemDC);

    return 0;
}

void CoordinatSystemWindow::draw()
{
    if (true/*!isValidViewState()*/)
    {
        Window::draw();
        Vector pixStep = getPixCellStep();
        Vector cellStep = getHumanCellStep();

        /*
        char textNum[MAX_PATH] = {};
        app->setColor(axisColor, *getOutputDC());
        for (int x = 0; x <= lround(cCellsLines.x); x++)
        {
            drawOneXLine(x, cellStep, textNum);
        }
        for (int x = -1; x >= -lround(cCellsLines.x); x--)
        {
            drawOneXLine(x, cellStep, textNum);
        }

        for (int y = 0; y <= lround(cCellsLines.y); y++)
        {
            drawOneYLine(y, cellStep, textNum);
        }
        for (int y = -1; y >= -lround(cCellsLines.y); y--)
        {
            drawOneYLine(y, cellStep, textNum);
        }

        drawAxisName();
        */
        app->bitBlt(*getOutputDC(), {}, axisSystemDC);
        drawPoints();
    }

}


void CoordinatSystemWindow::onClick(Vector mp)
{
    Window::onClick(mp);
    Vector clickedCellPos = fromPixToCell(mp);

    cout << clickedCellPos.getStr();

    if (onClickListener)
    {
        onClickListener->sendMessage(NULL, &clickedCellPos);
    }
}

void CoordinatSystemWindow::drawPoints()
{
    int vectorSize = points.size();
    M_HDC& _outDC = *getOutputDC();
    app->setColor(pointsColor, _outDC);

    Vector halfSize = { pointsR, pointsR };

    pointsMutex.lock();
    for (int i = 0; i < vectorSize; i++)
    {
        Vector pixPos = fromCellToPix(points[i]);
        app->ellipse(pixPos, halfSize, _outDC);
    }
    pointsMutex.unlock();
}


void CoordinatSystemWindow::drawAxisName(M_HDC& destDC)
{
    app->setColor(app->systemSettings->TextColor, destDC);
    Vector xBound = getXCellBound();
    Vector yBound = getYCellBound();
    
    Vector xAxisNameTopRight = fromCellToPix({ xBound.y, cellNull.y });
    Vector xAxisNameBottomLeft = { xAxisNameTopRight.x - 200, xAxisNameTopRight.y + 200 };

    Rect rectXAxisName = { xAxisNameTopRight, xAxisNameBottomLeft };
    rectXAxisName.sort();  

    app->setColor(app->systemSettings->TextColor, destDC);
    app->drawText(rectXAxisName, axisXName.c_str(), destDC, DT_RIGHT | DT_TOP);

    Vector yAxisNameLeftTop = fromCellToPix({ cellNull.x, yBound.y});
    Vector yAxisNameRightBottom = { yAxisNameLeftTop.x + 200, yAxisNameLeftTop.y + 200 };

    Rect rectYAxisName = { yAxisNameLeftTop, yAxisNameRightBottom };
    rectYAxisName.sort();

    app->setColor(app->systemSettings->TextColor, destDC);
    app->drawText(rectYAxisName, axisYName.c_str(), destDC, DT_LEFT | DT_TOP);
}

void CoordinatSystemWindow::drawOneYLine(int stepNum, const Vector& cellStep, char* textBuf, M_HDC& destDc)
{
    double outputNum = cellNull.y+ stepNum * cellStep.y;
    sprintf(textBuf, "%.2lf", outputNum);

    Rect drawRect = {};
    Vector pixPos = fromCellToPix({ cellNull.x, outputNum });
    
    drawRect.finishPos.x = pixPos.x;
    drawRect.pos.x = drawRect.finishPos.x - 100;

    drawRect.pos.y = pixPos.y;
    drawRect.finishPos.y = drawRect.pos.y + 100;

    Rect lineRect = {};
    lineRect.pos.x = 0;
    lineRect.pos.y = pixPos.y;

    lineRect.finishPos.x = getSize().x;
    lineRect.finishPos.y = lineRect.pos.y;

    app->line(lineRect, destDc);

    app->drawText(drawRect, textBuf, destDc, DT_RIGHT);
}

void CoordinatSystemWindow::drawOneXLine(int stepNum, const Vector& cellStep, char* textBuf, M_HDC& destDc)
{
    double outputNum = cellNull.x + stepNum * cellStep.x;
    sprintf(textBuf, "%.2lf", outputNum);

    Rect drawRect = {};
    Vector pixPos = fromCellToPix({ outputNum, cellNull.y });

    drawRect.pos = pixPos;
    drawRect.finishPos = drawRect.pos + 100;

    Rect lineRect = {};
    lineRect.pos.x = pixPos.x;
    lineRect.pos.y = 0;

    lineRect.finishPos.x = pixPos.x;
    lineRect.finishPos.y = getSize().y;

    app->line(lineRect, destDc);

    app->drawText(drawRect, textBuf, destDc, DT_LEFT);
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