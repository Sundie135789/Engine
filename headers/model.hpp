#pragma once

#include <vector>
#include "vertex.hpp"
#include <string>
struct ModelData{
  std::vector<Vertex> vertices;
  std::string texturePath;
};
class Model{
  public:
    static ModelData LoadOBJ(const char* path);
};
