#include "headers/serialize.hpp"
#include "headers/dirlight.hpp"
#include "headers/ui.hpp"
#include "headers/log.hpp"
#include "headers/assetmanager.hpp"
#include "headers/globals.hpp"
#include "vendor/json/json.hpp"
#include "headers/jsonconverter.hpp"
#include <fstream>
#include <iostream>
using json = nlohmann::json;
namespace Serialize{
  void ExitEngine(int code){

    UI::SaveAndExit();
    AssetManager::Cleanup();
    // Delete cameras
    if(editorCamera)
      delete editorCamera;
    if(gameCamera)
      delete gameCamera;
    
    Log::Clear();
    mainWindow->Terminate();
    std::exit(code);
  }
  void LoadEmptyWorld(){
    mainDirLight = new DirectionalLight({-0.5f, -1.0f, -0.8f}, {1.0f, 1.0f, 1.0f});
    editorCamera = new Camera(glm::radians(60.0f), 2560.0f/1920.0f, 0.1f, 100.0f);
    gameCamera = new Camera(glm::radians(60.0f), 2560.0f/1920.0f, 0.1f, 100.0f);
    editorCamera->position = {0.0f, 1.0f, 3.0f};
    gameCamera->position = {0.0f, 1.0f, 10.0f};
    gameCamera->pitch = 20;
    gameobjects.clear();
  }
  void LoadWorld(std::string path){
    std::ifstream file(path.c_str());
    std::cout << "The path is: *" << path << "*\n\n";
    if(!file){
      std::cerr << "Could not open file " << path << std::endl;
      Serialize::ExitEngine(1);
    }
    json j;
    file >> j;
    gameobjects.clear();
    int nGameobjects = j["gameobjects"].size();
    for(int i = 0;i<nGameobjects;i++){
      auto go = std::make_unique<Gameobject>(j["gameobjects"][i]["name"].get<std::string>());
      json goJson = j["gameobjects"][i];
      Transform transform(
            goJson["transform"]["position"].get<glm::vec3>(),
            goJson["transform"]["rotation"].get<glm::vec3>(),
            goJson["transform"]["scale"].get<glm::vec3>()
            );
      go->SetTransform(transform);
      Material material(
            goJson["material"]["albedoTexture"].get<std::string>(),
            goJson["material"]["metallicTexture"].get<std::string>(),
            goJson["material"]["roughnessTexture"].get<std::string>(),
            goJson["material"]["albedoValue"].get<glm::vec3>(),
            goJson["material"]["roughnessValue"].get<float>(),
            goJson["material"]["metallicValue"].get<float>(),
            goJson["material"]["shader"][0].get<std::string>(), //Vertex shader
            goJson["material"]["shader"][1].get<std::string>() //Fragment shader

          );
      go->SetMaterial(material);
      int nVertices = goJson["mesh"]["vertices"].size();
      std::vector<Vertex> vertices;
      std::vector<unsigned int> indices;
      for(int k = 0;k < nVertices; k++){
        goJson["mesh"]["vertices"][k];
        vertices.push_back(Vertex(
               goJson["mesh"]["vertices"][k]["position"].get<glm::vec3>(),
               goJson["mesh"]["vertices"][k]["normal"].get<glm::vec3>(),
               goJson["mesh"]["vertices"][k]["uv"].get<glm::vec2>()
              ));

      }
      int nIndices = goJson["mesh"]["indices"].size();
      indices.resize(nIndices);
      for(int i=0;i<nIndices;i++){
        indices[i] = goJson["mesh"]["indices"][i];
      }
      go->SetMesh(Mesh(vertices, indices));
      gameobjects.push_back(std::move(go));
      
    } mainDirLight = new DirectionalLight(
          j["dirlight"]["lightDir"].get<glm::vec3>(),
          j["dirlight"]["color"].get<glm::vec3>()
          );
      gameCamera = new Camera(
            j["game_camera"]["fov"].get<float>(),
            j["game_camera"]["aspect"].get<float>(),
            j["game_camera"]["nearPlane"].get<float>(),
            j["game_camera"]["farPlane"].get<float>()
          );
      editorCamera = new Camera(
            j["editor_camera"]["fov"].get<float>(),
            j["editor_camera"]["aspect"].get<float>(),
            j["editor_camera"]["nearPlane"].get<float>(),
            j["editor_camera"]["farPlane"].get<float>()
          );
      // Restore settings
      settings.graphics.chromaticAbberation = j["settings"]["graphics"]["chromaticAbberation"].get<bool>();
      settings.graphics.chromaticAbberationStrength = j["settings"]["graphics"]["chromaticAbberationStrength"].get<float>();
      settings.graphics.vsync = j["settings"]["graphics"]["vsync"].get<bool>();
      settings.controls.camera_speed = j["settings"]["controls"]["camera_speed"].get<float>();
      settings.controls.sensitivity = j["settings"]["controls"]["mouse_sensitivity"].get<float>();

  }
  void SaveWorld(std::string path){
    std::ofstream file(path.c_str());
    if(!file){
      std::cerr << "Could not open file " << path << std::endl;
      Serialize::ExitEngine(1);
    }
    json j;
    for(auto& go : gameobjects){
      if(!go) continue;
      json obj;
      obj["name"] = go->name;
      obj["transform"]["position"] = {go->transform.position.x, go->transform.position.y, go->transform.position.z};
      obj["transform"]["rotation"] = {go->transform.rotation.x, go->transform.rotation.y, go->transform.rotation.z};
      obj["transform"]["scale"] = {go->transform.scale.x, go->transform.scale.y, go->transform.scale.z};
      obj["material"]["albedoTexture"] = go->material.albedoTexture ? go->material.albedoTexture->path : "";
      obj["material"]["metallicTexture"] = go->material.metallicTexture ? go->material.metallicTexture->path : "";
      obj["material"]["roughnessTexture"] = go->material.roughnessTexture ? go->material.roughnessTexture->path : "";
      obj["material"]["albedoValue"] = {go->material.albedoValue.x, go->material.albedoValue.y, go->material.albedoValue.z};
      obj["material"]["roughnessValue"] = go->material.roughnessValue;
      obj["material"]["metallicValue"] = go->material.metallicValue;

      obj["material"]["shader"] = {go->material.shader.vertexPath, go->material.shader.fragmentPath};
      obj["mesh"]["vertices"] = json::array();
      for(Vertex vertex : go->mesh.vertices){
        json v;
        v["position"] = {vertex.position.x, vertex.position.y, vertex.position.z};
        v["normal"] = {vertex.normal.x, vertex.normal.y, vertex.normal.z};
        v["uv"] = {vertex.uv.x, vertex.uv.y};
        obj["mesh"]["vertices"].push_back(v);
      }
      for(unsigned int index : go->mesh.indices){
        obj["mesh"]["indices"].push_back(index);
      }
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
    //Settings
    j["settings"]["graphics"]["chromaticAbberation"] = settings.graphics.chromaticAbberation;
    j["settings"]["graphics"]["chromaticAbberationStrength"] = settings.graphics.chromaticAbberationStrength;
    j["settings"]["graphics"]["vsync"] = settings.graphics.vsync;
    j["settings"]["controls"]["mouse_sensitivity"] = settings.controls.sensitivity;
    j["settings"]["controls"]["camera_speed"] = settings.controls.camera_speed;
    file << j.dump(0) << std::endl;;
    //file << j.dump(0) << std::endl;;
  }
};
