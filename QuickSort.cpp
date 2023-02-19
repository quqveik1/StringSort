#pragma once
#include "QuickSort.h"
#include "SortStatistic.h"



void quickSort(void* arr, int len, int elementSize, int (*cmp)(const void* obj1, const void* obj2))
{
    setCCmps(0);
    setCExchanges(0);
    quickSort((char*)arr, elementSize, 0, len - 1, cmp);
}


void quickSort(char* arr, int elementSize, const int left, const int right, int (*cmp)(const void* obj1, const void* obj2))
{
    int len = (right - left) + 1;
    int currLeft = left;
    int currRight = right;
    int midIndex = (right + left) / 2;
    char* midNum = &(arr[getByteIndex(midIndex, elementSize)]);

    if (1 >= len)
    {
        return;
    }

    if (len == 2)
    {
        int leftByte = getByteIndex(left, elementSize);
        int rightByte = getByteIndex(right, elementSize);
        if (cmp( &( arr[leftByte] ), &(arr[rightByte])) > 0)
        {
            exchange(arr, left, right, elementSize, &midIndex, &midNum);
        }
        return;
    }

    if (len == 3)
    {
        sort3(arr, left, elementSize, &midIndex, &midNum, cmp);
        return;
    }


    for (;;)
    {
        if (currRight - currLeft <= 0) break;
        if (cmp(&( arr[getByteIndex(currLeft, elementSize)] ), midNum) >= 0)
        {
            while (cmp(midNum, &( arr[getByteIndex(currRight, elementSize)] )) < 0)
            {
                if (currRight - currLeft <= 0) break;
                currRight--;

            }
            if (currRight - currLeft <= 0) break;
            exchange(arr, currLeft, currRight, elementSize, &midIndex, &midNum);
            currLeft++;
            currRight--;
            continue;
        }
        currLeft++;
    }

    if (cmp(&( arr[getByteIndex(currRight, elementSize)] ), midNum) > 0)
    {
        quickSort(arr, elementSize, left, currRight - 1, cmp);
        quickSort(arr, elementSize, currRight, right, cmp);
    }
    else
    {
        quickSort(arr, elementSize, left, currRight, cmp);
        quickSort(arr, elementSize, currRight + 1, right, cmp);
    }

}

void sort3(char* arr, int fElement, int elementSize, int* midIndex, char** minIndexptr, int (*cmp)(const void* obj1, const void* obj2))
{
    int index0 = getByteIndex(fElement, elementSize);
    int index1 = getByteIndex(fElement + 1, elementSize);
    int index2 = getByteIndex(fElement + 2, elementSize);
    if (cmp(&( arr[index0] ), &( arr[index2] )) > 0)
    {
        exchange(arr, fElement, fElement + 2, elementSize, midIndex, minIndexptr);
    }
    if (cmp(&(arr[index0]), &(arr[index1])) > 0)
    {
        exchange(arr, fElement, fElement + 1, elementSize, midIndex, minIndexptr);
    }
    if (cmp(&(arr[index1]), &(arr[index2])) > 0)
    {
        exchange(arr, fElement + 1, fElement + 2, elementSize, midIndex, minIndexptr);
    }
}

int getByteIndex(int index, int elementSize)
{
    return index * elementSize;
}



void exchange(char* a, char* b, int elementSize)
{
    char t = 0;
    getCExchanges()++;
    for (int i = 0; i < elementSize; i++)
    {
        t = a[i];
        a[i] = b[i];
        b[i] = t;
    }
}


void exchange(char* arr, int fIndex, int sIndex, int elementSize, int* midIndex, char** minIndexptr)
{
    exchange(&arr[getByteIndex(fIndex, elementSize)], &arr[getByteIndex(sIndex, elementSize)], elementSize);

    if (fIndex == *midIndex)
    {
        (*minIndexptr) = &arr[getByteIndex(sIndex, elementSize)];
        *midIndex = sIndex;
    }
    else if (sIndex == *midIndex)
    {
        (*minIndexptr) = &arr[getByteIndex(fIndex, elementSize)];
        *midIndex = fIndex;
    }

}


int cmpInt(const void* a, const void* b)
{
    getCCmps()++;
    return (*(int*)a) - (*(int*)b);
}
