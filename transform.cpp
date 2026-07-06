#include "headers/transform.hpp"
Transform::Transform(){
  position = glm::vec3(0.0f);
  rotation =  glm::vec3(0.0f);
  scale =  glm::vec3(1.0f);
}
Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
  : position(position), rotation(rotation), scale(scale){}
void Transform::setPosition(glm::vec3* position){
  this->position = *position;
}
void Transform::setRotation(glm::vec3* rotation){
  this->rotation = *rotation;
}
void Transform::setScale(glm::vec3* scale){
  this->scale = *scale;
}

