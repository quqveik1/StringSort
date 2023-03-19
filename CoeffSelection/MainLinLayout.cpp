#pragma once
#include "MainLinLayout.h"
#include <thread>
#include <LinearLayout.cpp>
#include <iostream>


double MainLinLayout::currOriginalK = 5;
double MainLinLayout::currOriginalB = 7;

MainLinLayout::MainLinLayout(AbstractAppData* _app, Vector _startPos) :
    LinearLayout(_app, _startPos, LinearLayout::FLAG_VERTICAL),
    topSystem(_app),
    bottomSystem(_app),
    downLinLayout(_app, {}, LinearLayout::FLAG_HORIZONTAL),
    backGroundComputation(_app),
    suggestedCoeff(_app),
    answerCoeff(_app),
    topDescribtions(_app, {},  LinearLayout::FLAG_VERTICAL),
    topDescribtion1(_app),
    topDescribtion2(_app),
    topDescribtion3(_app),
    bottomDescribtions(_app, {}, LinearLayout::FLAG_VERTICAL),
    bottomDescribtion1(_app),
    bottomDescribtion2(_app),
    graphicInfoButton(_app)
{
    initCoordinats();

    initDescribtions();

    initDownLinLayout();

    startGradientComputation();
}

void MainLinLayout::initCoordinats()
{
    topSystem.setCCells({ 20, 20 });
    topSystem.pixNullPercantage = { 0.5, 0.5 };
    topSystem.onSize({}, { 0, 0, 50, 500 });
    topSystem.setAxisXName("X");
    topSystem.setAxisYName("Y");

    //LinearLayoutInfo* topInfo = new LinearLayoutInfo();
    static LinearLayoutInfo topInfo;
    topInfo.margin = Rect{ 0, 0, 0, 10 };
    topSystem.setLayoutInfo(&topInfo);

    topSystem.setMatchParentX(true);
    addWindow(topSystem);


    bottomSystem.setCellNull({ 0, 6.8 });
    bottomSystem.setCCells({ 12, 0.5 });
    bottomSystem.onSize({}, { 0, 0, 50, 500 });
    bottomSystem.setMatchParentX(true);
    bottomSystem.setOnClickListener(this);
    bottomSystem.setAxisXName("K");
    bottomSystem.setAxisYName("B");
    addWindow(bottomSystem);
}

void MainLinLayout::initDescribtions()
{
    addWindow(topDescribtions);

    topDescribtion1.setColor(C_TRANSPARENT);
    topDescribtion1.needTransparencyOutput = true;
    topDescribtion1.setFont(20);
    topDescribtion1.setWrapStatus(1);
    topDescribtion1.setFormat(DT_LEFT);
    topDescribtion1.setText("����� - ������������ ������");
    topDescribtions.addWindow(topDescribtion1);

    topDescribtion2.setColor(C_TRANSPARENT);
    topDescribtion2.needTransparencyOutput = true;
    topDescribtion2.setFont(20);
    topDescribtion2.setWrapStatus(1);
    topDescribtion2.setFormat(DT_LEFT);
    topDescribtion2.setText("������� - ���������� ������");
    topDescribtions.addWindow(topDescribtion2);

    topDescribtion3.setColor(C_TRANSPARENT);
    topDescribtion3.needTransparencyOutput = true;
    topDescribtion3.setFont(20);
    topDescribtion3.setWrapStatus(1);
    topDescribtion3.setFormat(DT_LEFT);
    topDescribtion3.setText("������� - ������, ����������� �� ������� ��� �������������");
    topDescribtions.addWindow(topDescribtion3);



    addWindow(bottomDescribtions);

    bottomDescribtion1.setColor(C_TRANSPARENT);
    bottomDescribtion1.needTransparencyOutput = true;
    bottomDescribtion1.setFont(20);
    bottomDescribtion1.setWrapStatus(1);
    bottomDescribtion1.setFormat(DT_LEFT);
    bottomDescribtion1.setText("����� - ����������� ����������");
    bottomDescribtions.addWindow(bottomDescribtion1);

    bottomDescribtion2.setColor(C_TRANSPARENT);
    bottomDescribtion2.needTransparencyOutput = true;
    bottomDescribtion2.setFont(20);
    bottomDescribtion2.setFormat(DT_LEFT);
    bottomDescribtion2.setWrapStatus(1);
    bottomDescribtion2.setText("������� - ������� ���������� ����������");
    bottomDescribtions.addWindow(bottomDescribtion2);
}


