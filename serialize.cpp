#include "headers/serialize.hpp"
#include "headers/globals.hpp"
#include "vendor/json/json.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>
using json = nlohmann::json;
namespace Serialize{
  void LoadWorld(std::string path){
    
  }
  void SaveWorld(std::string path){
    std::ofstream file(path.c_str());
    if(!file){
      std::cerr << "Could not open file " << path << std::endl;
      std::exit(1);
    }
    json j;
    for(Gameobject* go : gameobjects){
      if(!go || !go->transform || !go->material || !go->mesh || !go->material->texture || go->material->texture->path.empty()){
        std::cout << "\n\nGameobject saving gone wrong.\n" << std::endl;
        std::exit(1);
      }
      if(!go->material->shader){
        std::cerr << "\n\nShader pointer is null" << std::endl;
        std::exit(1);
      }
      json obj;
      obj["name"] = go->name;
      obj["transform"]["position"] = {go->transform->position.x, go->transform->position.y, go->transform->position.z};
      obj["transform"]["rotation"] = {go->transform->rotation.x, go->transform->rotation.y, go->transform->rotation.z};
      obj["transform"]["scale"] = {go->transform->scale.x, go->transform->scale.y, go->transform->scale.z};
      obj["material"]["specularColor"] = {go->material->specularColor.x, go->material->specularColor.y, go->material->specularColor.z};
      obj["material"]["specularStrength"] = go->material->specularStrength;
      obj["material"]["color"] = {go->material->color.x, go->material->color.y, go->material->color.z};
      obj["material"]["shininess"] = go->material->shininess;
      obj["material"]["texture"] = go->material->texture->path;
      obj["material"]["shader"] = {go->material->shader->vertexPath, go->material->shader->fragmentPath};

      j["gameobjects"].push_back(obj);
    }

    file << std::setw(4) << j<< std::endl;;
  }
};
