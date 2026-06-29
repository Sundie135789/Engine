#pragma once
#include <string>
#include <GLFW/glfw3.h>
class Window{
  public:
    Window(int width, int height, std::string title);
    void PollEvents();
    void SwapBuffers();
    bool ShouldClose();
    int GetKey(int key);
    void GetCursorPos(double& xPos, double& yPos);
    void setCursorMode(int mode);
    float GetTime();
    GLFWwindow* GetWindowHandle();
    void Terminate();
    int GetMouseButton(int button);
    int GetCursorMode();
    void setTitle(std::string title);
  private:
    GLFWwindow* window;
    int cursorMode;
};
