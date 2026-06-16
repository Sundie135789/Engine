// Graphics header
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
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
// C++ headers
#include <vector>
#include <iostream>
#include <cmath>
#define USER_SPEED 10.0f
#define SENSITIVITY 0.1f
// adjust specular multiplier and shininess in renderer.cpp. dont hardcode shininess. then add specular color and strenght to material.cpp
// then pass them through renderer to fragment shader. vec3 specular = spec * materialSpecular * lightColor * specularStrength;
std::vector<Gameobject*> gameobjects;
Camera* editorCamera = new Camera();
float lastX, lastY;
bool firstMouse = true;
void processInput(GLFWwindow* window, float deltaTime){
  double mouseX, mouseY;
  glfwGetCursorPos(window, &mouseX, &mouseY);
  float deltaX = mouseX - lastX;
  float deltaY = lastY - mouseY; 
  if(firstMouse)
  {
    lastX = mouseX;
    lastY = mouseY;
    firstMouse = false;
  }
  lastX = mouseX;
  lastY = mouseY;
  editorCamera->yaw += deltaX * SENSITIVITY;
  editorCamera->pitch += deltaY * SENSITIVITY;
  glm::vec3 direction;
  direction.x = cos(glm::radians(editorCamera->yaw) * cos(glm::radians(editorCamera->pitch)));
  direction.y = sin(glm::radians(editorCamera->pitch));
  direction.z = sin(glm::radians(editorCamera->yaw) * cos(glm::radians(editorCamera->pitch)));
  editorCamera->front = glm::normalize(direction);
  float speed = USER_SPEED * deltaTime;
  glm::vec3 flatFront = glm::normalize(glm::vec3(editorCamera->front.x, 0.0f, editorCamera->front.z));
  glm::vec3 right = glm::normalize(glm::cross(editorCamera->front, glm::vec3(0,1,0)));
  if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)  editorCamera->position += flatFront * speed;
  if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)  editorCamera->position -= flatFront * speed;
  if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)  editorCamera->position -= right * speed;
  if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)  editorCamera->position += right * speed;
}
bool gameObjectSelected = false;
int main(){
  glfwInit();
  GLFWwindow* window = glfwCreateWindow(2560, 1920, "Game Engine - x64", nullptr, nullptr);
  glewExperimental = GL_TRUE;
  glfwMakeContextCurrent(window);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glewInit();
  UI::Init(window);
  glEnable(GL_DEPTH_TEST);
  glViewport(0,0,2560,1920);
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
  Texture texture("assets/monkey.png");
  material.setColor(glm::vec3(1.0f, 1.0f, 1.0f));
  material.setShader(&shader);
  material.setTexture(&texture);
  material.setShininess(30.0f);
  material.setSpecularColor(glm::vec3(0.5f, 1.0f, 1.0f));
  material.setSpecularStrength(6.0f);
  Gameobject gameobject("Monkey Triangle");
  
  gameobject.SetMesh(&mesh);
  gameobject.SetMaterial(&material);
  gameobject.SetTransform(&transform);
  gameobjects.push_back(&gameobject);
  //Texture texture("assets/monkey.png");
  Gameobject* selected = &gameobject;
  float deltaTime, lastFrame = 0.0f;
  while(!glfwWindowShouldClose(window)){
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    glfwPollEvents();
    //ImGui Frame Start
    UI::BeginFrame();
    Renderer::NewFrame();
    renderer.SetCamera(editorCamera);
    processInput(window, deltaTime);
    //std::cout << editorCamera->position.x << editorCamera->position.y << editorCamera->position.z <<  std::endl;
    for(Gameobject* object : gameobjects){
      renderer.Submit(object);
    }
    if(selected != nullptr){
      UI::LoadInspector(selected);
    }
    UI::EndFrame();
    glfwSwapBuffers(window);
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
