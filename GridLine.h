#ifndef GRIDLINE_H
#define GRIDLINE_H

#include "BaseModel.h"

class GridLine:public BaseModel
{
public:
    GridLine();
    void load();
    void draw();
    void release();
};

#endif // GRIDLINE_H
