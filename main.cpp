// Graphics header
#include <GL/glew.h>
//Custom headers
#include "headers/renderer.hpp"
#include "headers/ui.hpp"
#include "headers/input.hpp"
#include "headers/globals.hpp"
#include "headers/serialize.hpp"
// C++ headers
#include <iostream>
//switch to submesh system
// add settings pop up in ui.cpp
// press key combo to run the actual game. press key combo to switch back to normal editor.
//
// BEST LINE: ui.cpp -> around line 55, if condition for combo dropdown.
// at the start, load 
int main(){
  UI::Init(mainWindow->GetWindowHandle());
  Serialize::LoadEmptyWorld();
  /* Do not ship with this line */// Serialize::LoadWorld("worlds/first.json");
  Renderer renderer;
  renderer.SetLight(mainDirLight);
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
      Input::HandleGameInput(mainWindow.get(), gameCamera);
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
    if(selected != -1){
      UI::LoadInspector();
    }
    UI::Menubar();
    UI::Hierarchy();
    UI::EndFrame();
    mainWindow->SwapBuffers();
  }
  UI::SaveAndExit();
  mainWindow->Terminate();
  glfwTerminate();
  return 0;
}
