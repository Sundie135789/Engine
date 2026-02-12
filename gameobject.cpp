#include "headers/gameobject.hpp"
#include <glm/glm.hpp>
GameObject::GameObject(Shader* shader, Mesh* mesh, Transform* transform){
  this->shader = shader;
  this->mesh = mesh;
  this->transform = transform;
}
GameObject::~GameObject(){
  delete shader;
  delete mesh;
  delete transform;
}
void GameObject::Delete(){
  delete shader;
  delete mesh;
  delete transform;
  shader = nullptr;
  mesh = nullptr;
  transform = nullptr;
}
