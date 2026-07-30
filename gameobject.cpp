#include "headers/gameobject.hpp"
#include "headers/mesh.hpp"
#include "headers/material.hpp"
#include "headers/transform.hpp"
#include "headers/globals.hpp"
#include "headers/log.hpp"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>
Gameobject::Gameobject(std::string name) : mesh(std::vector<Vertex>(), std::vector<unsigned int>()),material(), transform(), name(name){
  Log::Success("Gameobject created: " + name + "\n");
}
/*void Gameobject::SetShader(Shader* shader){
  this->shader = shader;
}*/
void Gameobject::SetMesh(const Mesh& mesh){
  this->mesh = mesh;
}
void Gameobject::SetTransform(const Transform& transform){
  this->transform = transform;
}
void Gameobject::SetMaterial(const Material& material){
  this->material = material;
}
void Gameobject::SetName(const std::string& name){
  this->name = name;
}
void Gameobject::CreateCube(){
  std::unique_ptr<Gameobject> gameobject = std::make_unique<Gameobject>((cube_untitled_number == 0) ? "Cube Untitled" : "Cube Untitled #" + std::to_string(cube_untitled_number));
  cube_untitled_number++;
std::vector<Vertex> vertices = {
    // FRONT (+Z)
    {{-0.5f,-0.5f, 0.5f}, {0,0,1}, {0,0}}, // 0
    {{ 0.5f,-0.5f, 0.5f}, {0,0,1}, {1,0}}, // 1
    {{ 0.5f, 0.5f, 0.5f}, {0,0,1}, {1,1}}, // 2
    {{-0.5f, 0.5f, 0.5f}, {0,0,1}, {0,1}}, // 3

    // BACK (-Z)
    {{-0.5f,-0.5f,-0.5f}, {0,0,-1}, {0,0}}, // 4
    {{-0.5f, 0.5f,-0.5f}, {0,0,-1}, {0,1}}, // 5
    {{ 0.5f, 0.5f,-0.5f}, {0,0,-1}, {1,1}}, // 6
    {{ 0.5f,-0.5f,-0.5f}, {0,0,-1}, {1,0}}, // 7

    // LEFT (-X)
    {{-0.5f, 0.5f, 0.5f}, {-1,0,0}, {1,1}}, // 8
    {{-0.5f, 0.5f,-0.5f}, {-1,0,0}, {0,1}}, // 9
    {{-0.5f,-0.5f,-0.5f}, {-1,0,0}, {0,0}}, // 10
    {{-0.5f,-0.5f, 0.5f}, {-1,0,0}, {1,0}}, // 11

    // RIGHT (+X)
    {{ 0.5f, 0.5f, 0.5f}, {1,0,0}, {1,1}}, // 12
    {{ 0.5f,-0.5f,-0.5f}, {1,0,0}, {0,0}}, // 13
    {{ 0.5f, 0.5f,-0.5f}, {1,0,0}, {0,1}}, // 14
    {{ 0.5f,-0.5f, 0.5f}, {1,0,0}, {1,0}}, // 15

    // TOP (+Y)
    {{-0.5f, 0.5f,-0.5f}, {0,1,0}, {0,1}}, // 16
    {{-0.5f, 0.5f, 0.5f}, {0,1,0}, {0,0}}, // 17
    {{ 0.5f, 0.5f, 0.5f}, {0,1,0}, {1,0}}, // 18
    {{ 0.5f, 0.5f,-0.5f}, {0,1,0}, {1,1}}, // 19

    // BOTTOM (-Y)
    {{-0.5f,-0.5f,-0.5f}, {0,-1,0}, {0,1}}, // 20
    {{ 0.5f,-0.5f,-0.5f}, {0,-1,0}, {1,1}}, // 21
    {{ 0.5f,-0.5f, 0.5f}, {0,-1,0}, {1,0}}, // 22
    {{-0.5f,-0.5f, 0.5f}, {0,-1,0}, {0,0}}, // 23
};
  std::vector<unsigned int > indices = {
    // FRONT
    0, 1, 2,
    2, 3, 0,

    // BACK
    4, 5, 6,
    6, 7, 4,

    // LEFT
    8, 9,10,
   10,11, 8,

    // RIGHT
   12,13,14,
   13,12,15,

    // TOP
   16,17,18,
   18,19,16,

    // BOTTOM
   20,21,22,
   22,23,20
};
  gameobject->SetMesh(Mesh(vertices, indices));
  Log::Success("Mesh Loaded: Vertex Count " + std::to_string(vertices.size()) + "\n");
  gameobject->SetMaterial(Material());
  gameobject->SetTransform(Transform());
  gameobjects.push_back(std::move(gameobject));
}
void Gameobject::CreatePlane(){
  std::unique_ptr<Gameobject> gameobject = std::make_unique<Gameobject>((plane_untitled_number == 0) ? "Plane Untitled" : "Plane Untitled #" + std::to_string(plane_untitled_number));
plane_untitled_number++;
std::vector<Vertex> vertices = {
    {{-0.5f, 0.0f, -0.5f}, {0,1,0}, {0,0}}, // 0
    {{ 0.5f, 0.0f, -0.5f}, {0,1,0}, {1,0}}, // 1
    {{ 0.5f, 0.0f,  0.5f}, {0,1,0}, {1,1}}, // 2
    {{-0.5f, 0.0f,  0.5f}, {0,1,0}, {0,1}}  // 3
};
std::vector<unsigned int > indices = {
    0, 2, 1,  // triangle 1
    0, 3, 2   // triangle 2
};
gameobject->SetMesh(Mesh(vertices, indices));
gameobject->SetMaterial(Material());
gameobject->SetTransform(Transform());
gameobjects.push_back(std::move(gameobject));
}
void Gameobject::CreateDirectionalLight(){
}
glm::mat4 Gameobject::getModelMatrix(){
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, transform.position);
  model = glm::rotate(model, glm::radians(transform.rotation.x), glm::vec3(1,0,0));
  model = glm::rotate(model, glm::radians(transform.rotation.y), glm::vec3(0,1,0));
  model = glm::rotate(model, glm::radians(transform.rotation.z), glm::vec3(0,0,1));
  model = glm::scale(model, transform.scale);
  return model;
}
void Gameobject::setModelMatrix(const glm::mat4& modelMatrix){
  glm::vec3 dummySkew;
  glm::vec4 dummyPerspective;
  glm::quat tempOrientation;
  glm::decompose(modelMatrix, transform.scale, tempOrientation, transform.position, dummySkew, dummyPerspective);
  transform.rotation = glm::degrees(glm::eulerAngles(tempOrientation));
}
//void Gameobject::Render(){
  //shader->Use();
  //glm::mat4 model = this->getModelMatrix(this->transform);
 // glUniformMatrix4fv(glGetUniformLocation(shader->shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
//  mesh->Render();
//}
