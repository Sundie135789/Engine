#pragma once
#include <GL/glew.h>
#include <string>
#include "texture.hpp"
#include <glm/glm.hpp>
class Shader{
  public:
  GLuint shaderProgram;
  bool hasColor;
  float red, green, blue;
  bool hasTexture;
  Texture* texture;
  Shader(std::string vertPath, std::string fragPath);
  void SetColor(float red, float green, float blue);
  void SetTexture(Texture* texture);
  void SetMatrix(std::string uniformName, glm::mat4 matrix);
  ~Shader();
  void use();
};
