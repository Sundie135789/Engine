#pragma once
#include <glm/glm.hpp>
class Camera{
  public:
    Camera();
    glm::vec3 position;
    glm::vec3 front;
    float pitch;
    float yaw;
    float fov, aspect, nearPlane, farPlane;
    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjectionMatrix();
};
