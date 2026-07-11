#pragma once
#include "vertex.hpp"
#include "material.hpp"
#include "assimp/scene.h"
class Model{
  public:
  static void ProcessNode(aiNode* node, const aiScene* scene, std::vector<Vertex>& out_vertices);
  static void LoadModel(const std::string& path, std::vector<Vertex>& out_vertices, Material& material);
};
