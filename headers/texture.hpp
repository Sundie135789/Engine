#pragma once
#include <GL/glew.h>
#include <string>
class Texture{
  public:
    GLuint texture;
    Texture(std::string path);
    void Bind(int unit = 0) const;
    std::string path;
};
