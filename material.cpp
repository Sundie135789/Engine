#include "headers/material.hpp"
#include "headers/assetmanager.hpp"
#include <memory.h>
// Default material (safe null init OR external assignment later)
Material::Material()
    : 
      color(1.0f),
      shininess(30.0f),
      specularColor(1.0f),
      specularStrength(6.0f),
      shader("shaders/basic.vert", "shaders/basic.frag")
{
  texture = AssetManager::GetTexture("assets/missing_texture.png");
}
// Fully defined material
Material::Material(glm::vec3 specularColor,
                   float specularStrength,
                   glm::vec3 color,
                   float shininess,
                   std::string texture,
                   std::string vertexPath,
                   std::string fragmentPath
                ) :
      specularColor(specularColor),
      specularStrength(specularStrength),
      color(color),
      shininess(shininess),
      shader(vertexPath, fragmentPath)
{
  this->texture = AssetManager::GetTexture(texture);
}

void Material::setColor(glm::vec3 color) {
    this->color = color;
}

void Material::setShader(Shader&& shader) {
    this->shader = std::move(shader);
}

void Material::setTexture(const std::string& texturePath) {
    this->texture = AssetManager::GetTexture(texturePath);
}

void Material::setShininess(float shininess) {
    this->shininess = shininess;
}

void Material::setSpecularColor(glm::vec3 specularColor) {
    this->specularColor = specularColor;
}

void Material::setSpecularStrength(float specularStrength) {
    this->specularStrength = specularStrength;
}

