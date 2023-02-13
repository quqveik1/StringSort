#pragma once

void quickSort(void* arr, int elementSize, const int left, const int right, int (*cmp)(const void* str1, const void* str2));
void quickSort(void* arr, int len, int elementSize, int (*cmp)(const void* str1, const void* str2));

void exchange(void* a, void* b, int elementSize);

