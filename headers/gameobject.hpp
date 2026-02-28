#pragma once
#include "shader.hpp"
#include "mesh.hpp"
#include "transform.hpp"
#include <string>
class GameObject{
  public:
  Shader *shader;
  Mesh* mesh;
  Transform* transform;
  std::string name;
  void draw();
  GameObject(std::string name, Shader* shader, Mesh* mesh, Transform* transform);
  GameObject(std::string name );
  void SetShader(Shader *shader);
  void SetMesh(Mesh *mesh);
  void SetName(std::string newName);
  void SetTransform(Transform* transform);
  ~GameObject();
};
