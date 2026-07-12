#include "headers/model.hpp"
#include "headers/assetmanager.hpp"
#include "headers/vertex.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/types.h>
#include <glm/ext/vector_float3.hpp>
#include <iostream>
#include <glm/glm.hpp>
void Model::ProcessNode(aiNode* node, const aiScene* scene, std::vector<Vertex>& out_vertices){
        // Unpack all sub-meshes attached to this specific hierarchy node
        for (unsigned int i = 0; i < node->mNumMeshes; i++) {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            
            // Loop through every face (triangle) in the sub-mesh
            for (unsigned int f = 0; f < mesh->mNumFaces; f++) {
                aiFace face = mesh->mFaces[f];
                
                // Unpack the vertices sequentially for your flat glDrawArrays layout
                for (unsigned int v = 0; v < face.mNumIndices; v++) {
                    unsigned int index = face.mIndices[v];
                    Vertex vertex{};

                    // 1. Position
                    vertex.position.x = mesh->mVertices[index].x;
                    vertex.position.y = mesh->mVertices[index].y;
                    vertex.position.z = mesh->mVertices[index].z;

                    // 2. Normal
                    if (mesh->HasNormals()) {
                        vertex.normal.x = mesh->mNormals[index].x;
                        vertex.normal.y = mesh->mNormals[index].y;
                        vertex.normal.z = mesh->mNormals[index].z;
                    }

                    // 3. Texture Coordinates (UVs)
                    if (mesh->mTextureCoords[0]) { // Check first UV channel
                        vertex.uv.x = mesh->mTextureCoords[0][index].x;
                        // Flip Y-axis: FBX layout maps top-to-bottom, OpenGL processes bottom-to-top
                        vertex.uv.y = mesh->mTextureCoords[0][index].y;
                    } else {
                        vertex.uv = glm::vec2(0.0f);
                    }

                    out_vertices.push_back(vertex);
                }
            }
        }

        // Recursively dig down into any nested child nodes
        for (unsigned int i = 0; i < node->mNumChildren; i++) {
            ProcessNode(node->mChildren[i], scene, out_vertices);
        }
    }

void Model::LoadModel(const std::string& path, std::vector<Vertex>& out_vertices, Material& material){
  Assimp::Importer importer;
  const aiScene* scene = importer.ReadFile(path,
      aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);
  out_vertices.clear();
  ProcessNode(scene->mRootNode, scene, out_vertices);
  if(scene->HasMaterials() && scene->mNumMaterials > 0){
    aiMaterial* srcMat = scene->mMaterials[0];
    aiColor3D diffuseColor(1.0f, 1.0f, 1.0f);
    aiColor3D specularColor(1.0f, 1.0f, 1.0f);
    float shininess = 32.0f;
    srcMat->Get(AI_MATKEY_COLOR_DIFFUSE, diffuseColor);
    srcMat->Get(AI_MATKEY_COLOR_SPECULAR, specularColor);
    srcMat->Get(AI_MATKEY_SHININESS, shininess);
    if(shininess <= 0.1f){
      shininess = 32.0f;
    }
    material.color = glm::vec3(diffuseColor.r, diffuseColor.g, diffuseColor.b);
    material.specularColor = glm::vec3(specularColor.r, specularColor.g, specularColor.b);
    material.shininess = shininess;
    material.specularStrength = 3.0f;
    aiString texturePath;
    if(srcMat->GetTextureCount(aiTextureType_DIFFUSE) > 0 &&
        srcMat->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath) == AI_SUCCESS){
      std::string textureFilename = texturePath.C_Str();
      std::string fullPath = textureFilename;
      fullPath = fullPath.substr(fullPath.find_last_of("/\\") + 1);
      fullPath = "assets/textures/" + fullPath;
      std::cout << "Resolved texture path: " << fullPath << "\n\n";
      material.texture = AssetManager::GetTexture(fullPath);
    }
    material.setShader(Shader("shaders/basic.vert", "shaders/basic.frag"));
    std::cout << "\n\n" << material.texture->path << "\n\n";
  }
}
