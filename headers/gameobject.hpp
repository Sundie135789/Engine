#pragma once
#include <string>
#include <glm/glm.hpp>
#include "transform.hpp"
#include "mesh.hpp"
#include "material.hpp"
class Gameobject{
  public:
    Gameobject(std::string name);
    void SetMesh(Mesh *mesh);
  //  void Render();
    void SetMaterial(Material* material);
    void SetTransform(Transform *transform);
    void SetName(std::string* name);
    glm::mat4 getModelMatrix(Transform* transform);
    Mesh *mesh;
    Material *material;
    Transform *transform;
    std::string name;
    // creation
    static void CreateCube();
    static void CreatePlane();
};
