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
    topWnd.setCCells({ (double)maxArrLen, maxArrLen * log2(maxArrLen) });
    topWnd.setMatchParentX(true);
    addWindow(bottomWnd);
    bottomWnd.setCCells({ (double)maxArrLen, maxArrLen * log2(maxArrLen) });
    bottomWnd.setMatchParentX(true);
    activeTimer = app->setTimer(updateFrequency);

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
        topWnd.addPoint({ (double)_len, (double)getCCmps() }, false);
        bottomWnd.addPoint({ (double)_len, (double)getCExchanges() }, false);
    }

    invalidateButton();
    delete[] arr;

    cout << clock() - start << "ms заняли вычесления\n";
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