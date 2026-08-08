#include "headers/rigidbody.hpp"
RigidBody::RigidBody(){
  this->velocity = glm::vec3(0.0f);
  this->applyGravity = true;
}
