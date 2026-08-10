#pragma once
#include <glm/glm.hpp>
class RigidBody{
  public:
    RigidBody();
    RigidBody(bool applyGravity, glm::vec3 velocity);
    bool applyGravity;
    glm::vec3 velocity;
};
