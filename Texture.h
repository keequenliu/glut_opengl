#ifndef KEEBITMAP_H
#define KEEBITMAP_H

#include <GL/glew.h>

class Texture
{
public:
    Texture();
    GLuint loadBMP(const char *filePath);
};

#endif // KEEBITMAP_H
