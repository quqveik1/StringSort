//
// Created by Kurlic on 11.05.2023.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <sstream>
#include <locale>
#include <vector>
#include <fcntl.h>
#include "QuickSort.cpp"

void workWithText(std::wstring path_str, std::wstring destFileName);

//you need to delete data from originalfile
void readText(const std::wstring_view& path, std::wstring_view* originalfile);
int findEOLsN_(const std::wstring_view& text);
int separateTextByLinesToArr(std::wstring_view& fullText, std::wstring_view** arr);
void fromOneCharToStrings(const std::wstring_view& text, std::wstring_view ptext[]);
void copyOriginalTextForSort(std::wstring_view* textLines, std::wstring_view** startToBackLines, int len);
void bubbleTextSort(std::wstring** lines, int len, int (*cmp)(const void* str1, const void* str2));
void textSort(std::wstring_view** lines, int len, int (*cmp)(const void* str1, const void* str2));
void printLines(std::wstring** str, int len);
int startToBackCmp(const void* str1, const void* str2);
int backToStartCmp(const void* str1, const void* str2);
void saveText(std::wstring** str, int len, const char* path);
void saveText(std::wstring** str, int len, std::ofstream& stream);
void saveText(std::wstring_view** str, int len, std::ofstream& stream);
void saveText(std::wstring* str, int len, std::ofstream& stream, bool needToMark = true);
void saveText(std::wstring_view* str, int len, std::ofstream& stream);
int getNextAlnumPos(const std::wstring_view& strs, int startIndex, int maxSize, int incrementDelta);
void save3TextsOriginalFnc(std::wstring& path,
                           std::wstring_view** startToBackLines, int startToBackLinesLen,
                           std::wstring_view** backToStartLines, int backToStartLinesLen,
                           std::wstring_view* fullTextLines);
bool isalnumRus(unsigned char c);