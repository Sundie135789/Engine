#include "headers/material.hpp"
Material::Material(){
  this->color = glm::vec3(0.0f);
  this->shader = new Shader("shaders/basic.vert", "shaders/basic.frag");
  this->texture = new Texture("assets/missing_texture.png");
  this->shininess = 8.0f;
  this->specularColor = glm::vec3(1.0f);
  this->specularStrength = 4.0f;
}
void Material::setColor(glm::vec3 color){
  this->color = color;
}
void Material::setShader(Shader* shader){
  this->shader = shader;
}
void Material::setTexture(Texture* texture){
  this->texture = texture;
}
void Material::setShininess(float shininess){
  this->shininess = shininess;
}
void Material::setSpecularColor(glm::vec3 specularColor){
  this->specularColor = specularColor;
}
void Material::setSpecularStrength(float specularStrength){
  this->specularStrength = specularStrength;
}
