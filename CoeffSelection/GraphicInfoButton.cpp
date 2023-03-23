#pragma once
#include "GraphicInfoButton.h" 
#include <fstream>


void GraphicInfoButton::onClick(Vector mp)
{
    TextView::onClick(mp);
    FILE* faqFile = fopen("Files\\FAQ.txt", "r");
    if (faqFile)
    {
        shared_ptr<char> faqText;
        int fileSize = app->getFileSize(faqFile) + 1;
        faqText.reset(new char[fileSize]);

        fread(faqText.get(), sizeof(char), fileSize, faqFile);
        fclose(faqFile);

        faqText.get()[fileSize] = 0;

        app->messageBox(faqText.get(), text);
    }

}