#include "gameobject.hpp"
GameObject::GameObject(Shader* shader, Mesh* mesh){
  this->shader = shader;
  this->mesh = mesh;
  this->shader->use();
}
GameObject::~GameObject(){
  delete mesh;
  delete shader;
}
