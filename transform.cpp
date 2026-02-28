#include "transform.hpp"

Transform::Transform(){
  position = glm::vec3(0.0, 0.0, 0.0);
  rotation = glm::vec3(0.0 ,0.0 ,0.0);
  scale = glm::vec3(1.0, 1.0, 1.0);
}
glm::mat4 Transform::GetModelMatrix() const {
  glm::mat4 model(1.0f);
  model = glm::translate(model, position);
  model = glm::rotate(model, rotation.x, glm::vec3(1,0,0));
  model = glm::rotate(model, rotation.y, glm::vec3(0,1,0));
  model = glm::rotate(model, rotation.z, glm::vec3(0,0,1));
  model = glm::scale(model, scale);
  return model;
}

