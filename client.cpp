#include "client.h"
#include "shader.h"
#include <stdio.h>
#include <time.h>
#include <sys/time.h>

Client* Client::s_client=NULL;

Client::Client()
    :m_model(NULL)
{

}

Client::~Client()
{

}

bool Client::init(int*argc,char ** argv,BaseModel *model)
{
    glutInit(argc,argv);
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_ALPHA );
    glutInitWindowPosition( 100, 100 );
    glutInitWindowSize(1024, 768 );
    glutCreateWindow("glut-opengl");

    if(glewInit()!=GLEW_OK)
    {
        fprintf(stderr,"Fail to initialize GLEW \n");
        return false;
    }
    s_client=this;
    /** init GL **/
    glClearColor(0.2f,0.2f,0.4f,0.0f);
    glEnable(GL_TEXTURE_2D);

    /** register glut method **/
    registerClient();

    /** test method **/
    m_model=model;
    m_model->load();

#ifdef KEE_SHADER
    m_programID=Shader::loadShaders("vertex.txt", "fragment.txt");
    m_matrixID=glGetUniformLocation(m_programID,"MVP");
    projectViewModel();
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
    glutSpecialFunc         (specialKeyHandle);
}

void Client::projectViewModel()
{
    // Model matrix : an identity matrix (model will be at the origin)
    glm::mat4 modelMatrix=glm::mat4(1.0f);
    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    glm::mat4 projectMatrix = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    // Or, for an ortho camera :
    //glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

    // Camera matrix
    glm::mat4 viewMatrix       = glm::lookAt(
                glm::vec3(0,1,10), // Camera is at (4,3,3), in World Space
                glm::vec3(0,0,0), // and looks at the origin
                glm::vec3(0,1,0)) ; // Head is up (set to 0,-1,0 to look upside-down)
    // Our ModelViewProjection : multiplication of our 3 matrices
    m_mvp = projectMatrix * viewMatrix * modelMatrix; // Remember, matrix multiplication is the other way around

}

void Client::release()
{
    s_client->m_model->release();
}


/** ------------------- static register method ------------------------- **/

void Client::frame()
{
    //    time_t tt =time(NULL);
    //    tm* t=localtime(&tt);
    //    timeval val;
    //    struct timezone tz;
    //    gettimeofday(&val,&tz);



    glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);

#ifdef KEE_SHADER
    //use shader
    glUseProgram(s_client->m_programID);
    // Send our transformation to the currently bound shader,
    // in the "MVP" uniform
    glUniformMatrix4fv(s_client->m_matrixID, 1, GL_FALSE, &s_client->m_mvp[0][0]);
#endif
    //变换
    // Save the matrix state and do the rotations
    //    glPushMatrix();
    s_client->m_camera.render();


    glPushMatrix();
    glTranslatef(0.0,0.0f,-20.0f);
    s_client->m_model->draw();
    glutSwapBuffers();
    glutPostRedisplay();
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

    //        glOrtho(left, right, bottom, top, -1.0, 1.0);
    gluPerspective(45,aspect,1.0f,-10000.0f);

    //    double mat[16];
    //    glGetDoublev(GL_PROJECTION_MATRIX,mat);
    //    printMat(mat);

    glutPostRedisplay();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Client::mousebutton( int button, int state, int x, int y )
{

}

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
    case '1':
        s_client->m_model->setWireMode();
        break;
    case 'a':
        s_client->m_camera.rotateY(5.0);
        break;
    case 'd':
        s_client->m_camera.rotateY(-5.0);
        break;
    case 'w':
        s_client->m_camera.moveForwards( -0.1 ) ;
        break;
    case 's':
        s_client->m_camera.moveForwards( 0.1 ) ;
        break;

    case 'x':
        s_client->m_camera.rotateX(5.0);
        break;
    case 'y':
        s_client->m_camera.rotateX(-5.0);

        break;
    case 'c':
        s_client->m_camera.strafeRight(-0.1);

        break;
    case 'v':
        s_client->m_camera.strafeRight(0.1);

        break;
    case 'f':
        s_client->m_camera.moveUpForwards(-0.3);

        break;
    case 'r':
        s_client->m_camera.moveUpForwards(0.3);

        break;
    case 'm':
        s_client->m_camera.rotateZ(-5.0);
        break;
    case 'n':
        s_client->m_camera.rotateZ(5.0);
    case ' ':
        //        s_client->m_camera.reset();
        break;
    }

    glutPostRedisplay();
}

void Client::specialKeyHandle(int key, int x, int y )
{
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
