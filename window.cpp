#include "GL/glew.h"
#include <iostream>
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "headers/window.hpp"
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
  glfwSwapInterval(1);
  glewInit();
  glDisable(GL_CULL_FACE);
  glFrontFace(GL_CCW);
  setCursorMode(GLFW_CURSOR_NORMAL);
  glEnable(GL_DEPTH_TEST);
  glViewport(0,0,width, height);
  std::cout << "GLFWwindow created successfully!\n" << std::endl;
}
int Window::GetMouseButton(int button){
  return glfwGetMouseButton(window, button);
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
                                                             
