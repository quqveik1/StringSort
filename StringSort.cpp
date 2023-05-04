// StringSort.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <sstream>
#include <locale>
#include <Windows.h>
#include <vector>
#include <fcntl.h>
#include <io.h>
#include "QuickSort.cpp"

void readText(const std::wstring_view& path, std::wstring_view* originalfile);
int findEOLsN_(const std::wstring_view& text);
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
void saveText(std::wstring* str, int len, std::ofstream& stream);
void saveText(std::wstring_view* str, int len, std::ofstream& stream);
void saveString(const std::wstring_view& str, std::ofstream& stream);
void workWithText();
int getNextAlnumPos(const std::wstring_view& strs, int startIndex, int maxSize, int incrementDelta);
void save3TextsOriginalFnc(const char* path, 
                           std::wstring_view** startToBackLines, int startToBackLinesLen,
                           std::wstring_view** backToStartLines, int backToStartLinesLen,
                           std::wstring_view* fullTextLines);
bool isalnumRus(unsigned char c);

int main()
{
    workWithText();
}

void workWithText()
{
    int res = _setmode(_fileno(stdout), _O_U16TEXT);

    std::wstring_view path = L"Onegin.txt";
    
    std::wstring_view fulltext(L"");
    readText(path, &fulltext);

    int stramount = findEOLsN_(fulltext) + 1;

    std::wstring_view* textLines = new std::wstring_view[stramount]{};
    fromOneCharToStrings(fulltext, textLines);

    std::wstring_view** startToBackLines = new std::wstring_view* [stramount] {};
    copyOriginalTextForSort(textLines, startToBackLines, stramount);
    textSort(startToBackLines, stramount, startToBackCmp);

    std::wstring_view** backToStartLines = new std::wstring_view* [stramount] {};
    copyOriginalTextForSort(textLines, backToStartLines, stramount);
    textSort(backToStartLines, stramount, backToStartCmp);

    save3TextsOriginalFnc("3Text.txt", startToBackLines, stramount, backToStartLines, stramount, textLines);

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
                           std::wstring_view** startToBackLines, int startToBackLinesLen,
                           std::wstring_view** backToStartLines, int backToStartLinesLen,
                           std::wstring_view* fullTextLines)
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
        saveText(fullTextLines, startToBackLinesLen, stream);
    }
    stream.close();
}

void saveText(std::wstring_view** str, int len, std::ofstream& stream)
{
    if (stream.is_open())
    {
        for (int i = 0; i < len; i++)
        {
            stream << i << ": \"";
            saveString(*str[i], stream);
            stream << "\"\n";
        }
    }
} 
void saveText(std::wstring** str, int len, std::ofstream& stream)
{
    if (stream.is_open())
    {
        for (int i = 0; i < len; i++)
        {
            stream << i << ": \"";
            saveString(*str[i], stream);
            stream << "\"\n";
        }
    }
}
 
void saveText(std::wstring_view* str, int len, std::ofstream& stream)
{
    if (stream.is_open())
    {
        for (int i = 0; i < len; i++)
        {
            stream << i << ": \"";
            saveString(str[i], stream);
            stream << "\"\n";
        }
    }
}    

void saveText(std::wstring* str, int len, std::ofstream& stream)
{
    if (stream.is_open())
    {
        for (int i = 0; i < len; i++)
        {
            stream << i << ": \"";
            saveString(str[i], stream);
            stream << "\"\n";
        }
    }
}

void saveString(const std::wstring_view& str, std::ofstream& stream)
{
    static std::string byteString;
    int required_size = WideCharToMultiByte(CP_UTF8, 0, str.data(), str.size() + 1, 0, 0, 0, 0);
    if (required_size > 0)
    {
        std::vector<char> buffer(required_size);
        WideCharToMultiByte(CP_UTF8, 0, str.data(), str.size() + 1, &buffer[0], required_size, 0, 0);
        byteString = std::string(buffer.begin(), buffer.end() - 1);

        stream << byteString;
    }
}

void saveText(std::wstring** str, int len, const char* path)
{
    std::wofstream stream(path);

    if (stream.is_open())
    {
        for (int i = 0; i < len; i++)
        {
            stream << i << ": \"" << *(str[i]) << "\"\n";
        }
    }
    stream.close();
}

void printLines(const std::wstring** str, int len)
{
    for (int i = 0; i < len; i++)
    {
        std::wcout << i << ": \"" << *(str[i]) << "\"\n";
    }
}



void copyOriginalTextForSort(std::wstring_view* textLines, std::wstring_view** startToBackLines, int len)
{
    for (int i = 0; i < len; i++)
    {
        startToBackLines[i] = &(textLines[i]);
    }
}


int backToStartCmp(const void* str1, const void* str2)
{
    std::wstring_view* _str1 = *((std::wstring_view**)str1);
    std::wstring_view* _str2 = *((std::wstring_view**)str2);
    int len1 = (int)_str1->length();
    int len2 = (int)_str2->length();
    int lenDelta = len2 - len1;

    int minLen = min(len1, len2);
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
    std::wstring_view* _str1 = *((std::wstring_view**)str1);
    std::wstring_view* _str2 = *((std::wstring_view**)str2);
    int len1 = (int)_str1->length();
    int len2 = (int)_str2->length();
    int lenDelta = len2 - len1;

    int minLen = min(len1, len2);
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

int getNextAlnumPos(const std::wstring_view& strs, int startIndex, int maxSize, int incrementDelta)
{
    int answer = -1;

    for (int i = startIndex; i < maxSize && i >= 0; i += incrementDelta)
    {
        if (iswalnum(strs[i]))
        {
            return i;
        }
    }

    return answer;
}

void textSort(std::wstring_view** lines, int len, int (*cmp)(const void* str1, const void* str2))
{
    quickSort(lines, len, sizeof(std::wstring_view*), cmp);
}

void bubbleTextSort(std::wstring** lines, int len, int (*cmp)(const void* str1, const void* str2))
{

    for (int j = 0; j < len; j++)
    {
        for (int i = 0; i < len - j - 1; i++)
        {
            int delta = (*cmp) (&lines[i], &lines[i + 1]);

            if (delta > 0)
            {
                std::wstring* temp = lines[i];
                lines[i] = lines[i + 1];
                lines[i + 1] = temp;
            }
        }
    }
}


void fromOneCharToStrings(const std::wstring_view& text, std::wstring_view ptext[])
{
    int nlines = 0;
    int start = 0;

    for (int i = 0;; i++)
    {
        if (start <= i)
        {
            if (i == text.size())
            {
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
}

void readText(const std::wstring_view& path, std::wstring_view* originalfile)
{
    std::ifstream file(path.data());
    std::stringstream stream;

    stream << file.rdbuf();
    file.close();

    std::string smallStr = stream.str();

    int required_size = MultiByteToWideChar(CP_UTF8, 0, smallStr.c_str(), -1, nullptr, 0);
    std::vector<wchar_t> buffer(required_size);
    MultiByteToWideChar(CP_UTF8, 0, smallStr.c_str(), -1, &buffer[0], required_size);

    static std::wstring _str(buffer.begin(), buffer.end() - 1);

    *originalfile = _str;
}


int findEOLsN_(const std::wstring_view& text)
{
    int nStr = 0;
    for (int i = 0; ; i++)
    {
        if (text.size() == i)
        {
            return nStr;
        }
        if (text[i] == L'\n')
        {
            nStr++;
        }
    }
    return nStr;
}