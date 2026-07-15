// Graphics header
#include <GL/glew.h>
//Custom headers
#include "headers/renderer.hpp"
#include "headers/assetmanager.hpp"
#include "headers/ui.hpp"
#include "headers/input.hpp"
#include "headers/globals.hpp"
#include "headers/serialize.hpp"
// C++ headers
// do os native file picker
// Import model, textuers, settings, all UI.
// only image texture models allowed
#include <iostream>
int main(){
  UI::Init(mainWindow->GetWindowHandle());
   
  Serialize::LoadEmptyWorld();
  /* Do not ship with this line */// Serialize::LoadWorld("worlds/first.json");
  Renderer renderer;
  renderer.SetLight(mainDirLight);
  std::vector<Vertex> vertices;
  Material material;
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
    GLenum err;
    while((err = glGetError()) != GL_NO_ERROR){
      std::cout << "OpenGL error flag detected: " << err << std::endl;
    }
    if(g_EngineState == EngineState::Editing){
      if(selected != -1)
        UI::LoadInspector();
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
