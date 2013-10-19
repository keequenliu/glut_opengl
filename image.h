#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <FreeImage.h>

class Image
{
public:
    Image();
    ~Image();
    bool load(std::string file);
    uint8_t *data();
    int width();
    int height();

private:
    int m_width;
    int m_heigth;
    uint8_t *m_data;
};

#endif // IMAGE_H
