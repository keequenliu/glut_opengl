#ifndef TERRAIN_H
#define TERRAIN_H

#include <glm/glm.hpp>

//暂时不能使用

//represents a terrain
class Terrain
{
public:
    Terrain();
    ~Terrain();
    void loadTerrain(const char* filename, float height);
    void drawTerrain();
private:
    void init(int width,int length);
    int width();
    int length();
    //Sets the height at (x, z) to y
    void setHeight(int x,int z,float y);
    //Returns the height at (x, z)
    float getHeight(int x, int z);
    void computeNormals();
    //Returns the normal at (x, z)
    glm::vec3 getNormal(int x,int z);

    int m_width;
    int m_length;
    float **m_hs;//height per point
    glm::vec3** m_normals;
    bool m_isComputeNormals;
};

#endif // TERRAIN_H
