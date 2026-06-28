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
#include "headers/dirlight.hpp"
#include "headers/input.hpp"
#include "headers/globals.hpp"
#include "headers/model.hpp"
// C++ headers
#include <vector>
#include <iostream>
// find a obj + mtl + some png/jpeg model, and load it. obj + mtl will load, send png jpeg to Texture to load through stbi.
// convert UI to zTheme style + testing

int main(){
  UI::Init(mainWindow->GetWindowHandle());
  Renderer renderer;
  DirectionalLight light(glm::vec3(-0.5f, -1.0f, -0.8f), glm::vec3(1.0f, 1.0f, 1.0f));
  renderer.SetLight(&light);
  
  /*std::vector<Vertex> vertices = {

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
};*/
  Shader shader("shaders/basic.vert", "shaders/basic.frag");
  ModelData carData = Model::LoadOBJ("assets/.obj");
  Mesh mesh(carData.vertices);
  Transform transform;
  glm::vec3 position(0.0f, 0.0f, 0.0f), rotation(0.0f, 0.0f, 0.0f), scale(1.0f, 1.0f, 1.0f);
  transform.setPosition(&position);
  transform.setRotation(&rotation);
  transform.setScale(&scale);
  Material material;
  material.setColor(glm::vec3(1.0f, 1.0f, 1.0f));
  material.setShader(&shader);
  if(!carData.texturePath.empty()){
    std::string fullTexPath = "assets/" + carData.texturePath;
    static Texture carTexture(fullTexPath.c_str());
    material.setTexture(&carTexture);
  }
  material.setShininess(30.0f);
  material.setSpecularColor(glm::vec3(1.0f, 1.0f, 1.0f));
  material.setSpecularStrength(6.0f);
  Gameobject gameobject("Monkey Cube");
  
  gameobject.SetMesh(&mesh);
  gameobject.SetMaterial(&material);
  gameobject.SetTransform(&transform);
  gameobjects.push_back(&gameobject);
  Gameobject* selected = &gameobject;
  float deltaTime, lastFrame = 0.0f;
  while(!mainWindow->ShouldClose()){
    mainWindow->PollEvents();
    float currentFrame = mainWindow->GetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    std::cout << 1.0f/deltaTime << " FPS\n";
    UI::BeginFrame();
    Renderer::NewFrame();
    if(g_EngineState == EngineState::Playing){
      renderer.SetCamera(gameCamera);
      Input::HandleGameInput();
    }else if(g_EngineState == EngineState::Editing){
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
