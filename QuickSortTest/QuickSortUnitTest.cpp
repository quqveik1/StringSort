#pragma once 
#include "QuickSortUnitTest.h"
#include "..\QuickSort.cpp"
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "StringSortEngine.cpp"

void drawQuickSortResults()
{
    StringSortEngine engine;
    engine.startApp();
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
