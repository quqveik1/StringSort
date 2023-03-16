#pragma once
#include "MainLinLayout.h"
#include <thread>
#include <LinearLayout.cpp>
#include <iostream>


double MainLinLayout::currOriginalK = 5;
double MainLinLayout::currOriginalB = 7;

MainLinLayout::MainLinLayout(AbstractAppData* _app, Vector _startPos) :
    LinearLayout(_app, _startPos, LinearLayout::FLAG_VERTICAL),
    downLinLayout(_app, {}, LinearLayout::FLAG_HORIZONTAL),
    backGroundComputation(_app),
    suggestedCoeff(_app),
    answerCoeff(_app)
{

    ColorfullCoordinatSystemWindow* topCoordinatSystemWindow = new ColorfullCoordinatSystemWindow(app);
    topCoordinatSystemWindow->setCCells({ 20, 20 });
    topCoordinatSystemWindow->pixNullPercantage = { 0.5, 0.5 };
    topCoordinatSystemWindow->onSize({}, { 0, 0, 50, 500 });

    setTopSystem(topCoordinatSystemWindow);
    LinearLayoutInfo* topInfo = new LinearLayoutInfo();
    topInfo->margin = Rect{ 0, 0, 0, 10 };
    topCoordinatSystemWindow->setLayoutInfo(topInfo);

    topCoordinatSystemWindow->setMatchParentX(true);
    addWindow(topCoordinatSystemWindow);

    ColorfullCoordinatSystemWindow* bottomCoordinatSystemWindow = new ColorfullCoordinatSystemWindow(app);
    bottomCoordinatSystemWindow->setCellNull({ 0, 6.8 });
    bottomCoordinatSystemWindow->setCCells({ 12, 0.5 });
    bottomCoordinatSystemWindow->onSize({}, { 0, 0, 50, 500 });
    bottomCoordinatSystemWindow->setMatchParentX(true);
    bottomCoordinatSystemWindow->setOnClickListener(this);
    setBottomSystem(bottomCoordinatSystemWindow);
    addWindow(bottomCoordinatSystemWindow);


    addWindow(downLinLayout);

    backGroundComputation.setText("Нет фоновых задач");
    backGroundComputation.setFont(40);
    backGroundComputation.setWrapStatus(1);
    downLinLayout.addWindow(backGroundComputation);

    static char suggestedCoeffText[MAX_PATH]{};
    Vector suggestedCoefVector = { currOriginalK, currOriginalB };
    sprintf(suggestedCoeffText, "Загаданный коэффицент: %s", suggestedCoefVector.getStr());
    suggestedCoeff.setText(suggestedCoeffText);
    suggestedCoeff.setFont(40);
    suggestedCoeff.setWrapStatus(1);
    downLinLayout.addWindow(suggestedCoeff);

    answerCoeff.setText("Ответа пока нет");
    answerCoeff.setFont(40);
    answerCoeff.setWrapStatus(1);
    downLinLayout.addWindow(answerCoeff);

    startGradientComputation();
    
}

void MainLinLayout::draw()
{
    int timeBefore = clock();
    bool isMainWindowMoving = app->isWindowMoving();
    if (!isMainWindowMoving)
    {

        LinearLayout::draw();
    }
    else
    {
        Vector currSize = getSize();
        Vector copySize = onWindowMovingCopyDC.getSize(); 
        M_HDC& _outputDC = *getOutputDC();
        app->stretchBlt(_outputDC, { .pos = {}, .finishPos = currSize }, onWindowMovingCopyDC, { .pos = {}, .finishPos = copySize });
        cout << currSize.getStr() << ":" << currSize.getStr()<<endl;
    }
    int timeAfter = clock();
    int delta = timeAfter - timeBefore;

    //cout << "Рисование заняло: " << delta << "мс\n";
}



void MainLinLayout::onMessageRecieve(const char* name, void* data)
{
    Vector clickedCellPos = *(Vector*)data;
    //thread  userPointSelection(&MainLinLayout::onCertainPointSelection, this, clickedCellPos);
    //userPointSelection.detach();
    onCertainPointSelection(clickedCellPos);
}

void MainLinLayout::onCertainPointSelection(Vector clickedCellPos)
{
    topSystem->clearSys();
    countOriginalFnc();
    if(wasAnswerFinded) countFncOnTopSystem(answerK, answerK, suggestedFncColor);
    countFncOnTopSystem(clickedCellPos.x, clickedCellPos.y, userSelectedFncColor);
    invalidateButton();
    cout << "MainLinLayout::onCertainPointSelectionEndDraw\n";

}

int MainLinLayout::onEnterWindowSizeMove()
{
    int res = LinearLayout::onEnterWindowSizeMove();

    M_HDC& outputDC = *getOutputDC();
    Vector currSize = outputDC.getSize();

    onWindowMovingCopyDC.setSize(currSize, app);
    app->bitBlt(onWindowMovingCopyDC, {}, outputDC);


    return res;
}

int MainLinLayout::onExitWindowSizeMove()
{
    int res = LinearLayout::onExitWindowSizeMove();
    invalidateButton();

    return res;
}

int MainLinLayout::onSize(Vector managerSize, Rect _newRect)
{
    int res = LinearLayout::onSize(managerSize, _newRect);
    Vector _size = getSize();
    downLineSize = _size * 0.1;
    downLineSize.x = _size.x;

    


    if (topSystem)
    {
        topSystem->onSize(_size, { 0, 0, topSystem->getSize().x, (_size.y - downLineSize.y) * 0.5 });
    }

    if (bottomSystem)
    {
        bottomSystem->onSize(_size, { 0, 0, bottomSystem->getSize().x, (_size.y - downLineSize.y) * 0.5 });                                                   
    }                                                                            

    backGroundComputation.onSize(_size, { {}, downLineSize });



    return LinearLayout::onSize(managerSize, _newRect);
}

