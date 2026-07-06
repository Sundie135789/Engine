#pragma once
#include <string>
#include <glm/glm.hpp>
#include "transform.hpp"
#include "mesh.hpp"
#include "material.hpp"
class Gameobject{
  public:
    Gameobject(std::string name);
    void SetMesh(const Mesh& mesh);
  //  void Render();
    void SetMaterial(Material& material);
    void SetTransform(const Transform& transform);
    void SetName(const std::string& name);
    glm::mat4 getModelMatrix();
    Mesh mesh;
    Material material;
    Transform transform;
    std::string name;
    // creation
    static void CreateCube();
    static void CreatePlane();
    static void CreateDirectionalLight();
};
