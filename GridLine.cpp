#include "GridLine.h"

GridLine::GridLine()
{
}


void GridLine::load()
{}

void DrawNet(GLfloat size, GLint LinesX, GLint LinesZ)
{
        glBegin(GL_LINES);
        for (int xc = 0; xc < LinesX; xc++)
        {
                glVertex3f(	-size / 2.0 + xc / (GLfloat)(LinesX-1)*size,
                                        0.0,
                                        size / 2.0);
                glVertex3f(	-size / 2.0 + xc / (GLfloat)(LinesX-1)*size,
                                        0.0,
                                        size / -2.0);
        }
        for (int zc = 0; zc < LinesX; zc++)
        {
                glVertex3f(	size / 2.0,
                                        0.0,
                                        -size / 2.0 + zc / (GLfloat)(LinesZ-1)*size);
                glVertex3f(	size / -2.0,
                                        0.0,
                                        -size / 2.0 + zc / (GLfloat)(LinesZ-1)*size);
        }
        glEnd();
}

void GridLine::draw()
{
    glTranslatef(0.0,0.8,0.0);

    glScalef(3.0,1.0,3.0);

    GLfloat size = 2.0;
    GLint LinesX = 30;
    GLint LinesZ = 30;

    GLfloat halfsize = size / 2.0;
    glColor3f(1.0,1.0,1.0);
    glPushMatrix();
            glTranslatef(0.0,-halfsize ,0.0);
            DrawNet(size,LinesX,LinesZ);
            glTranslatef(0.0,size,0.0);
            DrawNet(size,LinesX,LinesZ);
    glPopMatrix();
    glColor3f(0.0,0.0,1.0);
    glPushMatrix();
            glTranslatef(-halfsize,0.0,0.0);
            glRotatef(90.0,0.0,0.0,halfsize);
            DrawNet(size,LinesX,LinesZ);
            glTranslatef(0.0,-size,0.0);
            DrawNet(size,LinesX,LinesZ);
    glPopMatrix();
    glColor3f(1.0,0.0,0.0);
    glPushMatrix();
            glTranslatef(0.0,0.0,-halfsize);
            glRotatef(90.0,halfsize,0.0,0.0);
            DrawNet(size,LinesX,LinesZ);
            glTranslatef(0.0,size,0.0);
            DrawNet(size,LinesX,LinesZ);
    glPopMatrix();
}
void GridLine::release()
{}
