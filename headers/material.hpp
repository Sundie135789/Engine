#pragma once
#include "shader.hpp"
#include "texture.hpp"
#include <glm/glm.hpp>
class Material{
  public:
    glm::vec3 color;
    Texture* texture;
    Shader* shader;
    Material();
    void setColor(glm::vec3 color);
    void setTexture(Texture* texture);
    void setShader(Shader* shader);
};
