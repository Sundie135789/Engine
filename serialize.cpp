#include "headers/serialize.hpp"

#include "headers/globals.hpp"
#include "vendor/json/json.hpp"
#include "headers/jsonconverter.hpp"
#include <fstream>
#include <iostream>
using json = nlohmann::json;
namespace Serialize{
  void LoadWorld(std::string path){
    std::ifstream file(path.c_str());
    if(!file){
      std::cerr << "Could not open file " << path << std::endl;
      std::exit(1);
    }
    json j;
    file >> j;
    gameobjects.clear();
    int nGameobjects = j["gameobjects"].size();
    for(int i = 0;i<nGameobjects;i++){
      auto go = std::make_unique<Gameobject>(j["gameobjects"][i]["name"].get<std::string>());
      json goJson = j["gameobjects"][i];
      go->SetTransform(Transform(
            goJson["transform"]["position"].get<glm::vec3>(),
            goJson["transform"]["rotation"].get<glm::vec3>(),
            goJson["transform"]["scale"].get<glm::vec3>()
            ));
      go->SetMaterial(Material(
            goJson["material"]["specularColor"].get<glm::vec3>(),
            goJson["material"]["specularStrength"].get<float>(),
            goJson["material"]["color"].get<glm::vec3>(),
            goJson["material"]["shininess"].get<float>(),
            goJson["material"]["texture"].get<std::string>(),
            goJson["material"]["shader"][0].get<std::string>(), //Vertex shader
            goJson["material"]["shader"][1].get<std::string>() //Fragment shader
            ));
      int nVertices = goJson["mesh"]["vertices"].size();
      std::cout << "\n\n" << nVertices << "\n\n";
      //for(int k = 0;k < 
    }
  }
  void SaveWorld(std::string path){
    std::ofstream file(path.c_str());
    if(!file){
      std::cerr << "Could not open file " << path << std::endl;
      std::exit(1);
    }
    json j;
    for(auto& go : gameobjects){
      json obj;
      obj["name"] = go->name;
      obj["transform"]["position"] = {go->transform.position.x, go->transform.position.y, go->transform.position.z};
      obj["transform"]["rotation"] = {go->transform.rotation.x, go->transform.rotation.y, go->transform.rotation.z};
      obj["transform"]["scale"] = {go->transform.scale.x, go->transform.scale.y, go->transform.scale.z};
      obj["material"]["specularColor"] = {go->material.specularColor.x, go->material.specularColor.y, go->material.specularColor.z};
      obj["material"]["specularStrength"] = go->material.specularStrength;
      obj["material"]["color"] = {go->material.color.x, go->material.color.y, go->material.color.z};
      obj["material"]["shininess"] = go->material.shininess;
      obj["material"]["texture"] = go->material.texture->path;
      obj["material"]["shader"] = {go->material.shader->vertexPath, go->material.shader->fragmentPath};
      obj["mesh"]["vertices"] = json::array();
      for(Vertex vertex : go->mesh.vertices){
        json v;
        v["position"] = {vertex.position.x, vertex.position.y, vertex.position.z};
        v["normal"] = {vertex.normal.x, vertex.normal.y, vertex.normal.z};
        v["uv"] = {vertex.uv.x, vertex.uv.y};
        obj["mesh"]["vertices"].push_back(v);
      }
      //std::cout << "\n\nAmount of vertices found: " << go->mesh->vertices.size() << "\n\n";
      j["gameobjects"].push_back(obj);

    }
    //Directional Light
    j["dirlight"]["lightDir"] = {mainDirLight->lightDir.x, mainDirLight->lightDir.y, mainDirLight->lightDir.z};
    j["dirlight"]["color"] = {mainDirLight->color.x, mainDirLight->color.y, mainDirLight->color.z};
    //Camera
    j["game_camera"]["fov"] = gameCamera->fov;
    j["game_camera"]["aspect"] = gameCamera->aspect;
    j["game_camera"]["nearPlane"] = gameCamera->nearPlane;
    j["game_camera"]["farPlane"] = gameCamera->farPlane;
    j["editor_camera"]["fov"] = editorCamera->fov;
    j["editor_camera"]["aspect"] = editorCamera->aspect;
    j["editor_camera"]["nearPlane"] = editorCamera->nearPlane;
    j["editor_camera"]["farPlane"] = editorCamera->farPlane;
    file << j.dump(4) << std::endl;;
  }
};
