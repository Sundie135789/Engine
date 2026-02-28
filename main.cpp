/*
 The model matrix is handled by a Gameobject's Transform class.
 The projection and view matrices require a separate Camera class, even if there is only one Camera (uptill now).
 This is because the code inside a Camera class, written raw inside the main function in main.cpp would be catastrophic for cleanliness;
 * */
#include <iostream>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include "mesh.hpp"
#include "shader.hpp"
#include "gameobject.hpp"
#include "global.hpp"
#include "texture.hpp"
#include "sidepane.hpp"
#include "transform.hpp"
#include "camera.hpp"
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
#define WINDOW_WIDTH 2560
#define WINDOW_HEIGHT 1920

std::vector<GameObject*> gameobjects;

void goTerminate(){
  for(auto g : gameobjects){
    delete g;
  }
  gameobjects.clear();
  glfwTerminate();

}
int main(void){
  Camera* mainCamera = new Camera((float)WINDOW_WIDTH/WINDOW_HEIGHT);

  if(!glfwInit()){
    std::cout << "GLFW Init error" << std::endl;
    goTerminate();
    return 1;
  }
  GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "GameEngine - SundieCoder v1.0", nullptr, nullptr);
  glfwMakeContextCurrent(window);
  glewExperimental = GL_TRUE;
  GLenum glewStatus = glewInit();
  if(glewStatus != GLEW_OK){
    std::cout << "GLEW Init error" << std::endl;
    goTerminate();
    return 1;
  }
  glViewport(0,0,WINDOW_WIDTH, WINDOW_HEIGHT);
  // --- OpenGL Code ---
  //loadSidePane();
  float vertices[] = {
    -0.375f, -0.375f, 0.0f, 0.0f, 0.0f,
    0.375f, -0.375f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.375f, 0.0f ,0.5f, 1.0f
  };
  Texture* texture = new Texture("assets/monkey.png");
  Mesh* mesh = new Mesh(vertices, 3, true);
  Shader* shader = new Shader("shaders/texture.vert", "shaders/texture.frag");
  Transform* transform = new Transform();
  //shader->SetColor(0.5f, 0.5f, 0.5f);
  shader->SetTexture(texture);
  //shader->SetTexture(text);
  GameObject* gameobject = new GameObject("triangle");
  gameobject->SetShader(shader);
  gameobject->SetMesh(mesh);
  gameobject->SetTransform(transform);
  gameobjects.push_back(gameobject);
  while(!glfwWindowShouldClose(window)){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT);
    assert(mainCamera != nullptr);
    for(GameObject* g : gameobjects){
      g->draw(*mainCamera);
    }
    sidePaneShader->use();
    sidePaneShader->SetMatrix("view", mainCamera->GetViewMatrix());
    sidePaneShader->SetMatrix("projection", mainCamera->GetProjectionMatrix());
    glBindVertexArray(sidePaneVAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwDestroyWindow(window);
  goTerminate();
  return 0;
}
