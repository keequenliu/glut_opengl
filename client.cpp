#include "client.h"
#include "shader.h"
#include <stdio.h>

//GLfloat g_vertexBufferData[]={-25.0f,-25.0f,0.0f,
//                              25.0f,-25.0f,0.0f,
//                              0.0f,25.0f,0.0f
//                             };

GLfloat g_vertexBufferData[]={-1.0f,-1.0f,0.0f,
                              1.0f,-1.0f,0.0f,
                              0.0f,1.0f,0.0f
                             };


Client* Client::s_client=NULL;

Client::Client()
    :m_vertexArrayID(0)
    ,m_vertexBuffer(0)
{

}

Client::~Client()
{

}

bool Client::init(int*argc,char ** argv)
{
    glutInit(argc,argv);
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_ALPHA );
    glutInitWindowPosition( 100, 100 );
    glutInitWindowSize( 800, 600 );
    glutCreateWindow("glut-opengl");

    if(glewInit()!=GLEW_OK)
    {
        fprintf(stderr,"Fail to initialize GLEW \n");
        return false;
    }
    s_client=this;
    /** init GL **/
    glClearColor(0.0f,0.0f,0.4f,0.0f);

    /** register glut method **/
    registerClient();

    /** test method **/
    initVertexBuffer();
//    g_initVertexBuffer();
#ifdef KEE_SHADER
    m_programID=Shader::loadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");
#endif

    return true;
}

void Client::start()
{
    glutMainLoop();
}

void Client::registerClient()
{
    glutDisplayFunc         ( frame );           // this is where we render
    glutReshapeFunc         ( reshape );
    glutMouseFunc           ( mousebutton );
    glutMotionFunc          ( mousemove );
    glutKeyboardFunc        ( keyboard);
    //    glutSpecialFunc         (SpecialKeyHandle);
}

void Client::release()
{
    if(m_vertexBuffer)
        glDeleteBuffers(1,&m_vertexBuffer);
    if(m_vertexArrayID)
        glDeleteVertexArrays(1,&m_vertexArrayID);
}


void Client::initVertexBuffer()
{
//    static  GLfloat g_vertexBufferData[]={-1.0f,-1.0f,0.0f,
//                                          1.0f,-1.0f,0.0f,
//                                          0.0f, 1.0f,0.0f};

    //    //create verter array (VAO mode)
    glGenVertexArrays(1,&m_vertexArrayID);
    glBindVertexArray(m_vertexArrayID);

    //create vertex buffer,copy from memory to GL buffer
    glGenBuffers(1,&m_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER,m_vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,sizeof(g_vertexBufferData),g_vertexBufferData,GL_STATIC_DRAW);
}

#if 0
// normal VBO
void Client::drawVertexBuffer()
{
    glEnableClientState(GL_VERTEX_ARRAY);

    glVertexPointer(3,GL_FLOAT,0,0);
    glDrawArrays(GL_TRIANGLES,0,sizeof(g_vertexBufferData)/sizeof(GLfloat));

    glDisableClientState(GL_VERTEX_ARRAY);
}
#else

void Client::drawVertexBuffer()
{

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,m_vertexBuffer);
    glVertexAttribPointer(0,        // attribute 0. No particular reason for 0, but must match the layout in the shader.
                          3,        //size ,one vertex size,x,y,z in here
                          GL_FLOAT, //type
                          GL_FALSE, //normalized
                          0,        //stride
                          (void *)0 //array buffer offset,start 0
                          );

    glDrawArrays(GL_TRIANGLES,0,3);

    glDisableVertexAttribArray(0);
}
#endif

void Client::drawRect()
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

}


/** ------------------- static register method ------------------------- **/

void Client::frame()
{
    glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);

#ifdef KEE_SHADER
    //use shader
    glUseProgram(s_client->m_programID);
#endif

    s_client->drawVertexBuffer();

//    s_client->drawRect();
    glutSwapBuffers();
    //    glutPostRedisplay();
}

void Client::reshape(int width,int height)
{
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    GLdouble aspect	= (GLdouble)width/(GLdouble)height;
    GLdouble left	= -1.0f;
    GLdouble right	= 1.0f;
    GLdouble bottom	= -1.0f;
    GLdouble top	= 1.0f;

    if(aspect < 1.0)
    {
        bottom 	/= aspect;
        top		/= aspect;
    }
    else
    {
        left	*= aspect;
        right	*= aspect;
    }

    glOrtho(left, right, bottom, top, -1.0, 1.0);

    //    double mat[16];
    //    glGetDoublev(GL_PROJECTION_MATRIX,mat);
    //    printMat(mat);

    glutPostRedisplay();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Client::mousebutton( int button, int state, int x, int y )
{}

void Client::mousemove( int x, int y )
{

}
void Client::keyboard( unsigned char key, int x, int y )
{
    switch(key)
    {
    case 27:
    {
        s_client->release();
        exit(0);
    }
    break;
    }
}


//print mat[4x4]
void Client::printMat(double *mat)
{
    for(int i=0;i<16;i++)
    {
        fprintf(stderr,"%f\t ",mat[i]);
        if((i+1)%4 ==0)
        {
            fprintf(stderr,"\n");
        }
    }
}
