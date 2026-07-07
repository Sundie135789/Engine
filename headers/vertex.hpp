#pragma once
#include <glm/glm.hpp>
struct Vertex{
  Vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 uv) : position(position), normal(normal), uv(uv) {}
  Vertex() {};
  glm::vec3 position;
  glm::vec3 normal;
  glm::vec2 uv;
};
