#ifndef CLIENT_H
#define CLIENT_H

#include <GL/glew.h>
#include <GL/glut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Client
{
public:
    Client();
    ~Client();

    bool init(int*argc,char ** argv);
    void start();
    void release();

    static void frame();
    static void reshape(int width,int height);
    static void mousebutton( int button, int state, int x, int y );
    static void mousemove( int x, int y );
    static void keyboard( unsigned char key, int x, int y );
    //print mat[4x4]
    static void printMat(double *mat);
private:
    void registerClient();


    void initVertexBuffer();
    void drawVertexBuffer();
    void drawRect();
#ifdef KEE_SHADER
    GLuint m_programID;
#endif
    GLuint m_vertexBuffer;
    GLuint m_vertexArrayID;

    static Client* s_client;

};

#endif // CLIENT_H
