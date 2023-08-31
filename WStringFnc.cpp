//
// Created by Kurlic on 11.05.2023.
//
#pragma once
#include "WStringFnc.h"

#include <exception>

#include "StringCoding.cpp"


void workWithText(std::wstring path_str, std::wstring destFileName)
{
    //int res = _setmode(_fileno(stdout), _O_U16TEXT);

    std::wstring_view path = path_str;

    std::wstring_view fulltext(L"");
    readText(path, &fulltext);

    std::wstring_view* textLines = NULL;

    int stramount = separateTextByLinesToArr(fulltext, &textLines);

    std::wstring_view** startToBackLines = new std::wstring_view* [stramount] {};
    copyOriginalTextForSort(textLines, startToBackLines, stramount);
    textSort(startToBackLines, stramount, startToBackCmp);

    std::wstring_view** backToStartLines = new std::wstring_view* [stramount] {};
    copyOriginalTextForSort(textLines, backToStartLines, stramount);
    textSort(backToStartLines, stramount, backToStartCmp);

    save3TextsOriginalFnc(destFileName, startToBackLines, stramount, backToStartLines, stramount, textLines);

    delete[] textLines;
    delete[] startToBackLines;
    delete[] backToStartLines;
    delete fulltext.data();
}

int separateTextByLinesToArr(std::wstring_view& fullText, std::wstring_view** arr)
{
    int stramount = findEOLsN_(fullText) + 1;
    *arr = new std::wstring_view[stramount]{};
    fromOneCharToStrings(fullText, *arr);

    return stramount;
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

void save3TextsOriginalFnc(std::wstring& path,
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

template <typename TS>
void saveText(TS str, int len, std::ofstream& stream, bool needToMark/* = true*/)
{
    if (stream.is_open())
    {
        for (int i = 0; i < len; i++)
        {
            if(needToMark) stream << i << ": \"";
            saveString(str[i], stream);
            if (needToMark) stream << "\"\n";
            else
            {
                stream << "\n";
            }
        }
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
    std::wstring_view* _str1 = *((std::wstring_view**)str1);
    std::wstring_view* _str2 = *((std::wstring_view**)str2);
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

template<typename PATHSTR>
void readText(PATHSTR& path, std::wstring_view* originalfile)
{
    std::ifstream file(path.data());

    if (!file.is_open())
    {
        throw std::runtime_error("File wasn't opened");
    }

    std::stringstream stream;

    stream << file.rdbuf();
    file.close();

    std::string smallStr = stream.str();

    *originalfile = readStr(smallStr);
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
                ptext[nlines] = text.substr(start, (size_t)i - (size_t)start);
                return;
            }
            if (text[i] == '\n')
            {
                ptext[nlines] = text.substr(start, (size_t)i - (size_t)start);
                nlines++;
                start = i + 1;
            }
        }
    }
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
