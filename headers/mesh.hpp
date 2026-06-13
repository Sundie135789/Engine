#pragma once
#include <vector>
#include "vertex.hpp"
#include <GL/glew.h>
#include <GL/gl.h>
class Mesh{
  public:
    Mesh(std::vector<Vertex> vertices);
    std::vector<Vertex> vertices;
    GLuint vbo, vao;
    void Draw() const;
};
