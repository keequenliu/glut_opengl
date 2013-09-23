HEADERS += \
    main.h \
    client.h \
    shader.h

SOURCES += \
    main.cpp \
    client.cpp \
    shader.cpp

DESTDIR=./bin
OBJECTS_DIR=.obj
MOC_DIR=.obj

DEFINES+=KEE_SHADER

LIBS+=-lGL -lglut -lGLEW

INCLUDEPATH +=/home/liuqijun/keequen/opengl-tutorial-org/external/glm-0.9.4.0