void MainLinLayout::initDownLinLayout()
{
    addWindow(downLinLayout);

    backGroundComputation.setText("��� ������� �����");
    backGroundComputation.setFont(30);
    backGroundComputation.setWrapStatus(1);
    downLinLayout.addWindow(backGroundComputation);

    static char suggestedCoeffText[MAX_PATH]{};
    Vector suggestedCoefVector = { currOriginalK, currOriginalB };
    sprintf(suggestedCoeffText, "���������� ����������: %s", suggestedCoefVector.getStr());
    suggestedCoeff.setText(suggestedCoeffText);
    suggestedCoeff.setFont(30);
    suggestedCoeff.setWrapStatus(1);
    downLinLayout.addWindow(suggestedCoeff);

    answerCoeff.setText("������ ���� ���");
    answerCoeff.setFont(30);
    answerCoeff.setWrapStatus(1);
    downLinLayout.addWindow(answerCoeff);

    graphicInfoButton.setText("��� ��� �� �������?");
    graphicInfoButton.setFont(30);
    graphicInfoButton.setWrapStatus(1);
    downLinLayout.addWindow(graphicInfoButton);
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
        Vector copySize = onWindowMovingCopyDC.getSize(); 
        M_HDC& _outputDC = *getOutputDC();
        Vector currSize = _outputDC.getSize();
        app->stretchBlt(_outputDC, { .pos = {}, .finishPos = currSize }, onWindowMovingCopyDC, { .pos = {}, .finishPos = copySize });
        //cout << currSize.toString() << "|CopySize:" << copySize.toString()<<endl;

        //app->DEBUGsaveImage(_outputDC, "_outputDC");
        //app->DEBUGsaveImage(onWindowMovingCopyDC, "onWindowMovingCopyDC");
    }
    int timeAfter = clock();
    int delta = timeAfter - timeBefore;

    //cout << "��������� ������: " << delta << "��\n";
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
    topSystem.clearSys();
    countOriginalFnc();
    if(wasAnswerFinded) countFncOnTopSystem(answerK, answerB, suggestedFncColor);
    countFncOnTopSystem(clickedCellPos.x, clickedCellPos.y, userSelectedFncColor);
    invalidateButton();
    //cout << "MainLinLayout::onCertainPointSelectionEndDraw\n";

}

int MainLinLayout::onEnterWindowSizeMove()
{
    int res = LinearLayout::onEnterWindowSizeMove();

    M_HDC& outputDC = *getOutputDC();
    Vector currSize = outputDC.getSize();

    onWindowMovingCopyDC.setSize(currSize, app);
    app->bitBlt(onWindowMovingCopyDC, {}, outputDC);

    //cout << "onEnterWindowSizeMove|CopySize:" << currSize.getStr() << endl;


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
    int res1 = LinearLayout::onSize(managerSize, _newRect);
    Vector _size = getSize();
    downLineSize = _size * 0.1;
    downLineSize.x = _size.x;



    topSystem.onSize(_size, { 0, 0, topSystem.getSize().x, (_size.y - downLineSize.y) * 0.5 });



    bottomSystem.onSize(_size, { 0, 0, bottomSystem.getSize().x, (_size.y - downLineSize.y) * 0.5 });                                                                                                                     

    downLinLayout.onSize(_size, { {}, downLineSize });

    int res2 = LinearLayout::onSize(managerSize, _newRect);

    topDescribtions.MoveWindowTo(topSystem.rect.pos);
    bottomDescribtions.MoveWindowTo(bottomSystem.rect.pos);
    downLinLayout.MoveWindowTo({ bottomSystem.rect.pos.x, bottomSystem.rect.finishPos.y });

    return res2 + res1;
}

double MainLinLayout::originalSinFnc(double x)
{
    return sinFnc(currOriginalK, currOriginalB, x);
}

double MainLinLayout::sinFnc(double k, double b, double x)
{
    /// k - A, B - f(�������)
    return k * sin(b * x);
}

void MainLinLayout::threadCoeffFinder(double* k, double* b, Vector& kBound, Vector& bBound, double(*fnc)(double k, double b, double x), double (*originalFnc)(double x))
{
    //bottomSystem.clearSys();
    //topSystem.clearSys();

    double minQuadraticDelta = DBL_MAX;
    int detalisationK = 1000;
    int kDelta = abs(kBound.delta()) * detalisationK;
    double kStart = kBound.x * detalisationK;

    int bDelta = abs(bBound.delta()) * detalisationK;
    double bStart = bBound.x * detalisationK;

    Vector topCellXBound = topSystem.getXCellBound();
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
        bottomSystem.addPoint(point, quadraticDeltaColor);
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
    Vector topCellXBound = topSystem.getXCellBound();
    double topCellXBoundLen = topCellXBound.delta();
    double xDelta = abs(topCellXBoundLen / 1000);

    for (double x = topCellXBound.x; x < topCellXBound.y; x += xDelta)
    {
        if (!app->getAppCondition()) break;
        double fncRes = sinFnc(k, b, x);
        Vector newPoint = { x, fncRes };
        topSystem.addPoint(newPoint, _color);
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

    //cout << "������� ���� ����� �����: " << delta << "��\n";
}

void MainLinLayout::countGradientMap()
{
    double k = 0, b = 0;
    Vector kBound = { 0, 10 }; //k = A - ��������� ��������� A = 5
    Vector bBound = { 6.8, 7.2 }; // b = f - ����  ��������� f = 7
    backGroundComputation.setText("������ ���������");
    threadCoeffFinder(&answerK, &answerB, kBound, bBound, &MainLinLayout::sinFnc, &MainLinLayout::originalSinFnc);
    backGroundComputation.setText("��� ������� �����");
    static char ans[MAX_PATH] = {};
    Vector answerVector = { answerK, answerB };
    sprintf(ans, "���������� �����������: %s", answerVector.getStr());
    answerCoeff.setText(ans);
    invalidateButton();
}
