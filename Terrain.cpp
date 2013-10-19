#include "Terrain.h"
#include "image.h"
#include <GL/gl.h>


Terrain::Terrain()
{
    m_width=m_length=0;
    m_hs=NULL;
    m_normals=NULL;
    m_isComputeNormals=false;
}

Terrain::~Terrain()
{
    if(m_hs)
    {
        for(int i=0;i<m_length;i++)
            delete []m_hs[i];
        delete []m_hs;

        for(int i=0;i<m_length;i++)
            delete []m_normals[i];
        delete []m_normals;
    }
}

void Terrain::init(int width, int length)
{
    m_width=width;
    m_length=length;

    m_hs=new float*[m_length];//先长度
    for(int i=0;i<m_length;i++)
    {
        m_hs[i]=new float[m_width];
    }

    m_normals=new glm::vec3*[m_length];
    for(int i=0;i<m_length;i++)
    {
        m_normals[i]=new glm::vec3[m_width];
    }
    m_isComputeNormals=false;
}

int Terrain::width()
{
    return m_width;
}
int Terrain::length()
{
    return m_length;
}
//Sets the height at (x, z) to y
void Terrain::setHeight(int x,int z,float y)
{
    m_hs[x][z]=y;
    m_isComputeNormals = false; //值变化后，重新计算法线
}
//Returns the height at (x, z)
float Terrain::getHeight(int x, int z)
{
    return m_hs[x][z];
}
void Terrain::computeNormals()
{
    if(m_isComputeNormals)
    {
        return ;
    }
    glm::vec3** normals=new glm::vec3*[m_length];
    for(int i=0;i<m_length;i++)
    {
        normals[i]=new glm::vec3[m_width];
    }

    for(int z=0;z<m_length;z++)
    {
        for(int x=0;x<m_width;x++)
        {
            glm::vec3 sum(0.0f,0.0f,0.0f);
            glm::vec3 out,in,left,right;
            if(z>0)
            {
                out=glm::vec3(0.0f,m_hs[z-1][x]-m_hs[z][x],-1.0f);
            }
            if(z<m_length-1)
            {
                in=glm::vec3(0.0f,m_hs[z+1][x]-m_hs[z][x],1.0f);
            }
            if(x>0)
            {
                left=glm::vec3(-1.0f,m_hs[z][x-1]-m_hs[z][x],0.0f);
            }
            if(x<m_width-1)
            {
                right=glm::vec3(1.0f,m_hs[z][x+1]-m_hs[z][x],0.0f);
            }

            if(x> 0 && z>0)
            {
                sum+=glm::normalize(glm::cross(left,out));
            }
            if(x>0 && z< m_length-1)
            {
                sum+=glm::normalize(glm::cross(left,in));
            }
            if(x< m_width-1 && z<m_length-1 )
            {
                sum+=glm::normalize(glm::cross(in,right));
            }
            if(x< m_width-1 && z>0)
            {
                sum+=glm::normalize(glm::cross(right,out));
            }

            normals[z][x]=sum;

        }
    }

    //Smooth out the normals
    const float FALLOUT_RATIO = 0.5f;
    for(int z = 0; z < m_length; z++) {
        for(int x = 0; x < m_width; x++) {
            glm::vec3 sum = normals[z][x];

            if (x > 0) {
                sum += normals[z][x - 1] * FALLOUT_RATIO;
            }
            if (x < m_width - 1) {
                sum += normals[z][x + 1] * FALLOUT_RATIO;
            }
            if (z > 0) {
                sum += normals[z - 1][x] * FALLOUT_RATIO;
            }
            if (z < m_length - 1) {
                sum += normals[z + 1][x] * FALLOUT_RATIO;
            }

            if (glm::length(sum) == 0) {
                sum =  glm::vec3 (0.0f, 1.0f, 0.0f);
            }
            m_normals[z][x] = sum;
        }
    }

}
//Returns the normal at (x, z)
glm::vec3 Terrain::getNormal(int x,int z)
{
    if(!m_isComputeNormals)
    {
        computeNormals();
    }
    return m_normals[x][z];
}

//Loads a terrain from a heightmap.  The heights of the terrain range from
//-height / 2 to height / 2.
void Terrain::loadTerrain(const char* filename, float height)
{
    Image img;
    img.load(filename);
    init(img.width(), img.height());
    for(int y = 0; y < img.height(); y++)
    {
        for(int x = 0; x < img.width(); x++)
        {
//            unsigned char color =(unsigned char)img.data[3 * (y * img.width()+ x)];
//            float h = height * ((color / 255.0f) - 0.5f);
//            setHeight(x, y, h);
        }
    }
    computeNormals();
}

void Terrain::drawTerrain()
{
    for(int z = 0; z < length() - 1; z++)
    {
        //Makes OpenGL draw a triangle at every three consecutive vertices
        glBegin(GL_TRIANGLE_STRIP);
        for(int x = 0; x < width(); x++)
        {
            glm::vec3 normal = getNormal(x, z);
            glNormal3f(normal[0], normal[1], normal[2]);
            glVertex3f(x, getHeight(x, z), z);
            normal = getNormal(x, z + 1);
            glNormal3f(normal[0], normal[1], normal[2]);
            glVertex3f(x, getHeight(x, z + 1), z + 1);
        }
        glEnd();
    }
}
