#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class Camera {
  public:
    glm::vec3 position;
    glm::vec3 rotation;
    float fov = glm::radians(60.0f);
    float aspect;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;
    Camera(float aspect);
    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix() const;
};
