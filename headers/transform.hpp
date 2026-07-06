#pragma once
#include <glm/glm.hpp>

class Transform{
  public:
  glm::vec3 position;
  glm::vec3 rotation;
  glm::vec3 scale;
  Transform();
  Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
  void setPosition(glm::vec3* position);
  void setRotation(glm::vec3* rotation);
  void setScale(glm::vec3* scale);
};

