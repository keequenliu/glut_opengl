#ifndef KEEBITMAP_H
#define KEEBITMAP_H

#include <GL/glew.h>
#include <FreeImage.h>

class Texture
{
public:
    Texture();
    GLuint textureID(){return m_textureID;}
    void loadBMP(const char *fileName);
    void loadBMP2(const char *filePath);
    void setActive();
private:
    GLuint m_textureID;
    FIBITMAP *m_bitmap;

};

#endif // KEEBITMAP_H
