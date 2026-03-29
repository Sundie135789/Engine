#include <GL/glew.h>
#include <vector>
#pragma once
class Mesh{
  public:
    GLuint vbo, vao;
    Mesh(std::vector<float> vertices, int verticeCount, int stride);
    ~Mesh();
    void draw();
    int verticeCount;
   std::vector <float> vertices;
};
