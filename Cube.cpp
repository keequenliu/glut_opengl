#include "Cube.h"
#include <GL/glut.h>

Cube::Cube()
{
}

void Cube::load()
{}

void Cube::draw()
{
    glutWireCube(10.0f);
}

void Cube::release()
{

}
