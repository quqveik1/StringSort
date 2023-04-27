// StringSort.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <sstream>

void readText(const std::string& path, std::string* originalfile);
int findEOLsN_(const std::string& text);
void fromOneCharToStrings(const std::string& text, std::string ptext[]);
void copyOriginalTextForSort(std::string* textLines, std::string** startToBackLines, int len);
void bubbleTextSort(std::string** lines, int len, int (*cmp)(const void* str1, const void* str2));
void textSort(std::string** lines, int len, int (*cmp)(const void* str1, const void* str2));
void printLines(std::string** str, int len);
int startToBackCmp(const void* str1, const void* str2);
int backToStartCmp(const void* str1, const void* str2);
void saveText(std::string** str, int len, const char* path);
void saveText(std::string** str, int len, std::ofstream& stream);
void workWithText();
int getNextAlnumPos(const std::string& strs, int startIndex, int maxSize, int incrementDelta);
void save3TextsOriginalFnc(const char* path, 
                           std::string** startToBackLines, int startToBackLinesLen, 
                           std::string** backToStartLines, int backToStartLinesLen,
                           const std::string& fullText);
bool isalnumRus(unsigned char c);

int main()
{
    //std::locale::global(std::locale(""));
    setlocale(LC_ALL, "russian");
    setlocale(LC_NUMERIC, "english");

    bool res = isalnumRus(255);
    bool res2 = isalnum((unsigned char)'ÿ');
    //drawQuickSortResults();
    workWithText();
}

void workWithText()
{
    std::string path = "RusOnegin.txt";

    std::string fulltext;
    readText(path, &fulltext);

    int stramount = findEOLsN_(fulltext) + 1;

    std::string* textLines = new std::string[stramount]{};
    fromOneCharToStrings(fulltext, textLines);

    std::string** startToBackLines = new std::string * [stramount] {};
    copyOriginalTextForSort(textLines, startToBackLines, stramount);
    textSort(startToBackLines, stramount, startToBackCmp);

    std::string** backToStartLines = new std::string * [stramount] {};
    copyOriginalTextForSort(textLines, backToStartLines, stramount);
    textSort(backToStartLines, stramount, backToStartCmp);

    save3TextsOriginalFnc("3Text.txt", startToBackLines, stramount, backToStartLines, stramount, fulltext);

    delete[] textLines;
    delete[] startToBackLines;
    delete[] backToStartLines;
}

bool isalnumRus(unsigned char c)
{
    if (c >= 192 && c <= 255)
    {
        return true;
    }
    else
    {
        return isalnum(c);
    }
}

void save3TextsOriginalFnc(const char* path, 
                           std::string** startToBackLines, int startToBackLinesLen, 
                           std::string** backToStartLines, int backToStartLinesLen, 
                           const std::string& fullText)
{
    std::ofstream stream(path);
    if (stream.is_open())
    {
        stream << "Start to back sorted text:\n";
        saveText(startToBackLines, startToBackLinesLen, stream);

        stream << "\n-------------------------------------------------------------------------------------";
        stream << "\nBack to start sorted text:\n";
        saveText(backToStartLines, backToStartLinesLen, stream);

        stream << "\n-------------------------------------------------------------------------------------";
        stream << "\nOriginalText:\n";
        stream << fullText;
    }
    stream.close();
}

void saveText(std::string** str, int len, std::ofstream& stream)
{
    if (stream.is_open())
    {
        for (int i = 0; i < len; i++)
        {
            stream << i << ": \"" << *(str[i]) << "\"\n";
        }
    }
}

void saveText(std::string** str, int len, const char* path)
{
    std::ofstream stream(path);

    if (stream.is_open())
    {
        for (int i = 0; i < len; i++)
        {
            stream << i << ": \"" << *(str[i]) << "\"\n";
        }
    }
    stream.close();
}

void printLines(const std::string** str, int len)
{
    for (int i = 0; i < len; i++)
    {
        std::cout << i << ": \"" << *(str[i]) << "\"\n";
    }
}



