#include "Texture.h"

#include <stdio.h>

Texture::Texture()
{
}

GLuint Texture::loadBMP(const char *filePath)
{
    unsigned char head[54];
    unsigned int dataPos;
    unsigned int width ,height;
    unsigned int imageSize;
    // Actual RGB data
    unsigned char * data;

    FILE* file=fopen(filePath,"rb");
    if(file==NULL)
    {
        fprintf(stderr,"open the file: %s  fail \n",file);
        return 0;
    }

    if(fread(head,1,54,file)!=54)
    {
        fprintf(stderr,"the file is too short \n");
        return 0;
    }

    if(head[0]!='B' || head[1]!='M')
    {
        fprintf(stderr,"the file is not BMP format \n ");
        return 0;
    }
    // Make sure this is a 24bpp file
    if ( *(int*)&(head[0x1E])!=0  )         {printf("Not a correct BMP file\n");    return 0;}
    if ( *(int*)&(head[0x1C])!=24 )         {printf("Not a correct BMP file\n");    return 0;}

    //Read ints from the byte array
    dataPos=head[0x0a];
    imageSize=head[0x22];
    width=head[0x12];
    height=head[0x16];

    if(imageSize==0)
        imageSize=width * height *3;
    if(dataPos==0)
        dataPos=54;

    data=new unsigned char[imageSize];
    fread(data,1,imageSize,file);

    fclose(file);


    //create OpenGL texture
    GLuint textureID;
    glGenTextures(1,&textureID);
    glBindTexture(GL_TEXTURE_2D,textureID);

    //give the image to OpenGL
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB             //dest format,data type
                 ,width,height,0                    // src image w,h.
                 ,GL_BGR,GL_UNSIGNED_BYTE,data);    //src image format ,data type,data

    // OpenGL has now copied the data.
    delete []data;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Return the ID of the texture we just created
    return textureID;
}
