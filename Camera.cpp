#include "Camera.h"

#include <GL/glut.h>

#define PI 3.1415265359
#define DegreeToRadian(angle) (angle*3.1415265359/180.0)

Camera::Camera()
{
    init();
}


void Camera::render()
{
    //    glLoadIdentity();
    //    gluLookAt(m_eye.x,m_eye.y,m_eye.z
    //              ,0,0,0
    //              ,0.0f,1.0f,0.0f);
    glLoadIdentity();
    glRotatef(-m_rotatedX , 1.0, 0.0, 0.0);
    glRotatef(-m_rotatedY , 0.0, 1.0, 0.0);
    glRotatef(-m_rotatedZ , 0.0, 0.0, 1.0);
    glTranslatef( -m_eye.x, -m_eye.y, -m_eye.z );

    printf("eye[x: %f,y: %f,z: %f]\n",m_eye.x,m_eye.y,m_eye.z);
}

void Camera::init()
{
    m_rotatedX=0.0f;
    m_rotatedY=0.0f;
    m_rotatedZ=0.0f;
    m_eye=glm::vec3(0.0,0.0,0.0);
    m_center=glm::vec3(0.0,0.0,-1.0f);
    m_viewDirChanged=false;
}

void Camera::reset()
{
    m_eye=glm::vec3(0.0,0.0,0.0);
    m_center=glm::vec3(0.0,0.0,-1.0f);
    m_viewDirChanged=false;
}

void Camera::GetViewDir( void )
{
    glm::vec3 Step1, Step2;
    //Rotate around Y-axis:
    Step1.x = cos( DegreeToRadian(m_rotatedY + 90.0) );
    Step1.z = -sin( DegreeToRadian(m_rotatedY + 90.0) );
    //Rotate around X-axis:
    double cosX = cos (DegreeToRadian(m_rotatedX));
    Step2.x = Step1.x * cosX;
    Step2.z = Step1.z * cosX;
    Step2.y = sin(DegreeToRadian(m_rotatedX));
    //Rotation around Z-axis not yet implemented, so:
    m_center = Step2;
}

void Camera::move(glm::vec3 direct)
{
    m_eye+=direct;
}
void Camera::rotateX(GLfloat angle)
{
    m_rotatedX+=angle;
    m_viewDirChanged=true;
}
void Camera::rotateY(GLfloat angle)
{
    m_rotatedY+=angle;
    m_viewDirChanged=true;
}
void Camera::rotateZ(GLfloat angle)
{

}
void Camera::rotateXYZ(glm::vec3 angles)
{

}
void Camera::moveForwards(GLfloat distance)
{
    if (m_viewDirChanged) GetViewDir();
    glm::vec3 MoveVector;
    MoveVector.x = m_center.x * -distance;
    MoveVector.y = m_center.y * -distance;
    MoveVector.z = m_center.z * -distance;

    m_eye+=MoveVector;
}
/** 右移 **/
void Camera::strafeRight(GLfloat distance)
{
    if (m_viewDirChanged) GetViewDir();
    glm::vec3 MoveVector;
    MoveVector.z = -m_center.x * -distance;
    MoveVector.y = 0.0;
    MoveVector.x = m_center.z * -distance;
    m_eye+=MoveVector;
}


void Camera::computeMatrices()
{

}


/********************************** Camera2 ********************************/

glm::vec3 VecMutiValue(glm::vec3 v,GLfloat value)
{
        printf("v[x: %f,y: %f,z: %f]\n",v.x,v.y,v.z);
    v*=value;
            printf("v2[x: %f,y: %f,z: %f]\n",v.x,v.y,v.z);
    return v;
}

Camera2::Camera2()
{
    setInitPositin();
}

void Camera2::setInitPositin(glm::vec3 viewVec, glm::vec3 rightVec, glm::vec3 upVec)
{
    m_eyePos=glm::vec3(0.0f,0.0f,5.0f);
    m_viewDirectVec=viewVec;
    m_rightVec=rightVec;
    m_upVec=upVec;

    m_rotateX=m_rotateY=m_rotateZ=0.0f;
}

void Camera2::render()
{
    glLoadIdentity();

    glm::vec3 viewPoint=m_viewDirectVec+m_eyePos;
    //as we know the up vector, we can easily use gluLookAt:
    gluLookAt(	m_eyePos.x,m_eyePos.y,m_eyePos.z,
                            viewPoint.x,viewPoint.y,viewPoint.z,
                            m_upVec.x,m_upVec.y,m_upVec.z);

//    glm::lookAt(m_eyePos,viewPoint,m_upVec);

//    printf("m_eyePos[x: %f,y: %f,z: %f]\n",m_eyePos.x,m_eyePos.y,m_eyePos.z);
//    printf("viewPoint[x: %f,y: %f,z: %f]\n",viewPoint.x,viewPoint.y,viewPoint.z);
}

void Camera2::rotateX(GLfloat angle)
{
    m_rotateX+=angle;
    m_viewDirectVec=VecMutiValue(m_viewDirectVec,cos(DegreeToRadian(angle)))
                    + VecMutiValue(m_upVec,sin(DegreeToRadian(angle)));
    m_viewDirectVec= glm::normalize(m_viewDirectVec);
    m_upVec=glm::cross(m_viewDirectVec,m_rightVec);
}

void Camera2::rotateY(GLfloat angle)
{
    m_rotateY+=angle;
    m_rightVec=VecMutiValue(m_rightVec,cos(DegreeToRadian(angle)))
            +VecMutiValue(m_viewDirectVec,sin(DegreeToRadian(angle)));
        m_rightVec= glm::normalize(m_rightVec);
    m_viewDirectVec=glm::cross(m_rightVec,m_upVec);
}

void Camera2::rotateZ(GLfloat angle)
{
    m_rotateZ+=angle;
    m_rightVec=VecMutiValue(m_rightVec,cos(DegreeToRadian(angle)))
            +VecMutiValue(m_upVec,sin(DegreeToRadian(angle)));

        m_rightVec= glm::normalize(m_rightVec);
    m_upVec=glm::cross(m_rightVec,m_viewDirectVec);
}

void Camera2::moveForwards(GLfloat distance)
{
    //注意这里是向z负方向移动，所以要减
    m_eyePos+=VecMutiValue(m_viewDirectVec,-distance);
}

void Camera2::strafeRight(GLfloat distance)
{
    m_eyePos+=VecMutiValue(m_rightVec,distance);
}

void Camera2::moveUpForwards(GLfloat distance)
{
    m_eyePos+=VecMutiValue(m_upVec,distance);
}

void Camera2::move(glm::vec3 direct)
{
    m_eyePos+=direct;
}




