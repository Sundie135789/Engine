#include "headers/gameobject.hpp"
#include "headers/mesh.hpp"
#include "headers/material.hpp"
#include "headers/transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
Gameobject::Gameobject(std::string name){
  this->material = nullptr;
  this->transform = nullptr;
  this->name = name;
  std::cout << "Gameobject created: " << this->name << std::endl;
}
/*void Gameobject::SetShader(Shader* shader){
  this->shader = shader;
}*/
void Gameobject::SetMesh(Mesh* mesh){
  this->mesh = mesh;
}
void Gameobject::SetTransform(Transform* transform){
  this->transform = transform;
}
void Gameobject::SetMaterial(Material* material){
  this->material = material;
}
void Gameobject::SetName(std::string* name){
  this->name = *name;
}
glm::mat4 Gameobject::getModelMatrix(Transform* transform){
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, transform->position);
  model = glm::rotate(model, glm::radians(transform->rotation.x), glm::vec3(1,0,0));
  model = glm::rotate(model, glm::radians(transform->rotation.y), glm::vec3(0,1,0));
  model = glm::rotate(model, glm::radians(transform->rotation.z), glm::vec3(0,0,1));
  model = glm::scale(model, transform->scale);
  return model;
}
//void Gameobject::Render(){
  //shader->Use();
  //glm::mat4 model = this->getModelMatrix(this->transform);
 // glUniformMatrix4fv(glGetUniformLocation(shader->shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
//  mesh->Render();
//}
