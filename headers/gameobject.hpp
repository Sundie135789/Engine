#pragma once
#include "shader.hpp"
#include "mesh.hpp"
#include "transform.hpp"
#include "camera.hpp"
#include <string>
#include <stdbool.h>
class GameObject{
  public:
  Shader *shader;
  Mesh* mesh;
  Transform* transform;
  std::string name;
  void draw(Camera& camera);
	bool menuOpen = false;
  GameObject(std::string name, Shader* shader, Mesh* mesh, Transform* transform);
  GameObject(std::string name);
	void toggleObjectMenu();
  void SetShader(Shader *shader);
  void SetMesh(Mesh *mesh);
  void SetName(std::string newName);
  void SetTransform(Transform* transform);
	char XBuffer[128];
	char YBuffer[128];
	char ZBuffer[128];
  ~GameObject();
};
