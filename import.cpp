#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include "headers/global.hpp"
#include "headers/mesh.hpp"
#include "headers/transform.hpp"
#include "headers/shader.hpp"
#include "headers/gameobject.hpp"

std::vector<float> verts;

void loadModel(const char* path){

    verts.clear(); // IMPORTANT

    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(
        path,
        aiProcess_Triangulate
    );

    if(!scene || !scene->mRootNode) return;

    float r = 1.0f, g = 1.0f, b = 1.0f;

    for(unsigned int m = 0; m < scene->mNumMeshes; m++){
        aiMesh* aimesh = scene->mMeshes[m];

        // get material color
        if(aimesh->mMaterialIndex >= 0){
            aiMaterial* mat = scene->mMaterials[aimesh->mMaterialIndex];
            aiColor3D color(1,1,1);
            mat->Get(AI_MATKEY_COLOR_DIFFUSE, color);

            r = color.r;
            g = color.g;
            b = color.b;
        }

        for(unsigned int f = 0; f < aimesh->mNumFaces; f++){
            aiFace face = aimesh->mFaces[f];

            for(unsigned int i = 0; i < face.mNumIndices; i++){
                int idx = face.mIndices[i];

                aiVector3D v = aimesh->mVertices[idx];

                verts.push_back(v.x);
                verts.push_back(v.y);
                verts.push_back(v.z);
            }
        }
    }

    Mesh *mesh = new Mesh(verts.data(), verts.size() / 3, false);

    Shader* shader = new Shader("shaders/plain.vert", "shaders/plain.frag");
    shader->SetColor(r, g, b);
		Transform* transform = new Transform();
		GameObject* object = new GameObject("Untitled gltf object", shader, mesh, transform);
		gameobjects.push_back(object);
}
