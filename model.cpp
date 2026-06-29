#include "headers/model.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>

Model::Model(const char* path) {
    LoadModel(path);
}

void Model::LoadModel(const char* path) {
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(
        path,
        aiProcess_Triangulate |
        aiProcess_GenNormals |
        aiProcess_FlipUVs
    );

    if (!scene || !scene->mRootNode) {
        std::cerr << "Assimp error: " << importer.GetErrorString() << std::endl;
        return;
    }

    ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene) {
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        ProcessMesh(mesh, scene);
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        ProcessNode(node->mChildren[i], scene);
    }
}

void Model::ProcessMesh(aiMesh* mesh, const aiScene* scene) {
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];

        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            unsigned int idx = face.mIndices[j];

            Vertex v{};

            // position
            v.position.x = mesh->mVertices[idx].x;
            v.position.y = mesh->mVertices[idx].y;
            v.position.z = mesh->mVertices[idx].z;

            // normals
            if (mesh->HasNormals()) {
                v.normal.x = mesh->mNormals[idx].x;
                v.normal.y = mesh->mNormals[idx].y;
                v.normal.z = mesh->mNormals[idx].z;
            }

            // UVs
            if (mesh->mTextureCoords[0]) {
              v.uv = glm::vec2(
                  mesh->mTextureCoords[0][idx].x,
                  mesh->mTextureCoords[0][idx].y
                  );
            }else {
              v.uv = glm::vec2(0.0f);
            }
            v.color = glm::vec3(1.0f);
            vertices.push_back(v);
        }
    }
}
