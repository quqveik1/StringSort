#pragma once 
#include "QuickSortUnitTest.h"
#include "QuickSort.cpp"

void startQuickSortUnitTest()
{
    int arr[10000] = {};
    for (int i = 0; i < 10000; i++)
    {
        int testLen = rand() % 10000;
        printQuickSortUnitTest(arr, testLen, cmpInt);
    }
}




void printQuickSortUnitTest(int* arr, int len, int (*cmp)(const void* obj1, const void* obj2))
{
    bool isPassed = testQuickSort(arr, len, cmp);
    if (isPassed)
    {
        printf("Тест с массивом длинной %d прошел успешно\n", len);
    }
    else
    {
        printf("Тест с массивом длинной %d прошел НЕУСПЕШНО\n", len);
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


int cmpInt(const void* a, const void* b)
{
    return (*(int*)a) - (*(int*)b);
}