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
        long fileSize = app->getFileSize(faqFile);
        faqText.reset(new char[fileSize]);

        fread(faqText.get(), sizeof(char), fileSize, faqFile);

        app->messageBox(faqText.get(), text);
    }

}