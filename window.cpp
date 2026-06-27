#include "GL/glew.h"
#include <iostream>
#include "GLFW/glfw3.h"
#include "headers/window.hpp"
void Window::setCursorMode(int mode){
  glfwSetInputMode(window, GLFW_CURSOR, mode);
}
Window::Window(int width, int height, std::string title){
  window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  glewExperimental = GL_TRUE;
  glfwMakeContextCurrent(window);
  this->setCursorMode(GLFW_CURSOR_NORMAL);
  glewInit();
  glEnable(GL_DEPTH_TEST);
  glViewport(0,0,width, height);
  std::cout << "GLFWwindow created successfully!\n" << std::endl;
}
void Window::PollEvents(){
  glfwPollEvents();
}
void Window::SwapBuffers(){
  glfwSwapBuffers(window);
}
bool Window::ShouldClose(){
  return glfwWindowShouldClose(window);
}
void Window::Init(){
  glfwInit();
}
int Window::GetKey(int key){
  return glfwGetKey(this->window, key);
}

void Window::GetCursorPos(double& xPos, double& yPos){
  glfwGetCursorPos(this->window, &xPos, &yPos);
}

GLFWwindow* Window::GetWindowHandle(){
  return this->window;
}
float Window::GetTime(){
  return glfwGetTime();
}
void Window::Terminate(){
  glfwTerminate();
}
                                                             
