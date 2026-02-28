#include "camera.hpp"

Camera::Camera(float aspect){
  this->aspect = aspect;
  position = glm::vec3(0.0f, 0.0f, 3.0f);
  rotation = glm::vec3(0.0f);
  fov = glm::radians(60.0f);
  nearPlane = 0.1f;
  farPlane = 100.0f;
}

glm::mat4 Camera::GetViewMatrix() const{
  glm::mat4 view(1.0f);
  view = glm::rotate(view, rotation.x, glm::vec3(1,0,0));
  view = glm::rotate(view, rotation.y, glm::vec3(0,1,0));
  view = glm::rotate(view, rotation.z, glm::vec3(0,0,1));
  view = glm::translate(view, -position);
  return view;
}
glm::mat4 Camera::GetProjectionMatrix() const{
  return glm::perspective(fov, aspect, nearPlane, farPlane);
}
