#include "shader.h"

#include <iostream>
#include <fstream>
#include <vector>

Shader::Shader()
{
}

GLuint Shader::loadShaders(const char* vertexFilePath,const char* fragmentFilePath)
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
