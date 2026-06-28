#include "headers/model.hpp"

#define FAST_OBJ_IMPLEMENTATION
#include "vendor/fast_obj/fast_obj.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
ModelData Model::LoadOBJ(const char* path){
  ModelData data;
  fastObjMesh* mesh = fast_obj_read(path);
  if(!mesh) {
    std::cout << "mesh == false in Model::LoadOBJ" << std::endl;
    return data;
  }
  data.vertices.reserve(mesh->index_count);
  for(unsigned int i=0;i<mesh->index_count;++i){
    fastObjIndex idx = mesh->indices[i];
    Vertex v;
    v.position = glm::make_vec3(&mesh->positions[3 * idx.p]);
    v.normal = glm::make_vec3(&mesh->normals[3 * idx.n]);
    v.uv = glm::make_vec2(&mesh->texcoords[2 * idx.t]);

    v.color = glm::vec3(1.0f);
    data.vertices.push_back(v);
  }
  if(mesh->material_count > 0 && mesh->materials[0].map_Kd != 0 ){
    unsigned int textureIndex = mesh->materials[0].map_Kd;
    data.texturePath = std::string(mesh->textures[textureIndex].name);
  }else {
    data.texturePath = "";
  }
  fast_obj_destroy(mesh);
  return data;
}
