#include "main.h"


GLfloat g_vertexBufferData[]={-25.0f,-25.0f,0.0f,
                              25.0f,-25.0f,0.0f,
                              0.0f,25.0f,0.0f
                             };
GLuint g_vertexBuffer;
void ConfigVertexBuffer()
{


    //    //create verter array (VAO mode)
    //    GLuint vertexArrayID;
    //    glGenVertexArrays(1,&vertexArrayID);
    //    glBindVertexArray(vertexArrayID);

    //create vertex buffer,copy memory to GL buffer
    glGenBuffers(1,&g_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER,g_vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,sizeof(g_vertexBufferData),g_vertexBufferData,GL_STATIC_DRAW);
}

void drawVertexBuffer()
{
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,g_vertexBuffer);
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

//-----------------shade-----------------------

GLuint g_programID;

GLuint loadShaders(const char* vertexFilePath,const char* fragmentFilePath)
{
    //create shaders
    GLuint vertexShaderID=glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderID=glCreateShader(GL_FRAGMENT_SHADER);

    //read the vertex shader code from the file
    std::string vertexShaderCode;
    std::ifstream vertexShaderStream(vertexFilePath,std::ios::in);
    if(vertexShaderStream.is_open())
    {
        std::string Line="";
        while(getline(vertexShaderStream,Line))
        {
            vertexShaderCode+="\n"+Line;

        }
        vertexShaderStream.close();
    }
    else
    {
        printf("open file : %s fail \n",vertexFilePath);
        return 0;
    }
    //read the fragment shader code from the file
    std::string fragmentShaderCode;
    std::ifstream fragmentShaderStream(fragmentFilePath,std::ios::in);
    if(fragmentShaderStream.is_open())
    {
        std::string Line="";
        while(getline(fragmentShaderStream,Line))
        {
            fragmentShaderCode+="\n"+Line;
        }
        fragmentShaderStream.close();
    }
    else
    {
        printf("open file : %s fail \n",fragmentFilePath);
        return 0;
    }

    GLint result=GL_FALSE;
    printf("compiling shader : %s \n",vertexFilePath);
        char const * vertexSourcePtr=vertexShaderCode.c_str();
    glShaderSource(vertexShaderID,          //id
                   1,                       //count
                   &vertexSourcePtr //shader code string
                   ,NULL
                   );
    glCompileShader(vertexShaderID);

    //check vertex shader
    int logLen;
    glGetShaderiv(vertexShaderID,GL_COMPILE_STATUS,&result);
    glGetShaderiv(vertexShaderID,GL_INFO_LOG_LENGTH,&logLen);
    if(logLen>0)
    {
        std::vector<char> vertexErrorMessage(logLen+1);
        glGetShaderInfoLog(vertexShaderID,logLen,NULL,&vertexErrorMessage[0]);
        printf("%s \n",&vertexErrorMessage[0]);
    }

    printf("compiling shader : %s \n",fragmentFilePath);
    char const * fragmentSourcePtr=fragmentShaderCode.c_str();
    glShaderSource(fragmentShaderID,1,&fragmentSourcePtr,NULL);
    glCompileShader(fragmentShaderID);
    //check fragment shader

    glGetShaderiv(fragmentShaderID,GL_COMPILE_STATUS,&result);
    glGetShaderiv(fragmentShaderID,GL_INFO_LOG_LENGTH,&logLen);
    if(logLen>0)
    {
        std::vector<char> fragmentErrorMessage(logLen+1);
        glGetShaderInfoLog(fragmentShaderID,logLen,NULL,&fragmentErrorMessage[0]);
        printf("%s \n",&fragmentErrorMessage[0]);
    }

    //link the program
    printf("link program \n");
    GLuint programID=glCreateProgram();
    glAttachShader(programID,vertexShaderID);
    glAttachShader(programID,fragmentShaderID);
    glLinkProgram(programID);

    //check the program
    glGetProgramiv(programID,GL_LINK_STATUS,&result);
    glGetProgramiv(programID,GL_INFO_LOG_LENGTH,&logLen);
    if(logLen>0)
    {
        std::vector<char> programErrorMsg(logLen+1);
        glGetProgramInfoLog(programID,logLen,NULL,&programErrorMsg[0]);
        printf("%s \n",&programErrorMsg[0]);
    }

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    return programID;
}

void drawShades()
{

}

void init()
{
    glClearColor(0.0f,0.0f,0.4f,0.0f);
    ConfigVertexBuffer();

    g_programID=loadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );

}

void frame()
{
    glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);

    // Use our shader
    glUseProgram(g_programID);

    drawVertexBuffer();

    glutSwapBuffers();
    glutPostRedisplay();
}

void reshape(int w,int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    GLdouble aspect	= (GLdouble)w/(GLdouble)h;
    GLdouble left	= -50.0f;
    GLdouble right	= 50.0f;
    GLdouble bottom	= -50.0f;
    GLdouble top	= 50.0f;

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

    glutPostRedisplay();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void mousebutton( int button, int state, int x, int y )
{}

void mousemove( int x, int y )
{}

void SpecialKeyHandle(int key,int x,int y)
{}

void keyboard( unsigned char key, int x, int y )
{}


int main( int argc, char **argv )
{
    // --------------------------------------
    // Initialize glut
    // --------------------------------------
    glutInit(&argc, argv);

    // --------------------------------------
    // Define display/window traits
    // --------------------------------------
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_ALPHA );
    glutInitWindowPosition( 0, 0 );
    glutInitWindowSize( 800, 600 );
    glutCreateWindow("glut-opengl");

    if(glewInit()!=GLEW_OK)
    {
        fprintf(stderr,"Fail to initialize GLEW \n");
        return -1;
    }
    // --------------------------------------
    // Register the functions
    // --------------------------------------
    init();
    glutDisplayFunc         ( frame );           // this is where we render
    glutReshapeFunc         ( reshape );
    glutMouseFunc           ( mousebutton );
    glutMotionFunc          ( mousemove );
    glutKeyboardFunc        ( keyboard);
    glutSpecialFunc         (SpecialKeyHandle);

    glutMainLoop();

    return 0;
}
