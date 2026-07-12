#pragma once

#include "shader.hpp"
#include "texture.hpp"
#include <glm/glm.hpp>
#include <memory>
#include <string>

class Material {
  public:
    glm::vec3 specularColor;
    float specularStrength;
    glm::vec3 color;
    float shininess;

 Shader shader;
    Texture* texture;

    Material();
    Material(glm::vec3 specularColor,
             float specularStrength,
             glm::vec3 color,
             float shininess,
             std::string texture,
             std::string vertexPath,
             std::string fragmentPath
             );


    void setColor(glm::vec3 color);
    void setShader(Shader&& shader);
    void setTexture(const std::string& texturePath);
    void setShininess(float shininess);
    void setSpecularColor(glm::vec3 specularColor);
    void setSpecularStrength(float specularStrength);

};
