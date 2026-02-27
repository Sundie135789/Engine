
#pragma once
#include <string>
#include <GL/glew.h>
class Texture{
  public:
  Texture(std::string imagePath);
  GLuint textureID = 0;
  ~Texture();
  unsigned char** texture;
};
