HEADERS += \
    main.h

SOURCES += \
    main.cpp

DESTDIR=./bin
OBJECTS_DIR=.obj
MOC_DIR=.obj

LIBS+=-lGL -lglut -lGLEW
