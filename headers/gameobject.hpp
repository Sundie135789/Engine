#pragma once
#include "shader.hpp"
#include "mesh.hpp"
class GameObject{
  public:
  Shader *shader;
  Mesh* mesh;
  void draw();
  GameObject(Shader* shader, Mesh* mesh);
  ~GameObject();
};
