#pragma once
#include "vertex.hpp"
#include "material.hpp"
#include "assimp/scene.h"
class Model{
  public:
  static void ProcessNode(aiNode* node, const aiScene* scene, std::vector<Vertex>& out_vertices, std::vector<unsigned int>& out_indices);
  static void LoadModel(const std::string& path, std::vector<Vertex>& out_vertices, std::vector<unsigned int>& out_indices,  Material& material);
};
