#pragma once
#include <string>
#include <GLFW/glfw3.h>
class Window{
  public:
    Window(int width, int height, std::string title);
    void PollEvents();
    void SwapBuffers();
    bool ShouldClose();
  private:
    GLFWwindow* window;
};
