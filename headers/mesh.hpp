#pragma once
#include <vector>
#include <GL/glew.h>
#include "vertex.hpp"
class Mesh{
  public:
    Mesh(std::vector<Vertex> vertices);
    std::vector<Vertex> vertices;
    GLuint vbo, vao;
    void Draw() const;
};
