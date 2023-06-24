#pragma once
#include "MainCoorLinLayout.h"
#include "..\QuickSort.cpp"
#include <thread>

MainCoorLinLayout::MainCoorLinLayout(AbstractAppData* _app) :
    LinearLayout(_app, {}, LinearLayout::FLAG_VERTICAL),
    topWnd(_app),
    bottomWnd(_app),
    topFncCmpLayout(_app, {}, LinearLayout::FLAG_VERTICAL),
    topHandle(_app),
    topLogFnc(_app),
    topLinFnc(_app), 
    bottomFncCmpLayout(_app, {}, LinearLayout::FLAG_VERTICAL),
    bottomHandle(_app),
    bottomLogFnc(_app),
    bottomLinFnc(_app),
    graficInfoLayout(_app, {}, LinearLayout::FLAG_VERTICAL),
    sortDataText(_app),
    logDataText(_app),
    linDataText(_app),
    computionStatusText(_app)
{
    setMatchParent(true);
    initCoorSys();
    activeTimer = app->setTimer(updateFrequency);

    initColorDescribtions();
    initDescribtions();

    thread sortThread(&MainCoorLinLayout::startComputations, this);
    sortThread.detach();
}

void MainCoorLinLayout::initColorDescribtions()
{
    // Добавляем строки в ресурсы
    getApp().getStringResources().addCResource(StringResources::Russian, "sortDataText", "Циановый - данные функции сортировки");
    getApp().getStringResources().addCResource(StringResources::English, "sortDataText", "Cyan - sort function data");

    getApp().getStringResources().addCResource(StringResources::Russian, "logDataText", "Желтый - подобранный логарифм");
    getApp().getStringResources().addCResource(StringResources::English, "logDataText", "Yellow - fitted logarithm");

    getApp().getStringResources().addCResource(StringResources::Russian, "linDataText", "Красный - подобранная прямая");
    getApp().getStringResources().addCResource(StringResources::English, "linDataText", "Red - fitted line");

    addWindow(graficInfoLayout);

    sortDataText.setText(getApp().getStringResources().getCResource("sortDataText"));
    sortDataText.setWrapStatus(true);
    sortDataText.setTrancparencyOutput(true);
    sortDataText.setColor(C_TRANSPARENT);
    graficInfoLayout.addWindow(sortDataText);

    logDataText.setText(getApp().getStringResources().getCResource("logDataText"));
    logDataText.setWrapStatus(true);
    logDataText.setTrancparencyOutput(true);
    logDataText.setColor(C_TRANSPARENT);
    graficInfoLayout.addWindow(logDataText);

    linDataText.setText(getApp().getStringResources().getCResource("linDataText"));
    linDataText.setWrapStatus(true);
    linDataText.setTrancparencyOutput(true);
    linDataText.setColor(C_TRANSPARENT);
    graficInfoLayout.addWindow(linDataText);

}


void MainCoorLinLayout::initCoorSys()
{
    // Добавляем строки в ресурсы
    getApp().getStringResources().addCResource(StringResources::Russian, "topWndAxisX", "Размер массива");
    getApp().getStringResources().addCResource(StringResources::English, "topWndAxisX", "Array size");

    getApp().getStringResources().addCResource(StringResources::Russian, "topWndAxisY", "Количество сравнений");
    getApp().getStringResources().addCResource(StringResources::English, "topWndAxisY", "Number of comparisons");

    getApp().getStringResources().addCResource(StringResources::Russian, "bottomWndAxisX", "Размер массива");
    getApp().getStringResources().addCResource(StringResources::English, "bottomWndAxisX", "Array size");

    getApp().getStringResources().addCResource(StringResources::Russian, "bottomWndAxisY", "Количество обменов");
    getApp().getStringResources().addCResource(StringResources::English, "bottomWndAxisY", "Number of exchanges");

    addWindow(topWnd);
    topWnd.setCCells({ (double)topWndScale, topWndScale * log(topWndScale) });
    topWnd.setMatchParentX(true);
    topWnd.setAxisXName(getApp().getStringResources().getCResource("topWndAxisX"));
    topWnd.setAxisYName(getApp().getStringResources().getCResource("topWndAxisY"));

    addWindow(bottomWnd);
    bottomWnd.setCCells({ (double)bottomWndScale, bottomWndScale * log(bottomWndScale) });
    bottomWnd.setMatchParentX(true);
    bottomWnd.setAxisXName(getApp().getStringResources().getCResource("bottomWndAxisX"));
    bottomWnd.setAxisYName(getApp().getStringResources().getCResource("bottomWndAxisY"));

    topWnd.addLay();
    topWnd.addLay();

    bottomWnd.addLay();
    bottomWnd.addLay();
}


