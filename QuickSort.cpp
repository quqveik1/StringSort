#pragma once
#include "QuickSort.h"


void quickSort(void* arr, int len, int elementSize, int (*cmp)(const void* str1, const void* str2))
{
    quickSort(arr, elementSize, 0, len - 1);
}


void quickSort(void* arr, int elementSize, const int left, const int right, int (*cmp)(const void* str1, const void* str2))
{
    int len = (right - left) + 1;
    int currLeft = left;
    int currRight = right;
    int midIndex = (right + left) / 2;
    void* midNum = &arr[midIndex * elementSize];

    if (1 >= len)
    {
        return;
    }

    if (len == 2)
    {
        if (arr[left] > arr[right])
        {
            exchange(arr[left], arr[right]);
        }
        return;
    }

    if (len == 3)
    {
        sort3(&arr[left]);
        return;
    }


    for (;;)
    {
        if (currRight - currLeft <= 0) break;
        if (arr[currLeft] >= midNum)
        {
            while (midNum < arr[currRight])
            {
                if (currRight - currLeft <= 0) break;
                currRight--;

            }
            exchange(arr[currLeft], arr[currRight], elementSize);
            currLeft++;
            currRight--;
            continue;
        }
        currLeft++;
    }
    if (arr[currRight] > midNum)
    {
        quickSort(arr, left, currRight - 1);
        quickSort(arr, currRight, right);
    }
    else
    {
        quickSort(arr, left, currRight);
        quickSort(arr, currRight + 1, right);
    }

}



void exchange(void* a, void* b, int elementSize)
{
    char t = 0;

    for (int i = 0; i < elementSize; i++)
    {
        t = a[i];
        b[i] = t;

    }
}