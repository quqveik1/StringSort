#pragma once 
#include "QuickSortUnitTest.h"
#include "QuickSort.cpp"
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "StringSortEngine.cpp"
//#include "..\ALGORITHMICPROJECT\Q_CoordinatSystem.h"

/*
void startQuickSortUnitTest()
{
    txCreateWindow(1000, 800);
    txSetTextAlign(TA_RIGHT);

    coordinatSys sys1{};
    sys1.startPosPix_ = { 0, 0 };
    sys1.finishPosPix_ = { 1000, 400 };
    sys1.nullCoor_ = { 40, 380 };

    coordinatSys sys2{};
    sys2.startPosPix_ = { 0, 400 };
    sys2.finishPosPix_ = { 1000, 800 };
    sys2.nullCoor_ = { 40, 780 };



    coordinatSysConfig conf;
    sys1.config_ = conf;

    sys1.intepretK_.y = -0.1;
    sys1.intepretK_.x = 1;
    sys1.drawAxis({ 10, 1 });


    sys2.intepretK_.y = -0.1;
    sys2.intepretK_.x = 1;
    sys2.drawAxis({ 10, 1 });


    const int len = 3000;
    int arr[len] = {};
    for (int i = 0; i < len; i++)
    {
        int sTime = time(NULL);
        srand(sTime);
        int testLen = rand() % len;
        printQuickSortUnitTest(arr, testLen, cmpInt);
    }
}

void drawSortPoint(int* arr, int len, int (*cmp)(const void* obj1, const void* obj2), coordinatSys* sys1, coordinatSys* sys2)
{
    randomFill(arr, len);
    quickSort(arr, len, sizeof(int), cmp);
    //sys1->drawCircle(getCCmps())

}
*/

void startQuickSortUnitTest()
{

}




void printQuickSortUnitTest(int* arr, int len, int (*cmp)(const void* obj1, const void* obj2))
{
    bool isPassed = testQuickSort(arr, len, cmp);
    if(!isPassed)
    {
        printf("Тест с массивом длинной %d прошел НЕУСПЕШНО\n", len);
        (void)_getch();
    }
}

bool testQuickSort(int* arr, int len, int (*cmp)(const void* obj1, const void* obj2))
{
    clearArr(arr, len);
    randomFill(arr, len);
    quickSort(arr, len, sizeof(int), cmp);
    return isSorted(arr, len, cmp);
}

bool isSorted(int* arr, int len, int (*cmp)(const void* obj1, const void* obj2))
{
    for (int i = 0; i < len - 1; i++)
    {
        if (cmp(&arr[i], &arr[i + 1]) > 0)
        {
            return false;
        }
    }
    return true;
}

void randomFill(int* arr, int len)
{
    for (int i = 0; i < len; i++)
    {
        arr[i] = rand();
    }
}

void clearArr(int* arr, int len)
{
    for (int i = 0; i < len; i++)
    {
        arr[i] = {};
    }
}




void startCornerUnitTest()
{
    char arr[10000] = {};
}
