// Graphics header
#include <GL/glew.h>
//Custom headers
#include "headers/renderer.hpp"
#include "headers/assetmanager.hpp"
#include "headers/ui.hpp"
#include "headers/input.hpp"
#include "headers/globals.hpp"
#include "headers/serialize.hpp"
#include "vendor/imguizmo/ImGuizmo.h"
// switch to FBO
// input manager GUI
// add ability to import albedo, roughness, metallic maps.
// add gamma correction, light clamping. 
// main.cpp line 49 complete model loading code for fbx. 
int main(){
  UI::Init(mainWindow->GetWindowHandle());
  Input::PopulateKeybinds();
  Serialize::LoadEmptyWorld();
  /* Do not ship with this line */// Serialize::LoadWorld("worlds/first.json");
  Renderer renderer;
  renderer.SetLight(mainDirLight);
  //std::vector<Vertex> tempvertices;
  //Material material;
  /*Model::LoadModel("assets/models/Untitled.fbx", vertices, material);
  Mesh mesh(vertices);
  std::unique_ptr<Gameobject> gameobject = std::make_unique<Gameobject>("My gameobject");
  gameobject->SetMesh(mesh);
  gameobject->SetTransform(Transform());
  gameobject->SetMaterial(material);
  
  gameobjects.push_back(std::move(gameobject));*/
  float deltaTime, lastFrame = 0.0f, currentFrame;
  float fps, titleTimer = 0.0f;
  int fpsFrameCount = 0;
  while(!mainWindow->ShouldClose()){
    mainWindow->PollEvents();
    if(UI::triggerFilePick){
      UI::triggerFilePick = false;
      std::string texturePath = UI::OpenFilepicker();
      gameobjects[selected]->material.albedoTexture = AssetManager::GetTexture(texturePath);
    }
    /*if(UI::triggerModelPick){
      UI::triggerModelPick = false;
      std::string modelPath = UI::OpenModelpicker();
      std::vector<Vertex> vertices;
      Material material;
      Model::LoadModel(modelPath, vertices, material);
      std::unique_ptr<Gameobject> newGo = std::make_unique<Gameobject>("Imported Model");
      newGo->SetMesh(Mesh(vertices));
      newGo->SetMaterial(material);
      newGo->SetTransform(Transform());
      gameobjects.push_back(std::move(newGo));
    }*/
    currentFrame = mainWindow->GetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    titleTimer += deltaTime;
    fpsFrameCount++;
    if(titleTimer >= 0.5f){
      float averageFPS = fpsFrameCount / titleTimer;
      mainWindow->setTitle("FPS: " + std::to_string(static_cast<int>(averageFPS)));
      titleTimer = 0.0f;
      fpsFrameCount = 0.0f;
    }
    UI::BeginFrame();
    ImGuizmo::BeginFrame();
    Renderer::NewFrame();
    if(g_EngineState == EngineState::Playing){
      renderer.SetCamera(gameCamera);
      Input::HandleGameInput(mainWindow.get(), gameCamera, deltaTime, lastX, lastY, firstMouse);
    }else if(g_EngineState == EngineState::Editing){
      renderer.SetCamera(editorCamera);
        Input::HandleEngineInput(
          mainWindow.get(), editorCamera, deltaTime, lastX, lastY, firstMouse
        );
    }
    for(auto& go : gameobjects){
      renderer.Submit(go.get());
    }

    if(g_EngineState == EngineState::Editing){
      if(selected != -1)
      {
        UI::LoadInspector();
        UI::DrawTransformGizmo(gameobjects[selected].get(), editorCamera->GetViewMatrix(), editorCamera->GetProjectionMatrix());
      }
      UI::Hierarchy();
      UI::Menubar();
    }
    UI::EndFrame();
    mainWindow->SwapBuffers();
  }
  UI::SaveAndExit();
  AssetManager::Cleanup();
  mainWindow->Terminate();
  glfwTerminate();
  return 0;
}
