#pragma once
#include <GL/glew.h>
#include <string>
class Shader{
  public:
    Shader(std::string vertexPath, std::string fragmentPath);
    GLuint shaderProgram;
    std::string fragmentPath, vertexPath;
    void Use();
};
