#include "headers/gameobject.hpp"
#include "headers/mesh.hpp"
#include "headers/material.hpp"
#include "headers/transform.hpp"
#include "headers/globals.hpp"
#include "headers/log.hpp"
#include <glm/gtc/type_ptr.hpp>
Gameobject::Gameobject(std::string name) : mesh(std::vector<Vertex>()),material(), transform(), name(name){
  Log::Success("Gameobject created: " + name);
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
    { { 0.5f,-0.5f,-0.5f}, {0,0,-1}, {1,0}  },
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
  gameobject->SetMesh(Mesh(vertices));
  gameobject->SetMaterial(Material());
  gameobject->SetTransform(Transform());
  gameobjects.push_back(std::move(gameobject));
}
void Gameobject::CreatePlane(){
  std::unique_ptr<Gameobject> gameobject = std::make_unique<Gameobject>((plane_untitled_number == 0) ? "Plane Untitled" : "Plane Untitled #" + std::to_string(plane_untitled_number));
plane_untitled_number++;
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
gameobject->SetMesh(Mesh(vertices));
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
//void Gameobject::Render(){
  //shader->Use();
  //glm::mat4 model = this->getModelMatrix(this->transform);
 // glUniformMatrix4fv(glGetUniformLocation(shader->shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
//  mesh->Render();
//}
