#include "camera.hpp"

Camera::Camera(float aspect){
  this->aspect = aspect;
  position = glm::vec3(1.0f, 1.0f, 1.0f);
  rotation = glm::vec3(1.0f);
  fov = glm::radians(60.0f);
  nearPlane = 0.1f;
  farPlane = 100.0f;
}

glm::mat4 Camera::GetViewMatrix() const{

  return glm::lookAt(position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}
glm::mat4 Camera::GetProjectionMatrix() const{
  return glm::perspective(fov, aspect, nearPlane, farPlane);
}
