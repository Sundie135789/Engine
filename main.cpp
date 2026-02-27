#include <iostream>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include "mesh.hpp"
#include "shader.hpp"
#include "gameobject.hpp"
#include "global.hpp"
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
  float vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f
  };
  Mesh* mesh = new Mesh(vertices, 3);
  Shader* shader = new Shader("shaders/plain.vert", "shaders/plain.frag");
  GameObject gameobject(shader, mesh);
  while(!glfwWindowShouldClose(window)){
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwDestroyWindow(window);
  goTerminate();
  return 0;
}
