#pragma once
#include "shader.hpp"
#include "texture.hpp"
#include <glm/glm.hpp>
class Material{
  public:
    glm::vec3 specularColor;
    float specularStrength;
    glm::vec3 color;
    float shininess;
    Texture* texture;
    Shader* shader;
    Material();
    void setColor(glm::vec3 color);
    void setTexture(Texture* texture);
    void setShader(Shader* shader);
    void setShininess(float shininess);
    void setSpecularColor(glm::vec3 specularColor);
    void setSpecularStrength(float specularStrength);

};
