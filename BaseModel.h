#ifndef BASEMODEL_H
#define BASEMODEL_H

#include <GL/glew.h>

class BaseModel
{
public:
    BaseModel();
    virtual void load()=0;
    virtual void draw()=0;
    virtual void release()=0;

protected:
     GLuint m_vertexBuffer;
     GLuint m_colorBuffer;
};

#endif // BASEMODEL_H
