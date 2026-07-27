#include "headers/model.hpp"
#include "headers/assetmanager.hpp"
#include "headers/vertex.hpp"
#include "headers/log.hpp"
#include <assimp/Importer.hpp>
#include <assimp/material.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/types.h>
#include <glm/ext/vector_float3.hpp>
#include <glm/glm.hpp>
#include <filesystem>
void Model::ProcessNode(aiNode* node, const aiScene* scene, std::vector<Vertex>& out_vertices, std::vector<unsigned int>& out_indices){
        // Unpack all sub-meshes attached to this specific hierarchy node
        for (unsigned int i = 0; i < node->mNumMeshes; i++) {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            unsigned int baseIndex = static_cast<unsigned int>(out_vertices.size());
            for(unsigned int v = 0; v< mesh->mNumVertices;v++){
              Vertex vertex{};
              vertex.position.x = mesh->mVertices[v].x;
              vertex.position.y = mesh->mVertices[v].y;
              vertex.position.z = mesh->mVertices[v].z;
              if(mesh->HasNormals()){
                vertex.normal.x = mesh->mNormals[v].x;
                vertex.normal.y = mesh->mNormals[v].y;
                vertex.normal.z = mesh->mNormals[v].z;
              }
              if(mesh->mTextureCoords[0]){
                vertex.uv.x = mesh->mTextureCoords[0][v].x;
                vertex.uv.y = mesh->mTextureCoords[0][v].y;
              } else{
                vertex.uv = glm::vec3(0.0f);
              }
              out_vertices.push_back(vertex);
            }
            for(unsigned int f = 0;f < mesh->mNumFaces;f++){
              aiFace face = mesh->mFaces[f];
              for(unsigned int j = 0;j<face.mNumIndices;j++){
                out_indices.push_back(baseIndex + face.mIndices[j]);
              }
            }
        }

        // Recursively dig down into any nested child nodes
        for (unsigned int i = 0; i < node->mNumChildren; i++) {
            ProcessNode(node->mChildren[i], scene, out_vertices, out_indices);
        }
    }

void Model::LoadModel(const std::string& path, std::vector<Vertex>& out_vertices,std::vector<unsigned int>& out_indices,  Material& material){
  if(!std::filesystem::exists(std::filesystem::path(path))){
    Log::Fatal("[ERROR] Could not find model: " + path + '\n');
    std::exit(1);
  }
  Assimp::Importer importer;
  const aiScene* scene = importer.ReadFile(path,
      aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);
  out_vertices.clear();
  out_indices.clear();
  ProcessNode(scene->mRootNode, scene, out_vertices, out_indices);
  if(scene->HasMaterials() && scene->mNumMaterials > 0){
    aiMaterial* srcMat = scene->mMaterials[0];
    aiColor3D baseColor(1.0f, 1.0f, 1.0f);
    float roughness = 0.5f;
    float metallic = 0.0f;
    srcMat->Get(AI_MATKEY_BASE_COLOR, baseColor);
    srcMat->Get(AI_MATKEY_ROUGHNESS_FACTOR, roughness);
    srcMat->Get(AI_MATKEY_METALLIC_FACTOR, metallic);
    material.setAlbedoValue(glm::vec3(baseColor.r, baseColor.g, baseColor.b));
    material.setRoughnessValue(roughness);
    material.setMetallicValue(metallic);
    aiString texturePath;
    if(srcMat->GetTextureCount(aiTextureType_DIFFUSE) > 0 &&
        srcMat->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath) == AI_SUCCESS){

      std::string textureFilename = texturePath.C_Str();
      material.setAlbedoPath(textureFilename);
    }
    if(srcMat->GetTextureCount(aiTextureType_METALNESS) > 0 &&
        srcMat->GetTexture(aiTextureType_METALNESS, 0, &texturePath) == AI_SUCCESS){
      std::string textureFilename = texturePath.C_Str();
      material.setMetallicPath(textureFilename);
    }
    if(srcMat->GetTextureCount(aiTextureType_DIFFUSE_ROUGHNESS) > 0 &&
        srcMat->GetTexture(aiTextureType_DIFFUSE_ROUGHNESS, 0, &texturePath) == AI_SUCCESS){
      std::string textureFilename = texturePath.C_Str();
      material.setRoughnessPath(textureFilename);
    }
    material.setShader(Shader("shaders/basic.vert", "shaders/basic.frag"));
  }
}
