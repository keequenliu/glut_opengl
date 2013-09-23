#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

class Shader
{
public:
    Shader();
    //return program id
   static GLuint loadShaders(const char* vertexFile,const char* fragmentFile);
};

#endif // SHADER_H
