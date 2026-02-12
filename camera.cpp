#include "headers/camera.hpp"
#include <glm/gtc/matrix_transform.hpp>
Camera::Camera(){
  this->aspect = 16.0f/9.0f;
  this->far = 100.0f;
  this->near = 0.1f;
  this->fov = 45.0f;
  cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
  cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
  cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
  this->viewMatrix = getViewMatrix();
}
glm::mat4 Camera::getProjectionMatrix(){
  glm::mat4 projection = glm::perspective(glm::radians(this->fov), aspect, near, far);
  return projection;
}
glm::mat4 Camera::getViewMatrix(){
  glm::mat4 viewMatrix = glm::lookAt(this->cameraPos, this->cameraTarget, this->cameraUp);
  return viewMatrix;
}
void Camera::updateViewMatrix(){
  glm::vec3 forward = glm::vec3(0.0f, 0.0f, -1.0f);
  this->viewMatrix = glm::lookAt(this->cameraPos, cameraPos + forward, this->cameraUp);
}
