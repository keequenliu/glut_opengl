#include "keeTriangle.h"
#include "shader.h"

//GLfloat g_vertexBufferData[]={-25.0f,-25.0f,0.0f,
//                              25.0f,-25.0f,0.0f,
//                              0.0f,25.0f,0.0f
//                             };

GLfloat g_vertexBufferData[]={-1.0f,-1.0f,0.0f,
                              1.0f,-1.0f,0.0f,
                              0.0f,1.0f,0.0f
                             };

keeTriangle::keeTriangle()
{

}

void keeTriangle::load()
{
    //create verter array (VAO mode)
    glGenVertexArrays(1,&m_vertexArrayID);
    glBindVertexArray(m_vertexArrayID);

    //create vertex buffer,copy from memory to GL buffer
    glGenBuffers(1,&m_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER,m_vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,sizeof(g_vertexBufferData),g_vertexBufferData,GL_STATIC_DRAW);
}

#if 0
// normal VBO
void keeTriangle::draw()
{
    glEnableClientState(GL_VERTEX_ARRAY);

    glVertexPointer(3,GL_FLOAT,0,0);
    glDrawArrays(GL_TRIANGLES,0,sizeof(g_vertexBufferData)/sizeof(GLfloat));

    glDisableClientState(GL_VERTEX_ARRAY);
}
#else

void keeTriangle::draw()
{
        glBegin(GL_LINES);
        glVertex2d(-1,-1);
        glVertex2d(1,1);
        glEnd();

        glBegin(GL_TRIANGLES);
        glVertex3d(-1.0f,-1.0f,0.0f);
        glVertex3d( 1.0f,-1.0f,0.0f);
        glVertex3d(0.0f, 1.0f,0.0f);
        glEnd();

//    glEnableVertexAttribArray(0);
//    glBindBuffer(GL_ARRAY_BUFFER,m_vertexBuffer);
//    glVertexAttribPointer(0,        // attribute 0. No particular reason for 0, but must match the layout in the shader.
//                          3,        //size ,one vertex size,x,y,z in here
//                          GL_FLOAT, //type
//                          GL_FALSE, //normalized
//                          0,        //stride
//                          (void *)0 //array buffer offset,start 0
//                          );

//    glDrawArrays(GL_TRIANGLES,0,3);

//    glDisableVertexAttribArray(0);
}
#endif

void keeTriangle::release()
{
    if(m_vertexBuffer)
        glDeleteBuffers(1,&m_vertexBuffer);
    if(m_vertexArrayID)
        glDeleteVertexArrays(1,&m_vertexArrayID);
}


//void Client::drawRect()
//{
//    glBegin(GL_LINES);
//    glVertex2d(-1,-1);
//    glVertex2d(1,1);
//    glEnd();

//    glBegin(GL_TRIANGLES);
//    glVertex3d(-1.0f,-1.0f,0.0f);
//    glVertex3d( 1.0f,-1.0f,0.0f);
//    glVertex3d(0.0f, 1.0f,0.0f);
//    glEnd();

//}


