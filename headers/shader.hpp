#pragma once
#include <string>
#include <GL/glew.h>
#include <GL/gl.h>
#include "readshader.hpp"
class Shader{
  public:
    Shader(std::string vertex, std::string fragment);
    void use();
    ~Shader();
    GLuint shaderProgram;
};
