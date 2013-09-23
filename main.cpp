#include "main.h"

int main( int argc, char **argv )
{
    Client c;
    if(c.init(&argc,argv))
        c.start();

    return 0;
}
