#include "headers/camera.hpp"
#include <glm/gtc/matrix_transform.hpp>
Camera::Camera(){
  position = glm::vec3(0.0f, 1.0f, 3.0f);
  front = glm::vec3(0.0f, 0.0f, -1.0f);
  pitch = 0.0f;
  yaw = -90.0f;
  fov = glm::radians(60.0f);
  aspect = 2560.0f / 1920.0f;
  nearPlane = 0.1f;
  farPlane = 1000.0f;
  zoomSpeed = 2.0f;
}
Camera::Camera(float fov, float aspect, float nearPlane, float farPlane) :
  fov(fov), aspect(aspect), nearPlane(nearPlane), farPlane(farPlane)
{
  position = {0.0f, 1.0f, 3.0f};
  front = {0.0f, 0.0f, -1.0f};
  pitch = 0.0f;
  yaw = -90.0f;
  zoomSpeed = 2.0f;
}
glm::mat4 Camera::GetViewMatrix(){
  glm::mat4 view = glm::lookAt(position, position + front, glm::vec3(0.0f, 1.0f, 0.0f));
  return view;
}
glm::mat4 Camera::GetProjectionMatrix(){
  glm::mat4 projection;
  if(projectionType == ProjectionType::Perspective){
    projection = glm::perspective(fov, aspect, nearPlane, farPlane);
  }else{
    float orthoSize = fov;
    float right = orthoSize * aspect;
    projection = glm::ortho(-right, right, -orthoSize, orthoSize, nearPlane, farPlane);
  }
  return projection;
}
void Camera::ZoomIn(){
  this->fov -= glm::radians(zoomSpeed);
  if(this->fov < glm::radians(1.0f)){
    this->fov = glm::radians(1.0f);
  }
}
void Camera::ZoomOut(){
  this->fov += glm::radians(zoomSpeed);
  if(this->fov > glm::radians(120.0f)){
    this->fov = glm::radians(120.0f);
  }
}
