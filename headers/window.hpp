#pragma once
#include <string>
#include <GLFW/glfw3.h>
class Window{
  public:
    Window(int width, int height, std::string title);
    void PollEvents();
    void SwapBuffers();
    bool ShouldClose();
    void Init();
    int GetKey(int key);
    void GetCursorPos(double& xPos, double& yPos);
    void setCursorMode(int mode);
    float GetTime();
    GLFWwindow* GetWindowHandle();
    void Terminate();
  private:
    GLFWwindow* window;
};
