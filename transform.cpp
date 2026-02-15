#include "headers/transform.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
glm::mat4 Transform::getModelMatrix() const{
  glm::mat4 model(1.0f);
  model = glm::translate(model,position);
  model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1,0,0));
  model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0,1,0));
  model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0,0,1));
  model = glm::scale(model, scale);
  return model;
}
Transform::Transform(glm::vec3* position, glm::vec3* rotation, glm::vec3* scale) : position(*position), rotation(*rotation), scale(*scale){}
Transform::Transform(): position(glm::vec3(0.0f, 0.0f,0.0f)), rotation(glm::vec3(0.0f,0.0f,0.0f)), scale(glm::vec3(1.0f,1.0f,1.0f)){}
