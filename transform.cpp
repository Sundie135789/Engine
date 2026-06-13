#include "headers/transform.hpp"
Transform::Transform(){
  position = glm::vec3(0.0f);
  rotation =  glm::vec3(0.0f);
  scale =  glm::vec3(1.0f);
  velocity =  glm::vec3(0.0f);
}
void Transform::setPosition(glm::vec3* position){
  this->position = *position;
}
void Transform::setRotation(glm::vec3* rotation){
  this->rotation = *rotation;
}
void Transform::setScale(glm::vec3* scale){
  this->scale = *scale;
}
void Transform::setVelocity(glm::vec3* velocity){
  this->velocity = *velocity;
}
