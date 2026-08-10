#include "headers/rigidbody.hpp"
RigidBody::RigidBody(){
  this->velocity = glm::vec3(0.0f);
  this->applyGravity = true;
}
RigidBody::RigidBody(bool applyGravity, glm::vec3 velocity){
  this->applyGravity = applyGravity;
  this->velocity = velocity;
}
