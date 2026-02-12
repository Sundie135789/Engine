#pragma once
#include <glm/glm.hpp>
#include "shader.hpp"
#include "mesh.hpp"
#include "transform.hpp"
class GameObject{
  public:
  Shader* shader;
  Mesh* mesh;
  Transform* transform;
  GameObject(Shader* shader, Mesh* mesh, Transform* transform);
  ~GameObject();
  void Delete();
  
};
