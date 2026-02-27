#include <GL/glew.h>
#pragma once
class Mesh{
  public:
    GLenum shape;
    GLuint vbo, vao;
    Mesh(float* vertices, int verticeCount, bool hasTexCoords);
    ~Mesh();
    void draw();
    int verticeCount;
    float* vertices;
};
