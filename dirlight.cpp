#include "headers/dirlight.hpp"
DirectionalLight::DirectionalLight(glm::vec3 lightDir, glm::vec3 color){
  this->lightDir = lightDir;
  this->color = color;
}
