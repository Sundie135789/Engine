#pragma once
#include <glm/glm.hpp>
class DirectionalLight{
  public:
    DirectionalLight(glm::vec3 lightDir, glm::vec3 color);
    glm::vec3 lightDir;
    glm::vec3 color;
};
