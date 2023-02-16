#pragma once
#include "QuickSort.h"

void startQuickSortUnitTest();
void printQuickSortUnitTest(int* arr, int len, int (*cmp)(const void* obj1, const void* obj2));
bool testQuickSort(int* arr, int len, int (*cmp)(const void* obj1, const void* obj2));
bool isSorted(int* arr, int len, int (*cmp)(const void* obj1, const void* obj2));
void randomFill(int* arr, int len);
void clearArr(int* arr, int len);
int cmpInt(const void* a, const void* b);