void MainCoorLinLayout::initDescribtions()
{
    // Добавляем строки в ресурсы
    getApp().getStringResources().addCResource(StringResources::Russian, "computationStatus", "Идут вычисления...");
    getApp().getStringResources().addCResource(StringResources::English, "computationStatus", "Calculations are ongoing...");

    // Добавляем строки в ресурсы
    getApp().getStringResources().addCResource(StringResources::Russian, "comparison", "Сравнение:");
    getApp().getStringResources().addCResource(StringResources::English, "comparison", "Comparison:");

    onPartDescribtion(topFncCmpLayout, topHandle, topLogFnc, topLinFnc);
    onPartDescribtion(bottomFncCmpLayout, bottomHandle, bottomLogFnc, bottomLinFnc);

    computionStatusText.setText(getApp().getStringResources().getCResource("computationStatus"));
    computionStatusText.setWrapStatus(true);
    computionStatusText.setTrancparencyOutput(true);
    addWindow(computionStatusText);
}

void MainCoorLinLayout::onPartDescribtion(LinearLayout& _layout, TextView& handle, TextView& _logFnc, TextView& _linFnc)
{
    addWindow(_layout);

    handle.setColor(C_TRANSPARENT);
    handle.setTrancparencyOutput(true);
    handle.setWrapStatus(true);
    handle.setText(getApp().getStringResources().getCResource("comparison"));
    handle.setFormat(DT_LEFT);
    _layout.addWindow(handle);

    _linFnc.setColor(C_TRANSPARENT);
    _linFnc.setTrancparencyOutput(true);
    _linFnc.setWrapStatus(true);
    _linFnc.setText(""); // Если нужно добавить текст, добавьте его сюда
    _linFnc.setFormat(DT_LEFT);
    _layout.addWindow(_linFnc);

    _logFnc.setColor(C_TRANSPARENT);
    _logFnc.setTrancparencyOutput(true);
    _logFnc.setWrapStatus(true);
    _logFnc.setText(""); // Если нужно добавить текст, добавьте его сюда
    _logFnc.setFormat(DT_LEFT);
    _layout.addWindow(_logFnc);
}


string MainCoorLinLayout::logOddsToString(Vector _odd)
{
    string answer = {};
    answer = to_string(_odd.x) + "*x*log(" + to_string(_odd.y) + "*x)";
    return answer;
}

string MainCoorLinLayout::linOddsToString(Vector _odd)
{
    string answer = {};
    answer = to_string(_odd.x) + "*x + " + to_string(_odd.y);
    return answer;
}


void MainCoorLinLayout::startComputations()
{
    makeSortDataPoints();

    monteCarlo(topGradientLinOdds, topWnd, &MainCoorLinLayout::linfnc);
    monteCarlo(topGradientLogOdds, topWnd, &MainCoorLinLayout::logfnc);
                                                                            
    monteCarlo(bottomGradientLinOdds, bottomWnd, &MainCoorLinLayout::linfnc);
    monteCarlo(bottomGradientLogOdds, bottomWnd, &MainCoorLinLayout::logfnc);

    gradientDescentOddsComputation();

    drawGradientOdds(topGradientLinOdds, topWnd, &MainCoorLinLayout::linfnc, gradientLinColor, linOddsLayIndex);
    drawGradientOdds(topGradientLogOdds, topWnd, &MainCoorLinLayout::logfnc, gradientLogColor, logOddsLayIndex);

    drawGradientOdds(bottomGradientLinOdds, bottomWnd, &MainCoorLinLayout::linfnc, gradientLinColor, linOddsLayIndex);
    drawGradientOdds(bottomGradientLogOdds, bottomWnd, &MainCoorLinLayout::logfnc, gradientLogColor, logOddsLayIndex);

    invalidateButton();

    isActiveComputingPart = false;

    getApp().getStringResources().addCResource(StringResources::Russian, "noBackgroundProcesses", "Фоновых процессов нет");
    getApp().getStringResources().addCResource(StringResources::English, "noBackgroundProcesses", "No background processes");

    computionStatusText.setText(getApp().getStringResources().getCResource("noBackgroundProcesses"));
}   

void MainCoorLinLayout::makeSortDataPoints()
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
}

void MainCoorLinLayout::monteCarlo(Vector& _odds, MultiLayCoordinatSystemWindow& _wnd, double (*fnc) (double k, double b, double x))
{
    Vector oddsRange = { -20, 20 };
    size_t oddsPresision = 1;

    Vector currOdds = _odds;

    Vector bestOdds = _odds;
    double currMinQuadraticDelta = DBL_MAX;

    int cIterations = (int)1e5;
    for (int i = 0; i < cIterations; i++)
    {
        currOdds.x = app->generateRandom(oddsRange, oddsPresision);
        currOdds.y = app->generateRandom(oddsRange, oddsPresision);

        double quadraticDelta = computeQuadraticDelta(currOdds.x, currOdds.y, _wnd, fnc);

        if (quadraticDelta < currMinQuadraticDelta)
        {
            currMinQuadraticDelta = quadraticDelta;
            bestOdds = currOdds;
        }
    }

    _odds = bestOdds;
}

