#include "Texture.h"

#include <stdio.h>
#include <fstream>
#include <stream.h>
#include <assert.h>

#include "bitconvert.h"


Texture::Texture()
{

}

#if 1
void Texture::loadBMP(const char *fileName)
{

    //image format
    FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
    //check the file signature and deduce its format
    fif = FreeImage_GetFileType(fileName, 0);
    if(fif == FIF_UNKNOWN)
        return ;
    FIBITMAP *bitmap = FreeImage_Load(fif,fileName);
    BYTE *data (0);
    if(FreeImage_FIFSupportsReading(fif))
        data= FreeImage_GetBits(bitmap);
    if(!data)
        return;
    int width=FreeImage_GetWidth(bitmap);
    int height=FreeImage_GetHeight(bitmap);
    //

    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1,&m_textureID);
    glBindTexture(GL_TEXTURE_2D,m_textureID);
    //give the image to OpenGL
    glTexImage2D(GL_TEXTURE_2D          //Always GL_TEXTURE_2D
                 ,0                     //0 for now
                 ,GL_RGB                //Format OpenGL uses for image
                 ,width,height          //Width and height
                 ,0                     //The border of the image
                 ,GL_RGB                //GL_RGB, because pixels are stored in RGB format
                 ,GL_UNSIGNED_BYTE      //GL_UNSIGNED_BYTE, because pixels are stored as unsigned numbers
                 ,data                  //The actual pixel data
                 );

    FreeImage_Unload(bitmap);

    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void Texture::loadBMP2(const char *filePath)
{
    std::ifstream input;
    input.open(filePath, std::ifstream::binary);
    assert(!input.fail() || !"Could not find file");

    //read "BM" start flag
    char buffer[2];
    input.read(buffer, 2);
    assert(buffer[0] == 'B' && buffer[1] == 'M' || !"Not a bitmap file");
    //+8
    input.ignore(8);
    //+4
    int dataOffset = BitConvert::readInt(input);



    //Read the header
    int headerSize = BitConvert::readInt(input);
    int width;
    int height;
    switch(headerSize) {
    case 40:
        //V3
        width = BitConvert::readInt(input);
        height = BitConvert::readInt(input);
        input.ignore(2);
        assert(BitConvert::readShort(input) == 24 || !"Image is not 24 bits per pixel");
        assert(BitConvert::readShort(input) == 0 || !"Image is compressed");
        break;
    case 12:
        //OS/2 V1
        width = BitConvert::readShort(input);
        height = BitConvert::readShort(input);
        input.ignore(2);
        assert(BitConvert::readShort(input) == 24 || !"Image is not 24 bits per pixel");
        break;
    case 64:
        //OS/2 V2
        assert(!"Can't load OS/2 V2 bitmaps");
        break;
    case 108:
        //Windows V4
        assert(!"Can't load Windows V4 bitmaps");
        break;
    case 124:
        //Windows V5
        assert(!"Can't load Windows V5 bitmaps");
        break;
    default:
        assert(!"Unknown bitmap format");
    }

    //Read the data

    int bytesPerRow = ((width * 3 + 3) / 4) * 4 - (width * 3 % 4);
    int size = bytesPerRow * height;
    char * data=new char[size];
    input.seekg(dataOffset, std::ios_base::beg);
    input.read(data, size);

    //BGR->RGB
    //Get the data into the right format
    char * data2=new char[width * height * 3];
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            for(int c = 0; c < 3; c++) {
                data2[3 * (width * y + x) + c] =
                        data[bytesPerRow * y + 3 * x + (2 - c)];
            }
        }
    }

    input.close();
    //create OpenGL texture
    glGenTextures(1,&m_textureID);
    //     glBindTexture(GL_TEXTURE_2D,m_textureID);
    //give the image to OpenGL
    glTexImage2D(GL_TEXTURE_2D          //Always GL_TEXTURE_2D
                 ,0                     //0 for now
                 ,GL_RGB                //Format OpenGL uses for image
                 ,width,height          //Width and height
                 ,0                     //The border of the image
                 ,GL_RGB                //GL_RGB, because pixels are stored in RGB format
                 ,GL_UNSIGNED_BYTE      //GL_UNSIGNED_BYTE, because pixels are stored as unsigned numbers
                 ,data2                  //The actual pixel data
                 );

    // OpenGL has now copied the data.
    delete []data;
    delete []data2;
}
#else
void Texture::loadBMP(const char *filePath)
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
        return ;
    }

    if(fread(head,1,54,file)!=54)
    {
        fprintf(stderr,"the file is too short \n");
        return ;
    }

    if(head[0]!='B' || head[1]!='M')
    {
        fprintf(stderr,"the file is not BMP format \n ");
        return ;
    }
    // Make sure this is a 24bpp file
    if ( *(int*)&(head[0x1E])!=0  )         {printf("Not a correct BMP file\n");    return ;}
    if ( *(int*)&(head[0x1C])!=24 )         {printf("Not a correct BMP file\n");    return ;}

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
    glGenTextures(1,&m_textureID);
    //     glBindTexture(GL_TEXTURE_2D,m_textureID);
    //give the image to OpenGL
    glTexImage2D(GL_TEXTURE_2D          //Always GL_TEXTURE_2D
                 ,0                     //0 for now
                 ,GL_RGB                //Format OpenGL uses for image
                 ,width,height          //Width and height
                 ,0                     //The border of the image
                 ,GL_BGR                //GL_RGB, because pixels are stored in RGB format
                 ,GL_UNSIGNED_BYTE      //GL_UNSIGNED_BYTE, because pixels are stored as unsigned numbers
                 ,data                  //The actual pixel data
                 );

    // OpenGL has now copied the data.
    delete []data;

    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    //    glGenerateMipmap(GL_TEXTURE_2D);
}
#endif

void Texture::setActive()
{
    glBindTexture(GL_TEXTURE_2D,m_textureID);
//    glColor3f(0.0f, 0.0f, 0.0f);
//    //bottom
//    glBegin(GL_QUADS);
//    glTexCoord2f(0.0f, 0.0f);
//    glVertex3f(-2.5f, -2.5f, 2.5f);
//    glTexCoord2f(1.0f, 0.0f);
//    glVertex3f(2.5f, -2.5f, 2.5f);
//    glTexCoord2f(1.0f, 1.0f);
//    glVertex3f(2.5f, -2.5f, -2.5f);
//    glTexCoord2f(0.0f, 1.0f);
//    glVertex3f(-2.5f, -2.5f, -2.5f);
//    glEnd();
//    glDisable(GL_TEXTURE_2D);

//    glEnable(GL_TEXTURE_2D);
//    //up
//    glBegin(GL_TRIANGLES);
//    glTexCoord2f(1.0f, 0.0f);
//    glVertex3f(2.5f, -2.5f, -2.5f);
//    glTexCoord2f(0.0f, 0.0f);
//    glVertex3f(-2.5f, -2.5f, -2.5f);
//    glTexCoord2f(1.0f, 1.0f);
//    glVertex3f(0.0f, 2.5f, -2.5f);
//    glEnd();

//    glDisable(GL_TEXTURE_2D);

}
