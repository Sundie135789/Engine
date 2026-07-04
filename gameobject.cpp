#include "headers/gameobject.hpp"
#include "headers/mesh.hpp"
#include "headers/material.hpp"
#include "headers/transform.hpp"
#include "headers/globals.hpp"
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
void Gameobject::CreateCube(){
  Gameobject *gameobject = new Gameobject((untitled_number == 0) ? "Cube Untitled" : "Cube Untitled #" + std::to_string(untitled_number));
  untitled_number++;
  std::vector<Vertex> vertices = {{ {-0.5f,-0.5f, 0.5f}, {0,0,1}, {0,0} },
    { { 0.5f,-0.5f, 0.5f}, {0,0,1}, {1,0} },
    { { 0.5f, 0.5f, 0.5f}, {0,0,1}, {1,1} },
    { { 0.5f, 0.5f, 0.5f}, {0,0,1}, {1,1} },
    { {-0.5f, 0.5f, 0.5f}, {0,0,1}, {0,1} },
    { {-0.5f,-0.5f, 0.5f}, {0,0,1}, {0,0} },

    // BACK (-Z)
    { {-0.5f,-0.5f,-0.5f}, {0,0,-1}, {0,0} },
    { {-0.5f, 0.5f,-0.5f}, {0,0,-1}, {0,1} },
    { { 0.5f, 0.5f,-0.5f}, {0,0,-1}, {1,1} },
    { { 0.5f, 0.5f,-0.5f}, {0,0,-1}, {1,1} },
    { { 0.5f,-0.5f,-0.5f}, {0,0,-1}, {1,0} },
    { {-0.5f,-0.5f,-0.5f}, {0,0,-1}, {0,0} },

    // LEFT (-X)
    { {-0.5f, 0.5f, 0.5f}, {-1,0,0}, {1,1} },
    { {-0.5f, 0.5f,-0.5f}, {-1,0,0}, {0,1} },
    { {-0.5f,-0.5f,-0.5f}, {-1,0,0}, {0,0} },
    { {-0.5f,-0.5f,-0.5f}, {-1,0,0}, {0,0} },
    { {-0.5f,-0.5f, 0.5f}, {-1,0,0}, {1,0} },
    { {-0.5f, 0.5f, 0.5f}, {-1,0,0}, {1,1} },

    // RIGHT (+X)
    { { 0.5f, 0.5f, 0.5f}, {1,0,0}, {1,1} },
    { { 0.5f,-0.5f,-0.5f}, {1,0,0}, {0,0} },
    { { 0.5f, 0.5f,-0.5f}, {1,0,0}, {0,1} },
    { { 0.5f,-0.5f,-0.5f}, {1,0,0}, {0,0} },
    { { 0.5f, 0.5f, 0.5f}, {1,0,0}, {1,1} },
    { { 0.5f,-0.5f, 0.5f}, {1,0,0}, {1,0} },

    // TOP (+Y)
    { {-0.5f, 0.5f,-0.5f}, {0,1,0}, {0,1} },
    { {-0.5f, 0.5f, 0.5f}, {0,1,0}, {0,0} },
    { { 0.5f, 0.5f, 0.5f}, {0,1,0}, {1,0} },
    { { 0.5f, 0.5f, 0.5f}, {0,1,0}, {1,0} },
    { { 0.5f, 0.5f,-0.5f}, {0,1,0}, {1,1} },
    { {-0.5f, 0.5f,-0.5f}, {0,1,0}, {0,1} },

    // BOTTOM (-Y)
    { {-0.5f,-0.5f,-0.5f}, {0,-1,0}, {0,1} },
    { { 0.5f,-0.5f,-0.5f}, {0,-1,0}, {1,1} },
    { { 0.5f,-0.5f, 0.5f}, {0,-1,0}, {1,0} },
    { { 0.5f,-0.5f, 0.5f}, {0,-1,0}, {1,0} },
    { {-0.5f,-0.5f, 0.5f}, {0,-1,0}, {0,0} },
    { {-0.5f,-0.5f,-0.5f}, {0,-1,0}, {0,1} }};
  Mesh* mesh = new Mesh(vertices);
  Material* material = new Material();
  Transform* transform = new Transform();
  gameobject->SetMesh(mesh);
  gameobject->SetMaterial(material);
  gameobject->SetTransform(transform);
  gameobjects.push_back(gameobject);
}
void Gameobject::CreatePlane(){
 Gameobject *gameobject = new Gameobject((untitled_number == 0) ? "Plane Untitled" : "Plane Untitled #" + std::to_string(untitled_number));
untitled_number++;
std::vector<Vertex> vertices = {
    // Triangle 1
    { {-0.5f, -0.0f, -0.5f}, {0,1,0}, {0,0} },
    { { 0.5f, -0.0f,  0.5f}, {0,1,0}, {1,1} },
    { { 0.5f, -0.0f, -0.5f}, {0,1,0}, {1,0} },

    // Triangle 2
    { {-0.5f, -0.0f, -0.5f}, {0,1,0}, {0,0} },
    { {-0.5f, -0.0f,  0.5f}, {0,1,0}, {0,1} },
    { { 0.5f, -0.0f,  0.5f}, {0,1,0}, {1,1} }
};
Mesh* mesh = new Mesh(vertices);
Material* material = new Material();
Transform* transform = new Transform();
//transform->position = glm::vec3(0.0f, -0.5f, 0.0f);
gameobject->SetMesh(mesh);
gameobject->SetMaterial(material);
gameobject->SetTransform(transform);
gameobjects.push_back(gameobject);
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
