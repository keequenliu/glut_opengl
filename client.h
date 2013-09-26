#ifndef CLIENT_H
#define CLIENT_H

#include <GL/glew.h>
#include <GL/glut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "BaseModel.h"
#include "Camera.h"

class Client
{
public:
    Client();
    ~Client();
    /** model must not null ***/
    bool init(int*argc,char ** argv,BaseModel *model);
    void start();

    static void frame();
    static void reshape(int width,int height);
    static void mousebutton( int button, int state, int x, int y );
    static void mousemove( int x, int y );
    static void keyboard( unsigned char key, int x, int y );
    static void specialKeyHandle(int key, int x, int y );
    //print mat[4x4]
    static void printMat(double *mat);
private:
    void release();
    void registerClient();
    void projectViewModel();

    BaseModel* m_model;
#ifdef KEE_SHADER
    GLuint m_programID;
#endif
    GLuint m_matrixID;
    glm::mat4 m_mvp;
    static Client* s_client;

    Camera2 m_camera;
};

#endif // CLIENT_H
