#pragma once
#include <GL/glew.h>
#include <string>
class Shader{
  public:
    Shader(const std::string &vertexPath, const std::string &fragmentPath);
    GLuint shaderProgram;
    std::string fragmentPath, vertexPath;
    void Use();
};
