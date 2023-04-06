#pragma once
#include "MainCoorLinLayout.h"
#include "QuickSort.cpp"
#include <thread>

MainCoorLinLayout::MainCoorLinLayout(AbstractAppData* _app) :
    LinearLayout(_app, {}, LinearLayout::FLAG_VERTICAL),
    topWnd(_app),
    bottomWnd(_app),
    topFncCmp(_app, {}, LinearLayout::FLAG_VERTICAL),
    topHandle(_app),
    topLogFnc(_app),
    topLinFnc(_app),
    bottomOdd(_app)
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
    
    bottomWnd.addLay();
    bottomWnd.addLay();

    topOdd.setWrapStatus(true);
    topOdd.setColor(C_TRANSPARENT);
    topOdd.setTrancparencyOutput(true);
    topOdd.setText("Коэффициенты еще подбираются");
    addWindow(topOdd);

    bottomOdd.setWrapStatus(true);
    bottomOdd.setColor(C_TRANSPARENT);
    bottomOdd.setTrancparencyOutput(true);
    bottomOdd.setText("Коэффициенты еще подбираются");
    addWindow(bottomOdd);

    thread sortThread(&MainCoorLinLayout::startComputations, this);
    sortThread.detach();
}

string MainCoorLinLayout::oddsToString(Vector _odd)
{
    string answer = {};
    answer = to_string(_odd.x) + "*x*log(" + to_string(_odd.y) + "*x)";
    return answer;
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
        //topWnd.addPoint({ (double)_len, logres }, logColor, 0, logIndex, false);
        bottomWnd.addPoint({ (double)_len, (double)getCExchanges() }, sortDataColor, 0, sortDataIndex, false);
        //bottomWnd.addPoint({ (double)_len, logres }, logColor, 0, logIndex, false);
    }

    invalidateButton();
    delete[] arr;

    cout << clock() - start << "ms заняли вычесления сложности сортировки\n";

    double topDelta = gradientDescent(topGradientLogOdds, topWnd, &MainCoorLinLayout::logfnc, logLearningRate);
    static string topGradientText = oddsToString(topGradientLogOdds) + " с отклонением всего " + to_string(topDelta);
    topGradientText.insert(0, "Подошло ");
    cout << topGradientText;
    drawGradientOdds(topGradientLogOdds, topWnd, &MainCoorLinLayout::logfnc);

    double topLinDelta = gradientDescent(topGradientLinOdds, topWnd, &MainCoorLinLayout::linfnc, linLearningRate);
    topGradientText = oddsToString(topGradientLinOdds) + " с отклонением всего " + to_string(topLinDelta);
    topGradientText.insert(0, "Подошло ");
    cout << topGradientText;
    gradientLogColor = C_MAGENTA;
    drawGradientOdds(topGradientLinOdds, topWnd, &MainCoorLinLayout::linfnc);

    //topOdd.setText(topGradientText.c_str());
    /*
    
    double bottomDelta = gradientDescent(bottomGradientOdds, bottomWnd, &MainCoorLinLayout::logfnc);
    static string bottomGradientText = oddsToString(bottomGradientOdds) + " с отклонением всего " + to_string(bottomDelta);;
    bottomGradientText.insert(0, "Подошло ");
    bottomOdd.setText(bottomGradientText.c_str());
    */

    //drawGradientOdds(topGradientOdds, topWnd, &MainCoorLinLayout::logfnc);
    //drawGradientOdds(bottomGradientOdds, bottomWnd, &MainCoorLinLayout::logfnc);

    isActiveComputingPart = false;
}

double MainCoorLinLayout::gradientDescent(Vector& _odds, MultiLayCoordinatSystemWindow& _wnd, double (*fnc) (double k, double b, double x), Vector learning_rate)
{
    Vector gradientDelta = { 0.1, 0.1 };
    int iterations = 10000;
    for (int i = 0; i < iterations; i++)
    {
        if (!app->getAppCondition()) break;
        double currQuadraticDelta = countQuadraticDelta(_odds.x, _odds.y, _wnd, fnc);
        double dxQuadraticDelta = countQuadraticDelta(_odds.x + gradientDelta.x, _odds.y, _wnd, fnc);
        double dyQuadraticDelta = countQuadraticDelta(_odds.x, _odds.y + gradientDelta.y, _wnd, fnc);

        double xDerivative = (dxQuadraticDelta - currQuadraticDelta) / gradientDelta.x;
        double yDerivative = (dyQuadraticDelta - currQuadraticDelta) / gradientDelta.y;

        _odds.x -= learning_rate.x * xDerivative;
        _odds.y -= learning_rate.y * yDerivative;
        printf("");
    }
    //printf("");

    cout << "На сортировку лучше всего ложится: " << oddsToString(_odds) << endl;

    double finalQuadraticDelta = countQuadraticDelta(_odds.x, _odds.y, _wnd, fnc);

    return finalQuadraticDelta;
}

void MainCoorLinLayout::drawGradientOdds(Vector _odds, MultiLayCoordinatSystemWindow& wnd, double (*fnc) (double k, double b, double x))
{
    for (int i = 0; i < maxArrLen; i++)
    {
        if (!app->getAppCondition()) break;
        Vector newPoint = { (double)i, fnc(_odds.x, _odds.y, i) };

        wnd.addPoint(newPoint, gradientLogColor, 0, suggestedOddsIndex, false);
    }
    invalidateButton();
}

double MainCoorLinLayout::countQuadraticDelta(double k, double b, MultiLayCoordinatSystemWindow& wnd, double (*fnc) (double k, double b, double x))
{
    double answer = 0;
    for (int currLen = 1; currLen < maxArrLen; currLen++)
    {       
        double fncRes = fnc(k, b, currLen);
        double delta = (fncRes - wnd.getPoint(currLen, sortDataIndex).y);
        answer += delta * delta;
    }
    return answer;
}

double MainCoorLinLayout::logfnc(double k, double b, double x)
{
    return k * x * log(b * x);
}

double MainCoorLinLayout::linfnc(double k, double b, double x)
{
    double answer = (k * x ) + b;
    return answer;
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

    int res = LinearLayout::onSize(_managerSize, _newRect);
    topOdd.MoveWindowTo(topWnd.rect.pos);
    bottomOdd.MoveWindowTo(bottomWnd.rect.pos);

    return res;
}

int MainCoorLinLayout::onTimer(UINT_PTR timerName)
{
    if (activeTimer == timerName)
    {
        invalidateButton();
        if(isActiveComputingPart)activeTimer = app->setTimer(updateFrequency);
        return 1;
    }
    return 0;
}