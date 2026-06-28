// Graphics header
#include <GL/glew.h>
#include <GL/gl.h>
//Custom headers
#include "headers/shader.hpp"
#include "headers/mesh.hpp"
#include "headers/texture.hpp"
#include "headers/transform.hpp"
#include "headers/gameobject.hpp"
#include "headers/renderer.hpp"
#include "headers/material.hpp"
#include "headers/ui.hpp"
#include "headers/camera.hpp"
#include "headers/dirlight.hpp"
#include "headers/window.hpp"
#include "headers/input.hpp"
// C++ headers
#include <vector>
#include <iostream>
#include <memory>
// right click to do free movement, only if in engine mode.
// convert UI to zTheme style + testing

std::unique_ptr<Window> mainWindow = std::make_unique<Window>(2560, 1920, "Game Engine - x64");
std::vector<Gameobject*> gameobjects;
Camera* editorCamera = new Camera();
Camera*gameCamera = new Camera();
float lastX, lastY;
bool firstMouse = true;
bool gameObjectSelected = false;
// TODO replace with enum EngineState or EngineMode
bool playing = false;
int main(){
  UI::Init(mainWindow->GetWindowHandle());
  std::cout << "GLFWwindow created successfully!\n";
  Renderer renderer;
  DirectionalLight light(glm::vec3(-0.5f, -1.0f, -0.8f), glm::vec3(1.0f, 1.0f, 1.0f));
  renderer.SetLight(&light);
  
  std::vector<Vertex> vertices = {

    // FRONT (+Z)
    { {-0.5f,-0.5f, 0.5f}, {0,0,1}, {0.6f,0.2f,0.8f}, {0,0} },
    { { 0.5f,-0.5f, 0.5f}, {0,0,1}, {0.6f,0.2f,0.8f}, {1,0} },
    { { 0.5f, 0.5f, 0.5f}, {0,0,1}, {0.6f,0.2f,0.8f}, {1,1} },
    { { 0.5f, 0.5f, 0.5f}, {0,0,1}, {0.6f,0.2f,0.8f}, {1,1} },
    { {-0.5f, 0.5f, 0.5f}, {0,0,1}, {0.6f,0.2f,0.8f}, {0,1} },
    { {-0.5f,-0.5f, 0.5f}, {0,0,1}, {0.6f,0.2f,0.8f}, {0,0} },

    // BACK (-Z)
    { {-0.5f,-0.5f,-0.5f}, {0,0,-1}, {0.6f,0.2f,0.8f}, {0,0} },
    { {-0.5f, 0.5f,-0.5f}, {0,0,-1}, {0.6f,0.2f,0.8f}, {0,1} },
    { { 0.5f, 0.5f,-0.5f}, {0,0,-1}, {0.6f,0.2f,0.8f}, {1,1} },
    { { 0.5f, 0.5f,-0.5f}, {0,0,-1}, {0.6f,0.2f,0.8f}, {1,1} },
    { { 0.5f,-0.5f,-0.5f}, {0,0,-1}, {0.6f,0.2f,0.8f}, {1,0} },
    { {-0.5f,-0.5f,-0.5f}, {0,0,-1}, {0.6f,0.2f,0.8f}, {0,0} },

    // LEFT (-X)
    { {-0.5f, 0.5f, 0.5f}, {-1,0,0}, {0.6f,0.2f,0.8f}, {1,1} },
    { {-0.5f, 0.5f,-0.5f}, {-1,0,0}, {0.6f,0.2f,0.8f}, {0,1} },
    { {-0.5f,-0.5f,-0.5f}, {-1,0,0}, {0.6f,0.2f,0.8f}, {0,0} },
    { {-0.5f,-0.5f,-0.5f}, {-1,0,0}, {0.6f,0.2f,0.8f}, {0,0} },
    { {-0.5f,-0.5f, 0.5f}, {-1,0,0}, {0.6f,0.2f,0.8f}, {1,0} },
    { {-0.5f, 0.5f, 0.5f}, {-1,0,0}, {0.6f,0.2f,0.8f}, {1,1} },

    // RIGHT (+X)
    { { 0.5f, 0.5f, 0.5f}, {1,0,0}, {0.6f,0.2f,0.8f}, {1,1} },
    { { 0.5f,-0.5f,-0.5f}, {1,0,0}, {0.6f,0.2f,0.8f}, {0,0} },
    { { 0.5f, 0.5f,-0.5f}, {1,0,0}, {0.6f,0.2f,0.8f}, {0,1} },
    { { 0.5f,-0.5f,-0.5f}, {1,0,0}, {0.6f,0.2f,0.8f}, {0,0} },
    { { 0.5f, 0.5f, 0.5f}, {1,0,0}, {0.6f,0.2f,0.8f}, {1,1} },
    { { 0.5f,-0.5f, 0.5f}, {1,0,0}, {0.6f,0.2f,0.8f}, {1,0} },

    // TOP (+Y)
    { {-0.5f, 0.5f,-0.5f}, {0,1,0}, {0.6f,0.2f,0.8f}, {0,1} },
    { {-0.5f, 0.5f, 0.5f}, {0,1,0}, {0.6f,0.2f,0.8f}, {0,0} },
    { { 0.5f, 0.5f, 0.5f}, {0,1,0}, {0.6f,0.2f,0.8f}, {1,0} },
    { { 0.5f, 0.5f, 0.5f}, {0,1,0}, {0.6f,0.2f,0.8f}, {1,0} },
    { { 0.5f, 0.5f,-0.5f}, {0,1,0}, {0.6f,0.2f,0.8f}, {1,1} },
    { {-0.5f, 0.5f,-0.5f}, {0,1,0}, {0.6f,0.2f,0.8f}, {0,1} },

    // BOTTOM (-Y)
    { {-0.5f,-0.5f,-0.5f}, {0,-1,0}, {0.6f,0.2f,0.8f}, {0,1} },
    { { 0.5f,-0.5f,-0.5f}, {0,-1,0}, {0.6f,0.2f,0.8f}, {1,1} },
    { { 0.5f,-0.5f, 0.5f}, {0,-1,0}, {0.6f,0.2f,0.8f}, {1,0} },
    { { 0.5f,-0.5f, 0.5f}, {0,-1,0}, {0.6f,0.2f,0.8f}, {1,0} },
    { {-0.5f,-0.5f, 0.5f}, {0,-1,0}, {0.6f,0.2f,0.8f}, {0,0} },
    { {-0.5f,-0.5f,-0.5f}, {0,-1,0}, {0.6f,0.2f,0.8f}, {0,1} }
};
  Shader shader("shaders/basic.vert", "shaders/basic.frag");
  Mesh mesh(vertices);
  Transform transform;
  glm::vec3 position(0.0f, 0.0f, 0.0f), rotation(0.0f, 0.0f, 0.0f), scale(1.0f, 1.0f, 1.0f);
  transform.setPosition(&position);
  transform.setRotation(&rotation);
  transform.setScale(&scale);
  Material material;
  Texture texture("");
  material.setColor(glm::vec3(1.0f, 1.0f, 1.0f));
  material.setShader(&shader);
  material.setTexture(&texture);
  material.setShininess(30.0f);
  material.setSpecularColor(glm::vec3(1.0f, 1.0f, 1.0f));
  material.setSpecularStrength(6.0f);
  Gameobject gameobject("Monkey Triangle");
  
  gameobject.SetMesh(&mesh);
  gameobject.SetMaterial(&material);
  gameobject.SetTransform(&transform);
  gameobjects.push_back(&gameobject);
  Gameobject* selected = &gameobject;
  float deltaTime, lastFrame = 0.0f;
  while(!mainWindow->ShouldClose()){
    float currentFrame = mainWindow->GetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    mainWindow->PollEvents();
    UI::BeginFrame();
    Renderer::NewFrame();
    renderer.SetCamera(editorCamera);
    if(playing){
      renderer.SetCamera(gameCamera);
      Input::HandleGameInput();
    }else{
      renderer.SetCamera(editorCamera);
      Input::HandleEngineInput(
            mainWindow.get(), editorCamera, deltaTime, lastX, lastY, firstMouse
          );
    }
    for(Gameobject* object : gameobjects){
      renderer.Submit(object);
    }
    if(selected != nullptr){
      UI::LoadInspector(selected);
    }
    UI::EndFrame();
    mainWindow->SwapBuffers();
  }

  mainWindow->Terminate();
  glfwTerminate();
  return 0;
}
