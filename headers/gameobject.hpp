#pragma once
#include <string>
#include <glm/glm.hpp>
#include "transform.hpp"
#include "mesh.hpp"
#include "material.hpp"
#include "rigidbody.hpp"
class Gameobject{
  public:
    Gameobject(std::string name);
    void SetMesh(const Mesh& mesh);
  //  void Render();
    void SetMaterial(const Material& material);
    void SetTransform(const Transform& transform);
    void SetRigidbody(const RigidBody& rigidBody);
    void SetName(const std::string& name);
    glm::mat4 getModelMatrix();
    void setModelMatrix(const glm::mat4& modelMatrix);
    Mesh mesh;
    Material material;
    Transform transform;
    std::string name;
    RigidBody rigidbody;
    // creation
    static void CreateCube();
    static void CreatePlane();
    static void CreateDirectionalLight();
};
