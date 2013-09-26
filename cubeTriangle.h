#ifndef CUBETRIANGLE_H
#define CUBETRIANGLE_H

#include "BaseModel.h"

class cubeTriangle:public BaseModel
{
public:
    cubeTriangle();
    void load();
    void draw();
    void release();
};

#endif // CUBETRIANGLE_H
