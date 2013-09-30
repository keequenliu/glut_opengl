#include "Cube.h"
#include <GL/glut.h>

Cube::Cube()
{
    m_size=5.0f;
    m_wire=false;
}

void Cube::load()
{
    m_texture.loadBMP("/home/liuqijun/keequen/glut_opengl/data/tex1.bmp");
}

void Cube::setWireMode()
{
    m_wire=!m_wire;
}

void Cube::draw()
{


    glColor3f(1.0f,0.0f,0.0f);
    m_wire?glBegin(GL_LINE_LOOP):glBegin(GL_QUADS);

    glVertex3f(-m_size,-m_size,-m_size);

    glVertex3f(-m_size,-m_size,m_size);

    glVertex3f(-m_size,m_size,m_size);

    glVertex3f(-m_size,m_size,-m_size);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    //right
    m_wire?glBegin(GL_LINE_LOOP):glBegin(GL_QUADS);
    glVertex3f(m_size,-m_size,-m_size);
    glVertex3f(m_size,-m_size,m_size);
    glVertex3f(m_size,m_size,m_size);
    glVertex3f(m_size,m_size,-m_size);
    glEnd();
    glColor3f(0.0f,1.0f,0.0f);
    //top
    m_wire?glBegin(GL_LINE_LOOP):glBegin(GL_QUADS);
    glVertex3f(-m_size,m_size,-m_size);
    glVertex3f(-m_size,m_size,m_size);
    glVertex3f(m_size,m_size,m_size);
    glVertex3f(m_size,m_size,-m_size);
    glEnd();
    //bottom
    m_wire?glBegin(GL_LINE_LOOP):glBegin(GL_QUADS);
    glVertex3f(-m_size,-m_size,-m_size);
    glVertex3f(-m_size,-m_size,m_size);
    glVertex3f(m_size,-m_size,m_size);
    glVertex3f(m_size,-m_size,-m_size);
    glEnd();
    glColor3f(0.0f,0.0f,1.0f);


//    glColor3f(0.0f,0.0f,1.0f);
    //back
    m_wire?glBegin(GL_LINE_LOOP):glBegin(GL_QUADS);
    glVertex3f(-m_size,-m_size,-m_size);
    glVertex3f(m_size,-m_size,-m_size);
    glVertex3f(m_size,m_size,-m_size);
    glVertex3f(-m_size,m_size,-m_size);
    glEnd();

    glEnable(GL_TEXTURE_2D);
    m_texture.setActive();
    //front
    m_wire?glBegin(GL_LINE_LOOP):glBegin(GL_QUADS);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-m_size,-m_size,m_size);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(m_size,-m_size,m_size);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(m_size,m_size,m_size);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-m_size,m_size,m_size);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void Cube::release()
{

}
