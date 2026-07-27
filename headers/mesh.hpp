#pragma once
#include <vector>
#include <GL/glew.h>
#include "vertex.hpp"
class Mesh{
  public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    GLuint vbo, vao, ebo;
    void Draw() const;
};
