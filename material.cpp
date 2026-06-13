#include "headers/material.hpp"
Material::Material(){
  this->color = glm::vec3(0.0f);
  this->shader = new Shader("shaders/undefined.vert", "shaders/undefined.frag");
  this->texture = new Texture("assets/missing_texture.png");
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
