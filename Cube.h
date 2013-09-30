#ifndef CUBE_H
#define CUBE_H
#include "BaseModel.h"
#include "Texture.h"

class Cube:public BaseModel
{
public:
    Cube();
    void load();
    void setWireMode();
    void draw();
    void release();
private:
    float m_size;
    bool m_wire;
    Texture m_texture;
};

#endif // CUBE_H