double MainLinLayout::originalSinFnc(double x)
{
    return sinFnc(currOriginalK, currOriginalB, x);
}

double MainLinLayout::sinFnc(double k, double b, double x)
{
    /// k - A, B - f(частота)
    return k * sin(b * x);
}

void MainLinLayout::threadCoeffFinder(double* k, double* b, Vector& kBound, Vector& bBound, double(*fnc)(double k, double b, double x), double (*originalFnc)(double x))
{
    if (bottomSystem) bottomSystem->clearSys();
    if (topSystem) topSystem->clearSys();

    double minQuadraticDelta = DBL_MAX;
    int detalisationK = 1000;
    int kDelta = abs(kBound.delta()) * detalisationK;
    double kStart = kBound.x * detalisationK;

    int bDelta = abs(bBound.delta()) * detalisationK;
    double bStart = bBound.x * detalisationK;

    Vector topCellXBound = topSystem->getXCellBound();
    double topCellXBoundLen = topCellXBound.delta();

    for (int i = 0; i < cCountingCoef; i++)
    {
        if (!app->getAppCondition()) break;
        double currQuadraticDelta = 0;
        double _k = ((rand() % kDelta) + kStart) / detalisationK;
        double _b = ((rand() % bDelta) + bStart) / detalisationK;
        double xDelta = abs(topCellXBoundLen / cQuadraticDeltaCountingPoints);

        for (double x = topCellXBound.x; x < topCellXBound.y; x += xDelta)
        {
            double quadraticDelta = calcQuadratic(_k, _b, x, fnc, originalFnc);
            currQuadraticDelta += quadraticDelta;
        }

        if (isBigger(minQuadraticDelta, currQuadraticDelta))
        {
            minQuadraticDelta = currQuadraticDelta;
            *k = _k;
            *b = _b;
        }

        COLORREF quadraticDeltaColor = getQuadraticDeltaColor(currQuadraticDelta);
        Vector point = { _k, _b };
        bottomSystem->addPoint(point, quadraticDeltaColor);
    }
    wasAnswerFinded = true;
    countFncOnTopSystem(*k, *b, suggestedFncColor);

    invalidateButton();
    cout << "FinishedCountGraientMap\n";
}

COLORREF MainLinLayout::getQuadraticDeltaColor(double quadraticDelta)
{
    const double maxQuadraticDelta = 204;
    const double minQuadraticDelta = 0.03;
    const double rangeDelta = maxQuadraticDelta - minQuadraticDelta;
    const int r0 = 0;
    const int r1 = 255;

    const int g0 = 0;
    const int g1 = 0;

    const int b0 = 255;
    const int b1 = 0;

    double t = (quadraticDelta - minQuadraticDelta) / rangeDelta;

    int r2 = r0 + (double)(r1 - r0) * t;
    int g2 = 0;
    int b2 = b0 + (double)(b1 - b0) * t;


    COLORREF answer = RGB(r2, g2, b2);
    return answer;
}

double MainLinLayout::calcQuadratic(double k, double b, double x, double(*fnc)(double k, double b, double x), double (*originalFnc)(double x))
{
    double dy = fnc(k, b, x) - originalFnc(x);
    return (dy * dy);
}

void MainLinLayout::countOriginalFnc()
{
    countFncOnTopSystem(currOriginalK, currOriginalB);
};

void MainLinLayout::countFncOnTopSystem(double k, double b, COLORREF _color/* = NULL*/)
{
    Vector topCellXBound = topSystem->getXCellBound();
    double topCellXBoundLen = topCellXBound.delta();
    double xDelta = abs(topCellXBoundLen / 1000);

    for (double x = topCellXBound.x; x < topCellXBound.y; x += xDelta)
    {
        if (!app->getAppCondition()) break;
        double fncRes = sinFnc(k, b, x);
        Vector newPoint = { x, fncRes };
        topSystem->addPoint(newPoint, _color);
    }
    invalidateButton();
}


void MainLinLayout::startGradientComputation()
{
    int timeStart = clock();

    thread executeThread(&MainLinLayout::countGradientMap, this);
    executeThread.detach();

    thread originalFncThread(&MainLinLayout::countOriginalFnc, this);
    originalFncThread.detach();

    int timeFinish = clock();

    int delta = timeFinish - timeStart;

    //cout << "Подсчет всех точек занял: " << delta << "мс\n";
}

void MainLinLayout::countGradientMap()
{
    double k = 0, b = 0;
    Vector kBound = { 0, 10 }; //k = A - амплитуда идеальное A = 5
    Vector bBound = { 6.8, 7.2 }; // b = f - фаза  идеальное f = 7
    backGroundComputation.setText("Расчет градиента");
    threadCoeffFinder(&answerK, &answerB, kBound, bBound, &MainLinLayout::sinFnc, &MainLinLayout::originalSinFnc);
    backGroundComputation.setText("Нет фоновых задач");
    static char ans[MAX_PATH] = {};
    Vector answerVector = { answerK, answerB };
    sprintf(ans, "Отгаданный Коэффициент: %s", answerVector.getStr());
    answerCoeff.setText(ans);
}
