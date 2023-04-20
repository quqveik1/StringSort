// StringSort.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <cctype>

using namespace std;
void readText(const string& path, string* originalfile);
int findEOLsN_(const string& text);
void fromOneCharToStrings(const string& text, string ptext[]);
void copyOriginalTextForSort(string* textLines, string** startToBackLines, int len);
void bubbleTextSort(string** lines, int len, int (*cmp)(const void* str1, const void* str2));
void textSort(string** lines, int len, int (*cmp)(const void* str1, const void* str2));
void printLines(string** str, int len);
int startToBackCmp(const void* str1, const void* str2);
int backToStartCmp(const void* str1, const void* str2);
void saveText(string** str, int len, const char* path);
void saveText(string** str, int len, ofstream& stream);
void workWithText();
int getNextAlnumPos(const string& strs, int startIndex, int maxSize, int incrementDelta);
void save3TextsOriginalFnc(const char* path, 
                           string** startToBackLines, int startToBackLinesLen, 
                           string** backToStartLines, int backToStartLinesLen,
                           const string& fullText);


int main()
{
    //drawQuickSortResults();
    workWithText();
}

void workWithText()
{
    string path = "RusOnegin.txt";


    string fulltext;
    readText(path, &fulltext);

    int stramount = findEOLsN_(fulltext) + 1;

    string* textLines = new string[stramount]{};
    fromOneCharToStrings(fulltext, textLines);

    string** startToBackLines = new string * [stramount] {};
    copyOriginalTextForSort(textLines, startToBackLines, stramount);
    textSort(startToBackLines, stramount, startToBackCmp);

    string** backToStartLines = new string * [stramount] {};
    copyOriginalTextForSort(textLines, backToStartLines, stramount);
    textSort(backToStartLines, stramount, backToStartCmp);

    /*

    cout << "Start to back sorted text:\n";
    printLines(startToBackLines, stramount);

    cout << "Back to start sorted text:\n";
    printLines(backToStartLines, stramount);

    saveText(startToBackLines, stramount, "startToBackLines.txt");
    saveText(backToStartLines, stramount, "backToStartText.txt");
    */

    save3TextsOriginalFnc("3Text.txt", startToBackLines, stramount, backToStartLines, stramount, fulltext);

    delete[] textLines;
    delete[] startToBackLines;
    delete[] backToStartLines;
}

void save3TextsOriginalFnc(const char* path, 
                           string** startToBackLines, int startToBackLinesLen, 
                           string** backToStartLines, int backToStartLinesLen, 
                           const string& fullText)
{
    ofstream stream(path);
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

void saveText(string** str, int len, ofstream& stream)
{
    if (stream.is_open())
    {
        for (int i = 0; i < len; i++)
        {
            stream << i << ": \"" << *(str[i]) << "\"\n";
        }
    }
}

void saveText(string** str, int len, const char* path)
{
    ofstream stream(path);

    if (stream.is_open())
    {
        for (int i = 0; i < len; i++)
        {
            stream << i << ": \"" << *(str[i]) << "\"\n";
        }
    }
    stream.close();
}

void printLines(const string** str, int len)
{
    for (int i = 0; i < len; i++)
    {
        cout << i << ": \"" << *(str[i]) << "\"\n";
    }
}



void copyOriginalTextForSort(string* textLines, string** startToBackLines, int len)
{
    for (int i = 0; i < len; i++)
    {
        startToBackLines[i] = &(textLines[i]);
    }
}


int backToStartCmp(const void* str1, const void* str2)
{
    string* _str1 = *((string**)str1);
    string* _str2 = *((string**)str2);
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
    string* _str1 = *((string**)str1);
    string* _str2 = *((string**)str2);
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

int getNextAlnumPos(const string& strs, int startIndex, int maxSize, int incrementDelta)
{
    int answer = -1;

    for (int i = startIndex; i < maxSize && i >= 0; i += incrementDelta)
    {
        if (isalnum(strs[i]))
        {
            return i;
        }
    }

    return answer;
}

void textSort(string** lines, int len, int (*cmp)(const void* str1, const void* str2))
{
    qsort(lines, len, sizeof(string*), cmp);

}

void bubbleTextSort(string** lines, int len, int (*cmp)(const void* str1, const void* str2))
{

    for (int j = 0; j < len; j++)
    {
        for (int i = 0; i < len - j - 1; i++)
        {
            int delta = (*cmp) (&lines[i], &lines[i + 1]);

            if (delta > 0)
            {
                string* temp = lines[i];
                lines[i] = lines[i + 1];
                lines[i + 1] = temp;
            }
        }
    }
}


void fromOneCharToStrings(const string& text, string ptext[])
{
    int nlines = 0;
    int start = 0;

    for (int i = 0;; i++)
    {
        if (text[i] == '\0')
        {
            //ptext[nlines] = new string{};
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

void readText(const string& path, string* originalfile)
{
    struct stat buff;
    stat(path.c_str(), &buff);

    int filesize = buff.st_size;


    originalfile->reserve(filesize + 1);

    FILE* file = fopen(path.c_str(), "r");
    for (int i = 0; i < filesize; i++)
    {           
        char nextChar = getc(file);
        if (nextChar != EOF)
        {
            originalfile->push_back(nextChar);
        }
        else
        {
            break;
        }
    }
    fclose(file);

}


int findEOLsN_(const string& text)
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