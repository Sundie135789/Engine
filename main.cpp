// Graphics header
#include <GL/glew.h>
#include <cstdlib>
//Custom headers
#include "headers/renderer.hpp"
#include "headers/assetmanager.hpp"
#include "headers/ui.hpp"
#include "headers/input.hpp"
#include "headers/globals.hpp"
#include "headers/serialize.hpp"
#include "headers/model.hpp"
#include "vendor/imguizmo/ImGuizmo.h"
// compile, and fix memory leaks
// fix segmentation fault on saving world
// allow copy pasting of gameobjects in hierarchy
// fix model loading texture importing
int main(){
  UI::Init(mainWindow->GetWindowHandle());
  Input::PopulateKeybinds();
  Renderer::FBOSetup();
  Serialize::LoadEmptyWorld();
  /* Do not ship with this line */// Serialize::LoadWorld("worlds/first.json");
  Renderer renderer;
  renderer.SetLight(mainDirLight);
  std::vector<Vertex> tempVertices;
  std::vector<unsigned int> tempIndices;
  Material material;
  /*Model::LoadModel("/home/paaji/Downloads/Novulari.fbx", tempVertices,tempIndices,  material);
  Mesh mesh(tempVertices, tempIndices);
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
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glEnable(GL_DEPTH_TEST);
    Renderer::NewFrame();

    if(UI::triggerFilePick){
      UI::triggerFilePick = false;
      std::string texturePath = UI::OpenFilepicker();
      gameobjects[selected]->material.albedoTexture = AssetManager::GetTexture(texturePath);
    }
    if(UI::triggerModelPick){
      UI::triggerModelPick = false;
      std::string modelPath = UI::OpenModelpicker();
      if(!modelPath.empty()){
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        Material material;
        Model::LoadModel(modelPath, vertices, indices, material);
        std::unique_ptr<Gameobject> newGo = std::make_unique<Gameobject>((model_untitled_number == 0) ? "Imported Model"
            : "Imported Model " + std::to_string(model_untitled_number));
        newGo->SetMesh(Mesh(vertices, indices));
        newGo->SetMaterial(material);
        newGo->SetTransform(Transform());
        gameobjects.push_back(std::move(newGo));
        model_untitled_number++;
      }
    }
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

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    Renderer::SetGraphicsUniforms();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureColorBuffer);
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    UI::BeginFrame();
    ImGuizmo::BeginFrame();
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
  Serialize::ExitEngine(EXIT_SUCCESS);
  return 0;
}
