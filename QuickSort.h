#pragma once

void quickSort(char* arr, int elementSize, const int left, const int right, int (*cmp)(const void* obj1, const void* obj2));
void quickSort(void* arr, int len, int elementSize, int (*cmp)(const void* obj1, const void* obj2));
void testIntQuickSort(int* arr, int len);

void exchange(char* a, char* b, int elementSize);
void exchange(char* arr, int fIndex, int sIndex, int elementSize, int* midIndex, char** midindex);
int getByteIndex(int index, int elementSize);
void sort3(char* arr, int fElement, int elementSize, int* midIndex, char** minIndexptr, int (*cmp)(const void* obj1, const void* obj2));
int cmpInt(const void* a, const void* b);

