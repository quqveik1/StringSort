#pragma once
#include "MainCoorLinLayout.h"
#include "QuickSort.cpp"
#include <thread>

MainCoorLinLayout::MainCoorLinLayout(AbstractAppData* _app) :
    LinearLayout(_app, {}, LinearLayout::FLAG_VERTICAL),
    topWnd(_app),
    bottomWnd(_app)
{
    setMatchParent(true);
    addWindow(topWnd);
    topWnd.setCCells({ (double)maxArrLen, maxArrLen * log(maxArrLen) });
    topWnd.setMatchParentX(true);
    addWindow(bottomWnd);
    bottomWnd.setCCells({ (double)maxArrLen, maxArrLen * log(maxArrLen) });
    bottomWnd.setMatchParentX(true);
    activeTimer = app->setTimer(updateFrequency);

    topWnd.addLay();
    topWnd.addLay();

    thread sortThread(&MainCoorLinLayout::startComputations, this);
    sortThread.detach();
}

void MainCoorLinLayout::startComputations()
{
    int* arr = new int[maxArrLen] {};
    int start = clock();
    for (int _len = 1; _len <= maxArrLen; _len++)
    {
        if (!app->getAppCondition()) break;
        randomArrFill(arr, _len);
        testIntQuickSort(arr, _len);
        double logres = _len * log(_len);

        topWnd.addPoint({ (double)_len, (double)getCCmps() }, sortDataColor, 0, sortDataIndex, false);
        topWnd.addPoint({ (double)_len, logres }, logColor, 0, logIndex, false);
        bottomWnd.addPoint({ (double)_len, (double)getCExchanges() }, sortDataColor, 0, sortDataIndex, false);
        bottomWnd.addPoint({ (double)_len, logres }, logColor, 0, logIndex, false);
    }

    invalidateButton();
    delete[] arr;

    cout << clock() - start << "ms заняли вычесления\n";
    gradientDescent();
    drawGradientOdds();

    isActiveComputingPart = false;
}

void MainCoorLinLayout::gradientDescent()
{
   
    Vector learning_rate = { 1e-10, 1e-10};
    Vector gradientDelta = { 0.1, 0.1 };
    int iterations = 1000;
    for (int i = 0; i < iterations; i++)
    {
        if (!app->getAppCondition()) break;
        double currQuadraticDelta = countQuadraticDelta(gradientOdds.x, gradientOdds.y);
        double dxQuadraticDelta = countQuadraticDelta(gradientOdds.x + gradientDelta.x, gradientOdds.y);
        double dyQuadraticDelta = countQuadraticDelta(gradientOdds.x, gradientOdds.y + gradientDelta.y);

        double xDerivative = (dxQuadraticDelta - currQuadraticDelta) / gradientDelta.x;
        double yDerivative = (dyQuadraticDelta - currQuadraticDelta) / gradientDelta.y;

        gradientOdds.x -= learning_rate.x * xDerivative;
        gradientOdds.y -= learning_rate.y * yDerivative;
        //printf("");
    }
    //printf("");

    cout << "На сортировку лучше всего ложится: " << to_string(gradientOdds.x) << " * x * log(" << to_string(gradientOdds.y) << " * x)\n";
}

void MainCoorLinLayout::drawGradientOdds()
{
    for (int i = 0; i < maxArrLen; i++)
    {
        if (!app->getAppCondition()) break;
        Vector newPoint = { i, logfnc(gradientOdds.x, gradientOdds.y, i) };

        topWnd.addPoint(newPoint, gradientLogColor, 0, suggestedOddsIndex, false);
    }
    invalidateButton();
}

double MainCoorLinLayout::countQuadraticDelta(double k, double b)
{
    double answer = 0;
    for (int currLen = 1; currLen < maxArrLen; currLen++)
    {       
        double fncRes = logfnc(k, b, currLen);
        double delta = (fncRes - topWnd.getPoint(currLen, sortDataIndex).y);
        answer += fabs(delta);
    }
    return answer;
}

double MainCoorLinLayout::logfnc(double k, double b, double x)
{
    return k * x * log(b * x);
}

void MainCoorLinLayout::randomArrFill(int* arr, int len)
{
    for (int i = 0; i < len; i++)
    {
        arr[i] = rand();
    }
}


int MainCoorLinLayout::onSize(Vector _managerSize, Rect _newRect)
{
    LinearLayout::onSize(_managerSize, _newRect);

    topWnd.onSize({}, { .pos = {}, .finishPos = {getSize().x, getSize().y * 0.5} });
    bottomWnd.onSize({}, { .pos = {}, .finishPos = {getSize().x, getSize().y * 0.5} });

    return LinearLayout::onSize(_managerSize, _newRect);
}

int MainCoorLinLayout::onTimer(UINT_PTR timerName)
{
    if (activeTimer == timerName)
    {
        invalidateButton();
        activeTimer = app->setTimer(updateFrequency);
        return 1;
    }
    return 0;
}