void copyOriginalTextForSort(std::string* textLines, std::string** startToBackLines, int len)
{
    for (int i = 0; i < len; i++)
    {
        startToBackLines[i] = &(textLines[i]);
    }
}


int backToStartCmp(const void* str1, const void* str2)
{
    std::string* _str1 = *((std::string**)str1);
    std::string* _str2 = *((std::string**)str2);
    int len1 = (int)_str1->length();
    int len2 = (int)_str2->length();
    int lenDelta = len2 - len1;

    int minLen = std::min(len1, len2);
    int index1 = len1 - 1;
    int index2 = len2 - 1;
    for (int i = 1; i <= minLen; i++)
    {
        index1 = getNextAlnumPos(*_str1, index1, len1, -1);
        index2 = getNextAlnumPos(*_str2, index2, len2, -1);

        if (index1 == -1 || index2 == -1) break;
        int delta = (*_str1)[index1] - (*_str2)[index2];

        index1--;
        index2--;
        if (delta != 0)
        {
            return delta;
        }
    }

    if (lenDelta != 0)
    {
        return lenDelta;
    }

    return 0;
}

int startToBackCmp(const void* str1, const void* str2)
{
    std::string* _str1 = *((std::string**)str1);
    std::string* _str2 = *((std::string**)str2);
    int len1 = (int)_str1->length();
    int len2 = (int)_str2->length();
    int lenDelta = len2 - len1;

    int minLen = std::min(len1, len2);
    int index1 = 0;
    int index2 = 0;
    for (int i = 0; i < minLen; i++)
    {
        index1 = getNextAlnumPos(*_str1, index1, len1, 1);
        index2 = getNextAlnumPos(*_str2, index2, len2, 1);

        if (index1 == -1 || index2 == -1) break;
        int delta = (*_str1)[index1] - (*_str2)[index2];

        index1++;
        index2++;

        if (delta != 0)
        {
            return delta;
        } 
    }

    if (lenDelta != 0)
    {
        return lenDelta; 
    }

    return 0;
}

int getNextAlnumPos(const std::string& strs, int startIndex, int maxSize, int incrementDelta)
{
    int answer = -1;

    for (int i = startIndex; i < maxSize && i >= 0; i += incrementDelta)
    {
        if (isalnum((unsigned char)strs[i]))
        {
            return i;
        }
    }

    return answer;
}

void textSort(std::string** lines, int len, int (*cmp)(const void* str1, const void* str2))
{
    qsort(lines, len, sizeof(std::string*), cmp);

}

void bubbleTextSort(std::string** lines, int len, int (*cmp)(const void* str1, const void* str2))
{

    for (int j = 0; j < len; j++)
    {
        for (int i = 0; i < len - j - 1; i++)
        {
            int delta = (*cmp) (&lines[i], &lines[i + 1]);

            if (delta > 0)
            {
                std::string* temp = lines[i];
                lines[i] = lines[i + 1];
                lines[i + 1] = temp;
            }
        }
    }
}


void fromOneCharToStrings(const std::string& text, std::string ptext[])
{
    int nlines = 0;
    int start = 0;

    for (int i = 0;; i++)
    {
        if (text[i] == '\0')
        {
            //ptext[nlines] = new std::string{};
            ptext[nlines] = text.substr(start, i - start);
            return;
        }
        if (text[i] == '\n')
        {
            ptext[nlines] = text.substr(start, i - start);
            nlines++;
            start = i + 1;

        }

    }
}

void readText(const std::string& path, std::string* originalfile)
{
    std::ifstream file(path);
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    std::stringstream stream;

    stream << file.rdbuf();

    *originalfile = stream.str();

    file.close();
}


int findEOLsN_(const std::string& text)
{
    int nStr = 0;
    for (int i = 0; ; i++)
    {
        if (text[i] == '\n')
        {
            nStr++;


        }
        if (text[i] == '\0')
        {
            return nStr;
        }
    }
    return nStr;
}