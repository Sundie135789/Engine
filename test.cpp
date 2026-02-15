#include <GLFW/glfw3.h>
#include <iostream>

int main(){
  if(!glfwInit())  return -1;
  GLFWwindow* win = glfwCreateWindow(100, 100, "Test", nullptr, nullptr);
  glfwMakeContextCurrent(win);
  int major, minor;
  glfwGetVersion(&major, &minor, nullptr);
  std::cout << "GLFW Version: " << major + "." << minor << std::endl;
  glfwTerminate();
  return 0;
}
