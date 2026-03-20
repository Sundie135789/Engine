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
	float posX = 0.0f;
	float posY = 0.0f;
	float posZ = 0.0f;
	float scaleX =1.0f, scaleY=1.0f, scaleZ=1.0f;
	float rotateX = 0.0f, rotateY = 0.0f, rotateZ = 0.0f;
  ~GameObject();
};
