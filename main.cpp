#include "main.h"

#include <string>
#include <vector>

#if 1

int main( int argc, char **argv )
{

//    std::string d="22";
//    double d0=Utility::FromString<double>(d);
//    std::cout<<d0<<std::endl;

//    double tt=22.03f;
//    std::string s0=Utility::ToString<double>(tt);
//    std::cout<<s0<<std::endl;

//    std::string::size_type sz;   // alias of size_t

//    //       int i_dec = std::stoi (d,&sz);

//    std::string test="hello,grst,world,test,liuqijun,ok";
//    std::vector<std::string> list=Utility::StringSplit(test,',');

//    for(int i=0;i<list.size();i++)
//    {
//        std::cout<<"[list]-"<<list[i]<<std::endl;
//    }
//    std::cout<<"hex:"<<Utility::StringToHex("a")<<std::endl;

//    std::cout<<"hex:"<<Utility::ToHexString<int>(11)<<std::endl;

//    Utility::getChildsOfDir("/home/liuqijun");

//    return 0;

    Client c;
    if(c.init(&argc,argv,new Cube))
        c.start();
    return 0;
}
#else

/* Copyright (c) Mark J. Kilgard, 1997.  */

/* This program is freely distributable without licensing fees  and is
   provided without guarantee or warrantee expressed or  implied. This
   program is -not- in the public domain. */

/* This example shows how to use the GLU polygon tessellator to determine the

   2D boundary of OpenGL rendered objects.  The program uses OpenGL's
   feedback mechanim to capture transformed polygons and then feeds them to
   the GLU tesselator in GLU_TESS_WINDING_NONZERO and GLU_TESS_BOUNDARY_ONLY
   mode. */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#ifdef GLU_VERSION_1_2

#ifndef CALLBACK
#define CALLBACK
#endif

enum {
    M_TORUS, M_CUBE, M_SPHERE, M_ICO, M_TEAPOT, M_ANGLE, M_BOUNDARY
};

struct VertexHolder {
    struct VertexHolder *next;
    GLfloat v[2];
};

int shape = M_TORUS;
int boundary = 1;
GLfloat angle = 0.0;
GLfloat y_angle=0.0;

GLfloat lightDiffuse[] =
{1.0, 0.0, 0.0, 1.0};
GLfloat lightPosition[] =
{1.0, 1.0, 1.0, 0.0};

GLUtesselator *tess;
int width, height;

static void CALLBACK
begin(GLenum type)
{
    assert(type == GL_LINE_LOOP);
    glBegin(type);
}

static void CALLBACK
vertex(void *data)
{
    GLfloat *v = (GLfloat*)data;
    glVertex2fv(v);
}

static void CALLBACK
end(void)
{
    glEnd();
}

static GLfloat *combineList = NULL;
static int combineListSize = 0;
static int combineNext = 0;
static struct VertexHolder *excessList = NULL;

static void
freeExcessList(void)
{
    struct VertexHolder *holder, *next;

    holder = excessList;
    while (holder) {
        next = holder->next;
        free(holder);
        holder = next;
    }
    excessList = NULL;
}

/* ARGSUSED1 */
static void CALLBACK
combine(GLdouble coords[3], void *d[4], GLfloat w[4], void **dataOut)
{
    GLfloat *new1;
    struct VertexHolder *holder;

    /* XXX Careful, some systems still don't understand realloc of NULL. */
    if (combineNext >= combineListSize) {
        holder = (struct VertexHolder *) malloc(sizeof(struct VertexHolder));
        holder->next = excessList;
        excessList = holder;
        new1 = holder->v;
    } else {
        new1 = &combineList[combineNext * 2];
    }

    new1[0] = coords[0];
    new1[1] = coords[1];
    *dataOut = new1;

    combineNext++;
}

static void CALLBACK
error(GLenum errno)
{
    printf("ERROR: %s\n", gluErrorString(errno));
}

void
reshape(int w, int h)
{
    width = w;
    height = h;
    glViewport(0, 0, width, height);
}

void
processFeedback(GLint size, GLfloat * buffer)
{
    GLfloat *loc, *end;
    GLdouble v[3];
    int token, nvertices, i;

    if (combineNext > combineListSize) {
        freeExcessList();
        combineListSize = combineNext;
        combineList = (GLfloat *)realloc(combineList, sizeof(GLfloat) * 2 * combineListSize);
    }
    combineNext = 0;

    gluTessBeginPolygon(tess, NULL);
    loc = buffer;
    end = buffer + size;
    while (loc < end) {
        token = *loc;
        loc++;
        switch (token) {
        case GL_POLYGON_TOKEN:
            nvertices = *loc;
            loc++;
            assert(nvertices >= 3);
            gluTessBeginContour(tess);
            for (i = 0; i < nvertices; i++) {
                v[0] = loc[0];
                v[1] = loc[1];
                v[2] = 0.0;
                gluTessVertex(tess, v, loc);
                loc += 2;
            }
            gluTessEndContour(tess);
            break;
        default:
            /* Ignore everything but polygons. */
            ;
        }
    }
    gluTessEndPolygon(tess);
}

