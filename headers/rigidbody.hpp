#pragma once
#include <glm/glm.hpp>
class RigidBody{
  public:
    RigidBody();
    bool applyGravity;
    glm::vec3 velocity;
};
