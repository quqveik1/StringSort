#pragma once
#include "GraphicInfoButton.h" 
#include <fstream>


void GraphicInfoButton::onClick(Vector mp)
{
    TextView::onClick(mp);

    char* outputText = app->readText("Files\\FAQ.txt");
    
    if (outputText)
    {
        app->messageBox(outputText, text);
        delete outputText;
    }

    /*
    FILE* faqFile = fopen("Files\\FAQ.txt", "r");
    if (faqFile)
    { 
        
        int fileSize = app->getFileSize(faqFile);
        faqText.reset(new char[fileSize]);

        int creadchar = fread(faqText.get(), sizeof(char), fileSize, faqFile);
        fclose(faqFile);

        if (creadchar < 0)
        {
            printf("Файл с описанием программы не считался\n");
        }

        faqText.get()[creadchar] = 0;
        

        shared_ptr<char> faqText;

        app->messageBox(faqText.get(), text);
    }
    */

}