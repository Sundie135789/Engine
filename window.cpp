#include "GL/glew.h"
#include "headers/globals.hpp"
#include <iostream>
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "headers/window.hpp"
void framebuffer_size_callback(GLFWwindow* window, int width, int height ){
  if(width == 0 || height == 0) return;
  glViewport(0, 0, width, height);
  editorCamera->aspect = (float)width / (float)height;
  gameCamera->aspect = (float)width / (float)height;
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
  if(key == GLFW_KEY_F3 && action == GLFW_PRESS){
    g_EngineState = g_EngineState == EngineState::Editing ? EngineState::Playing : EngineState::Editing;
  }
}
void Window::setCursorMode(int mode){
  glfwSetInputMode(window, GLFW_CURSOR, mode);
  cursorMode = mode;
}
Window::Window(int width, int height, std::string title){
  glfwInit();
  window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  if(!window){
    std::cout << "Failed to create GLFW window\n";
    std::exit(0);
  }
  glewExperimental = GL_TRUE;
  glfwMakeContextCurrent(window);
  SetVerticalSync();
  glewInit();
  glDisable(GL_CULL_FACE);
  glFrontFace(GL_CCW);
  glCullFace(GL_BACK);
  setCursorMode(GLFW_CURSOR_NORMAL);
  glEnable(GL_DEPTH_TEST);
  glViewport(0,0,width, height);
  glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
  glfwSetKeyCallback(window, key_callback);
  std::cout << "GLFWwindow created successfully!\n" << std::endl;
}
int Window::GetMouseButton(int button){
  return glfwGetMouseButton(window, button);
}
void Window::SetVerticalSync(){
  glfwSwapInterval(vsync ? 1 : 0);
}
void Window::PollEvents(){
  glfwPollEvents();
}
void Window::setTitle(std::string title){
  glfwSetWindowTitle(GetWindowHandle(), title.c_str());
}
int Window::GetCursorMode(){
  return cursorMode;
}
void Window::SwapBuffers(){
  if(window){
    glfwSwapBuffers(window);
    return;
  }
  std::cout << "Window found null in Window::SwapBuffers\n";
  std::exit(1);
}
bool Window::ShouldClose(){
  if(window){
    return glfwWindowShouldClose(window);
  }
  std::cout << "Window found null in Window::ShouldClose()\n";
  std::exit(1);
}
int Window::GetKey(int key){
  if(window){
    return glfwGetKey(this->window, key);
  }
  std::cout << "Window found null in Window::GetKey()\n";
  std::exit(1);
}

void Window::GetCursorPos(double& xPos, double& yPos){
  if(window){
    return glfwGetCursorPos(this->window, &xPos, &yPos);
  }
  std::cout << "Window found null in Window::GetCursorPos()\n";
  std::exit(1);
}

GLFWwindow* Window::GetWindowHandle(){
  if(window){
    return window;
  }
  std::cout << "Window found null in WIndow::GetWindowHandle()\n";
  std::exit(1);
}
float Window::GetTime(){
  return glfwGetTime();
}
void Window::Terminate(){
  glfwTerminate();
}
// TODO window resize detect, gl view port
                                                             