void MainCoorLinLayout::gradientDescentOddsComputation()
{
    getApp().getStringResources().addCResource(StringResources::Russian, "fitted", "Подошло ");
    getApp().getStringResources().addCResource(StringResources::English, "fitted", "Fitted ");
    getApp().getStringResources().addCResource(StringResources::Russian, "withDeviation", "с отклонением всего");
    getApp().getStringResources().addCResource(StringResources::English, "withDeviation", "with a total deviation of");

    double topLinDelta = gradientDescent(topGradientLinOdds, topWnd, &MainCoorLinLayout::linfnc, linLearningRate);
    static string topLogText = linOddsToString(topGradientLinOdds) + " " + getApp().getStringResources().getCResource("withDeviation") + " " + to_string(topLinDelta);
    topLogText.insert(0, getApp().getStringResources().getCResource("fitted"));
    topLinFnc.setText(topLogText.c_str());

    double topDelta = gradientDescent(topGradientLogOdds, topWnd, &MainCoorLinLayout::logfnc, logLearningRate);
    static string topGradientText = logOddsToString(topGradientLogOdds) + " " + getApp().getStringResources().getCResource("withDeviation") + " " + to_string(topDelta);
    topGradientText.insert(0, getApp().getStringResources().getCResource("fitted"));
    topLogFnc.setText(topGradientText.c_str());

    double bottomLinDelta = gradientDescent(bottomGradientLinOdds, bottomWnd, &MainCoorLinLayout::linfnc, linLearningRate);
    static string bottomLinText = linOddsToString(bottomGradientLinOdds) + " " + getApp().getStringResources().getCResource("withDeviation") + " " + to_string(bottomLinDelta);
    bottomLinText.insert(0, getApp().getStringResources().getCResource("fitted"));
    bottomLinFnc.setText(bottomLinText.c_str());

    double bottomLogDelta = gradientDescent(bottomGradientLogOdds, bottomWnd, &MainCoorLinLayout::logfnc, logLearningRate);
    static string bottomLogText = logOddsToString(bottomGradientLogOdds) + " " + getApp().getStringResources().getCResource("withDeviation") + " " + to_string(bottomLogDelta);
    bottomLogText.insert(0, getApp().getStringResources().getCResource("fitted"));
    bottomLogFnc.setText(bottomLogText.c_str());
}


double MainCoorLinLayout::gradientDescent(Vector& _odds, MultiLayCoordinatSystemWindow& _wnd, double (*fnc) (double k, double b, double x), Vector learning_rate)
{
    Vector gradientDelta = { 0.1, 0.1 };
    int iterations = 10000;
    for (int i = 0; i < iterations; i++)
    {
        if (!app->getAppCondition()) break;
        double currQuadraticDelta = computeQuadraticDelta(_odds.x, _odds.y, _wnd, fnc);
        double dxQuadraticDelta = computeQuadraticDelta(_odds.x + gradientDelta.x, _odds.y, _wnd, fnc);
        double dyQuadraticDelta = computeQuadraticDelta(_odds.x, _odds.y + gradientDelta.y, _wnd, fnc);

        double xDerivative = (dxQuadraticDelta - currQuadraticDelta) / gradientDelta.x;
        double yDerivative = (dyQuadraticDelta - currQuadraticDelta) / gradientDelta.y;

        _odds.x -= learning_rate.x * xDerivative;
        _odds.y -= learning_rate.y * yDerivative;
        //printf("");
    }
    //printf("");

    //cout << "На сортировку лучше всего ложится: " << oddsToString(_odds) << endl;

    double finalQuadraticDelta = computeQuadraticDelta(_odds.x, _odds.y, _wnd, fnc);

    return finalQuadraticDelta;
}

void MainCoorLinLayout::drawGradientOdds(Vector _odds, MultiLayCoordinatSystemWindow& wnd, double (*fnc) (double k, double b, double x), COLORREF graficColor, size_t layIndex)
{
    for (int i = 0; i < maxArrLen; i++)
    {
        if (!app->getAppCondition()) break;
        Vector newPoint = { (double)i, fnc(_odds.x, _odds.y, i) };

        wnd.addPoint(newPoint, graficColor, 0, layIndex, false);
    }
    wnd.invalidateButton();
}

double MainCoorLinLayout::computeQuadraticDelta(double k, double b, MultiLayCoordinatSystemWindow& wnd, double (*fnc) (double k, double b, double x))
{
    double answer = 0;
    int len = maxArrLen;
    for (int currLen = 1; currLen < len; currLen++)
    {       
        if (!app->getAppCondition()) break;
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
    topFncCmpLayout.MoveWindowTo(topWnd.rect.pos);
    bottomFncCmpLayout.MoveWindowTo(bottomWnd.rect.pos);

    Vector newPos = topWnd.rect.pos;
    newPos.x = topWnd.rect.finishPos.x - graficInfoLayout.getSize().x;
    graficInfoLayout.MoveWindowTo(newPos);

    Vector statusTextPos = getSize();
    statusTextPos.x = 0;
    statusTextPos.y -= computionStatusText.getSize().y;

    computionStatusText.MoveWindowTo(statusTextPos);

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