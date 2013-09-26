#ifndef KEETRIANGLE_H
#define KEETRIANGLE_H


#include "BaseModel.h"

/** draw triangle **/
class keeTriangle:public BaseModel
{
public:
    keeTriangle();

    void load();
    void draw();
    void release();

private:
    GLuint m_vertexArrayID;
};

#endif // KEETRIANGLE_H
