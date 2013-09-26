#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
    Camera();

    void render();
    void computeMatrices();
    void reset();
    void move(glm::vec3 direct);
    void rotateX(GLfloat angle);
    void rotateY(GLfloat angle);
    void rotateZ(GLfloat angle);
    void rotateXYZ(glm::vec3 angles);
    void moveForwards(GLfloat distance);
    /** 右移 **/
    void strafeRight(GLfloat distance);
private:

    void init();
    void GetViewDir( void );

    GLfloat m_rotatedX; //rolate by x
    GLfloat m_rotatedY; //rolate by y
    GLfloat m_rotatedZ; //rolate by z

    glm::vec3 m_eye;
    glm::vec3 m_center;
    bool m_viewDirChanged;

    float m_horizontalAngle;
    float m_verticalAngle;
    float m_FOV;
    float m_speed;
    float m_mouseSpeed;

    glm::mat4 m_viewMatrix;
    glm::mat4 m_projectMatrix;
};


/** 改进版本的camera ,以三个向量的方式来管理摄像机,但是并没有处理鼠标
// -----------------------------------------------
//  Coordinate system
// up+  |
//      | /- viewDirect
//      |/
//      +--- right+
//
// -----------------------------------------------
**/
class Camera2
{
public:
    Camera2();
    /** 初始位置 **/
    void setInitPositin(glm::vec3 viewVec=glm::vec3(0.0f,0.0f,-1.0f)
                        ,glm::vec3 rightVec=glm::vec3(1.0f,0.0f,0.0f)
                        ,glm::vec3 upVec=glm::vec3(0.0f,1.0f,0.0f));
    void reset();
    void render();
    void move(glm::vec3 direct);
    void rotateX(GLfloat angle);
    void rotateY(GLfloat angle);
    void rotateZ(GLfloat angle);
    void rotateXYZ(glm::vec3 angles);
    /** 向里移动(相当于延z轴向里)**/
    void moveForwards(GLfloat distance);
    /** 右移 **/
    void strafeRight(GLfloat distance);
    /** 上移（相当于延y轴向上）**/
    void moveUpForwards(GLfloat distance);
private:

    /** 角度 **/
    GLfloat m_rotateX;
    GLfloat m_rotateY;
    GLfloat m_rotateZ;
    glm::vec3 m_viewDirectVec;
    glm::vec3 m_rightVec;
    glm::vec3 m_upVec;
    glm::vec3 m_eyePos;
};


#endif // CAMERA_H
