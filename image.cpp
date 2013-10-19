#include "image.h"

Image::Image()
    :m_width(0)
    ,m_heigth(0)
    ,m_data(NULL)
{
}
Image::~Image()
{

}

bool Image::load(std::string file)
{
    //image format
    FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
    //check the file signature and deduce its format
    fif = FreeImage_GetFileType(file.c_str(), 0);
    if(fif == FIF_UNKNOWN)
        return false;
    FIBITMAP *bitmap = FreeImage_Load(fif,file.c_str());
    if(FreeImage_FIFSupportsReading(fif))
    {
        m_data= FreeImage_GetBits(bitmap);
        if(!m_data)
            return false;
        m_width=FreeImage_GetWidth(bitmap);
        m_heigth=FreeImage_GetHeight(bitmap);
    }
    FreeImage_Unload(bitmap);

    return true;
}

uint8_t *Image::data()
{
    return m_data;
}
int Image::width()
{
    return m_width;
}
int Image::height()
{
    return m_heigth;
}