int
determineBoundary(void (*renderFunc) (void), int probableSize)
{
    static GLfloat *feedbackBuffer = NULL;
    static int bufferSize = 0;
    GLint returned;

    if (bufferSize > probableSize) {
        probableSize = bufferSize;
    }
doFeedback:

    /* XXX Careful, some systems still don't understand realloc of NULL. */
    if (bufferSize < probableSize) {
        bufferSize = probableSize;
        feedbackBuffer = (GLfloat *)realloc(feedbackBuffer, bufferSize * sizeof(GLfloat));
    }
    glFeedbackBuffer(bufferSize, GL_2D, feedbackBuffer);

    (void) glRenderMode(GL_FEEDBACK);

    (*renderFunc) ();

    returned = glRenderMode(GL_RENDER);
#if 0
    if (returned == -1) {
#else
    /* XXX RealityEngine workaround. */
    if (returned == -1 || returned == probableSize) {
#endif
        probableSize = probableSize + (probableSize >> 1);
        goto doFeedback;    /* Try again with larger feedback buffer. */
    }
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    processFeedback(returned, feedbackBuffer);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    return returned;
}

void
render(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective( /* field of view in degree */ 30.0,
                    /* aspect ratio */ 1.0,
                    /* Z near */ 1.0, /* Z far */ 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 10.0,  /* eye is at (0,0,5) */
              0.0, 0.0, 0.0,      /* center is at (0,0,0) */
              0.0, 1.0, 0.);      /* up is in postivie Y direction */

    //  glPushMatrix();
    //  glRotatef(angle, 1.0, 0.3, 0.0);
    glRotatef(angle, 1.0, 0.0, 0.0);
    glRotatef(y_angle, 0.0, 1.0, 0.0);
    switch (shape) {
    case M_TORUS:
        glutSolidTorus(0.275, 0.85, 8, 8);
        break;
    case M_CUBE:
        glutSolidCube(1.0);
        break;
    case M_SPHERE:
        glutSolidSphere(1.0, 10, 10);
        break;
    case M_ICO:
        glutSolidIcosahedron();
        break;
    case M_TEAPOT:
        glutSolidTeapot(1.0);
        break;
    }
    //  glPopMatrix();
}

void
display(void)
{
    if (boundary) {
        glClear(GL_COLOR_BUFFER_BIT);
        glDisable(GL_LIGHTING);
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        determineBoundary(render, 250);
    } else {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_LIGHTING);
        glEnable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE);
        render();
    }
    glutSwapBuffers();
}

void
menu(int value)
{
    switch (value) {
    case M_TORUS:
    case M_CUBE:
    case M_SPHERE:
    case M_ICO:
    case M_TEAPOT:
        shape = value;
        break;
    case M_ANGLE:
        angle += 10.0;
        break;
    case M_BOUNDARY:
        boundary = !boundary;  /* Toggle. */
        break;
    }
    glutPostRedisplay();
}

/* ARGSUSED1 */
void
special(int key, int x, int y)
{
    switch (key) {
    case GLUT_KEY_UP:
        angle += 10.0;
        glutPostRedisplay();
        break;
    case GLUT_KEY_DOWN:
        angle -= 10.0;
        glutPostRedisplay();
        break;
    case GLUT_KEY_LEFT:
        y_angle += 10.0;
        glutPostRedisplay();
        break;
    case GLUT_KEY_RIGHT:
        y_angle -= 10.0;
        glutPostRedisplay();
        break;
    }
}

int
main(int argc, char **argv)
{
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInit(&argc, argv);

    glutCreateWindow("boundary");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(special);

    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glEnable(GL_LIGHT0);

    tess = gluNewTess();
    gluTessProperty(tess, GLU_TESS_BOUNDARY_ONLY, GL_TRUE);
    gluTessProperty(tess, GLU_TESS_WINDING_RULE, GLU_TESS_WINDING_NONZERO);
    gluTessCallback(tess, GLU_TESS_BEGIN, (void (CALLBACK*)())begin);
    gluTessCallback(tess, GLU_TESS_VERTEX, (void (CALLBACK*)())vertex);
    gluTessCallback(tess, GLU_TESS_END, (void (CALLBACK*)())end);
    gluTessCallback(tess, GLU_TESS_ERROR, (void (CALLBACK*)())error);
    gluTessCallback(tess, GLU_TESS_COMBINE, (void (CALLBACK*)())combine);

    glutCreateMenu(menu);
    glutAddMenuEntry("Torus", M_TORUS);
    glutAddMenuEntry("Cube", M_CUBE);
    glutAddMenuEntry("Sphere", M_SPHERE);
    glutAddMenuEntry("Icosahedron", M_ICO);
    glutAddMenuEntry("Teapot", M_TEAPOT);
    glutAddMenuEntry("Angle", M_ANGLE);
    glutAddMenuEntry("Toggle boundary", M_BOUNDARY);
    glutAttachMenu(GLUT_RIGHT_BUTTON);




    glutMainLoop();
    return 0;             /* ANSI C requires main to return int. */
}

#else
int main(int argc, char** argv)
{
    fprintf(stderr, "This program demonstrates the new tesselator API in GLU 1.2.\n");
    fprintf(stderr, "Your GLU library does not support this new interface, sorry.\n");
    return 0;
}
#endif  /* GLU_VERSION_1_2 */

#endif

