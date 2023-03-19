#pragma once

#include <TextView.h>

struct GraphicInfoButton : TextView
{
    GraphicInfoButton(AbstractAppData* _app) : 
        TextView(_app)
    {
    }
    virtual void onClick(Vector mp) override;
};
