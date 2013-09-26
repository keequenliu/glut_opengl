#include "main.h"


int main( int argc, char **argv )
{

    Client c;
    if(c.init(&argc,argv,new GridLine))
        c.start();

    return 0;
}
