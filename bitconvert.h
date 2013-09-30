#ifndef BITCONVERT_H
#define BITCONVERT_H

#include <fstream>

class BitConvert
{
public:
    BitConvert();

    //Converts a four-character array to an integer, using little-endian form
   static int toInt(const char* bytes) {
            return (int)(((unsigned char)bytes[3] << 24) |
                                     ((unsigned char)bytes[2] << 16) |
                                     ((unsigned char)bytes[1] << 8) |
                                     (unsigned char)bytes[0]);
    }

    //Converts a two-character array to a short, using little-endian form
    static short toShort(const char* bytes) {
            return (short)(((unsigned char)bytes[1] << 8) |
                                       (unsigned char)bytes[0]);
    }

    //Reads the next four bytes as an integer, using little-endian form
    static int readInt(std::ifstream &input) {
            char buffer[4];
            input.read(buffer, 4);
            return toInt(buffer);
    }

    //Reads the next two bytes as a short, using little-endian form
    static short readShort(std::ifstream &input) {
            char buffer[2];
            input.read(buffer, 2);
            return toShort(buffer);
    }

};

#endif // BITCONVERT_H
