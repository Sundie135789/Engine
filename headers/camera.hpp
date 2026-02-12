#pragma once
#include <glm/glm.hpp>

class Camera{
  public:
  //members
  glm::vec3 cameraPos;
  glm::vec3 cameraTarget;
  glm::vec3 cameraUp;
  glm::mat4 viewMatrix;
  float aspect, fov, near, far;
  Camera();
  glm::mat4 getProjectionMatrix();
  glm::mat4 getViewMatrix();
  void updateViewMatrix();
};
