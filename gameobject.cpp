#include "gameobject.hpp"
#include <string>
#include <iostream>
#include "global.hpp"
GameObject::GameObject(std::string name, Shader* shader, Mesh* mesh, Transform* transform){
  this->name = name;
  this->shader = shader;
  this->mesh = mesh;
  this->transform = transform;
  this->shader->use();
}
GameObject::GameObject(std::string name){
  this->name = name;
  this->shader = nullptr;
  this->mesh = nullptr;
}
void GameObject::SetShader(Shader *shader){
  this->shader = shader;
}
void GameObject::SetMesh(Mesh *mesh){
  this->mesh = mesh;
}
void GameObject::SetName(std::string newName){
  this->name = newName;
}
void GameObject::SetTransform(Transform* transform){
  this->transform = transform;
}
GameObject::~GameObject(){
  delete mesh;
  delete shader;
}
void GameObject::draw(){
  if(this->shader == nullptr){
    std::cout << "GameObject.name: " << this->name << "\nGameObject.draw() called without setting shader." << std::endl;
    goTerminate();
    std::exit(1);
  }
  if(this->mesh == nullptr){
    std::cout << "GameObject.name: " << this->name << "\nGameObject.draw() called without setting mesh." << std::endl;
    goTerminate();
    std::exit(1);
  }
  shader->use();
  glm::mat4 model = transform->GetModelMatrix();
  shader->SetMatrix("model", model);
  mesh->draw();
}
