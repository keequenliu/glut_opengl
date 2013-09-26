
QT       -= core gui
CONFIG -=qt

DESTDIR=./bin
OBJECTS_DIR=.obj
MOC_DIR=.obj

#DEFINES+=KEE_SHADER

HEADERS += \
    main.h \
    client.h \
    shader.h \
    BaseModel.h \
    cubeTriangle.h \
    keeTriangle.h \
    Texture.h \
    Camera.h \
    GridLine.h \
    Cube.h

SOURCES += \
    main.cpp \
    client.cpp \
    shader.cpp \
    BaseModel.cpp \
    cubeTriangle.cpp \
    keeTriangle.cpp \
    Texture.cpp \
    Camera.cpp \
    GridLine.cpp \
    Cube.cpp

LIBS+=-lGL -lglut -lGLEW
INCLUDEPATH +=/home/liuqijun/keequen/opengl-tutorial-org/external/glm-0.9.4.0
