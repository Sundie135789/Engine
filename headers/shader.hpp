#pragma once
#include <GL/glew.h>
#include <string>
class Shader{
  public:
  GLuint shaderProgram;

  Shader(std::string vertPath, std::string fragPath);
  void use();
};
