#pragma once
#include "shader.hpp"
#include "mesh.hpp"
class GameObject{
  public:
  Shader *shader;
  Mesh* mesh;
  void draw(){
    shader->use();
    mesh->draw();
  }
  GameObject(Shader* shader, Mesh* mesh);
  ~GameObject();
};
