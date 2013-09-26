#ifndef CUBE_H
#define CUBE_H
#include "BaseModel.h"

class Cube:public BaseModel
{
public:
    Cube();
    void load();
    void draw();
    void release();
};

#endif // CUBE_H
